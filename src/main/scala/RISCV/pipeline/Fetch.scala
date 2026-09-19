package RISCV
import chisel3._
import chisel3.util._

object FetchOp extends ChiselEnum {
  val ST, RD, DQ = Value // Stall, Redirect, Dequeue
}

class FetchReq extends Bundle {
  val fetch_op = FetchOp()
  val redirect_addr = UInt(32.W)
}

class FetchResult extends Bundle {
  val pc = UInt(32.W)
  val inst = UInt(32.W)
}

class Fetch() extends Module {
	val io = IO(new Bundle {
		val execute = Input(Bool())

		val active_warp = Input(UInt(4.W))
		val active_pc = Input(UInt(32.W))
		val next_pc = Output(UInt(32.W))

		val fetch_request = Input(new FetchReq)
		val fetch_result = Output(Valid(new FetchResult))
		
		val icache_req = Output(new MemReq)
		val icache_start = Output(Bool())
		val icache_ready = Input(Bool())
		val icache_valid = Input(Bool())
		val icache_data  = Input(UInt(32.W))
	})

	val request_instruction_pointer = RegInit(0.U(32.W))
	val ignore_instruction = RegInit(false.B)
	val in_flight = RegInit(false.B)

	val fetch_result = Reg(new FetchResult)
	val fetch_result_valid = RegInit(false.B)

	io.icache_req.address := io.active_pc
	io.icache_req.op := MemOp.LW
	io.icache_req.write_data := 0.U
	io.icache_req.read := true.B
	io.icache_req.write := false.B
	io.icache_start := false.B

	io.fetch_result.valid := fetch_result_valid
	io.fetch_result.bits := fetch_result

	io.next_pc := io.active_pc

	val stalling = io.execute && io.fetch_request.fetch_op === FetchOp.ST
	val dequeuing = io.execute && io.fetch_request.fetch_op === FetchOp.DQ
	val redirecting = io.execute && io.fetch_request.fetch_op === FetchOp.RD

	val can_issue = io.icache_ready && !fetch_result_valid

	def issue(instruction_pointer: UInt): Unit = {
		io.icache_req.address := instruction_pointer
		io.icache_start := true.B
		request_instruction_pointer := instruction_pointer
		io.next_pc := instruction_pointer + 4.U
	}

	when(io.execute) {
		when((dequeuing || stalling) && can_issue) {
			issue(io.active_pc)
		}

		when(redirecting) {
			when(can_issue) {
				issue(io.fetch_request.redirect_addr)
			}.otherwise {
				io.next_pc := io.fetch_request.redirect_addr
			}
			
			ignore_instruction := in_flight && !io.icache_valid
		}
	}

	when(io.icache_valid && ignore_instruction) {
		ignore_instruction := false.B
	}

	when(redirecting) {
		fetch_result_valid := false.B        
	}.otherwise {
		when(io.icache_valid && !ignore_instruction) {
			fetch_result.pc   := request_instruction_pointer
			fetch_result.inst := io.icache_data
			fetch_result_valid := true.B
		}.elsewhen(dequeuing) {
			fetch_result_valid := false.B
		}
	}

	in_flight := io.icache_start || (!io.icache_valid && in_flight)
}