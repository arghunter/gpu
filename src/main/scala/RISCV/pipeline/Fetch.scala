package RISCV
import chisel3._
import chisel3.util._

object FetchOp extends ChiselEnum {
  val ST, RD, DQ, WS = Value // Stall, Redirect, Dequeue, Warp Switch
}

class FetchReq extends Bundle {
  val fetch_op = FetchOp()
  val redirect_addr = UInt(32.W)
}

class FetchResult extends Bundle {
  val pc = UInt(32.W)
  val warp = UInt(2.W)
  val inst = UInt(32.W)
}

class Fetch() extends Module {
	val io = IO(new Bundle {
		val execute = Input(Bool())

		val active_warp = Input(UInt(2.W))

		val mark = Input(Bool())
		val mark_pc = Input(UInt(32.W))
		val mark_warp = Input(UInt(2.W))

		val allocate_warp = Input(Bool())
    val allocate_pc = Input(UInt(32.W))
		val allocate_id = Input(UInt(2.W))

		val fetch_request = Input(new FetchReq)
		val fetch_result = Output(Valid(new FetchResult))
		
		val icache_req = Output(new MemReq)
		val icache_start = Output(Bool())
		val icache_ready = Input(Bool())
		val icache_valid = Input(Bool())
		val icache_data  = Input(UInt(32.W))
	})

	val speculative_instruction_pointers = RegInit(VecInit(Seq.fill(4.toInt)(0.U(32.W))))
	val instruction_pointers = RegInit(VecInit(Seq.fill(4.toInt)(0.U(32.W))))

	when(io.mark) {
		instruction_pointers(io.mark_warp) := io.mark_pc
	}

	
	val ignore_instruction = RegInit(false.B)
	val request_instruction_pointer = RegInit(0.U(32.W))

	val request_warp = RegInit(0.U(2.W))
	val request_in_flight = RegInit(false.B)

	val fetch_result = Reg(new FetchResult)
	val fetch_result_valid = RegInit(false.B)

	io.icache_req.address := speculative_instruction_pointers(io.active_warp)
	io.icache_req.op := MemOp.LW
	io.icache_req.write_data := 0.U
	io.icache_req.read := true.B
	io.icache_req.write := false.B
	io.icache_start := false.B

	io.fetch_result.valid := fetch_result_valid
	io.fetch_result.bits := fetch_result

	val stalling = io.execute && io.fetch_request.fetch_op === FetchOp.ST
	val dequeuing = io.execute && io.fetch_request.fetch_op === FetchOp.DQ
	val redirecting = io.execute && io.fetch_request.fetch_op === FetchOp.RD
	val warp_switching = io.execute && io.fetch_request.fetch_op === FetchOp.WS

	val can_issue = io.icache_ready && !fetch_result_valid && !io.icache_valid

	when(io.execute) {
    
		when((dequeuing || stalling) && can_issue) {
			io.icache_req.address := speculative_instruction_pointers(io.active_warp)
			io.icache_start := true.B
			request_instruction_pointer := speculative_instruction_pointers(io.active_warp)
			request_warp := io.active_warp
			speculative_instruction_pointers(io.active_warp) := speculative_instruction_pointers(io.active_warp) + 4.U
		}

		when(redirecting) {
			when(can_issue) {
				io.icache_req.address := io.fetch_request.redirect_addr
				io.icache_start := true.B
				request_instruction_pointer := io.fetch_request.redirect_addr
				request_warp := io.active_warp
				speculative_instruction_pointers(io.active_warp) := io.fetch_request.redirect_addr + 4.U
			}.otherwise {
				speculative_instruction_pointers(io.active_warp) := io.fetch_request.redirect_addr
			}

			ignore_instruction := request_in_flight && !io.icache_valid
		}

		when(warp_switching) {
			for(i <- 0 until 4) {
				speculative_instruction_pointers(i.U) := instruction_pointers(i.U)
			}

			ignore_instruction := request_in_flight && !io.icache_valid
		}
	}

	when(io.allocate_warp) {
		instruction_pointers(io.allocate_id) := io.allocate_pc
    speculative_instruction_pointers(io.allocate_id) :=  io.allocate_pc
	}
	when(redirecting) {
		fetch_result_valid := false.B        
	}.otherwise {
		when(warp_switching) {
			fetch_result_valid := false.B
		}.otherwise {
			when(io.icache_valid && !ignore_instruction) {
				fetch_result.pc := request_instruction_pointer
				fetch_result.inst := io.icache_data
				fetch_result.warp := request_warp
				fetch_result_valid := true.B
			}.elsewhen(dequeuing) {
				fetch_result_valid := false.B
			}
		}
	}

	when(io.icache_valid && ignore_instruction) {
		ignore_instruction := false.B
	}

	request_in_flight := io.icache_start || (!io.icache_valid && request_in_flight)
}