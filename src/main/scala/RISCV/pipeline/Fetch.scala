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

	val fetch_result_0 = Reg(new FetchResult)
	val fetch_result_1 = Reg(new FetchResult)
	val fetch_valid_0 = RegInit(false.B)
	val fetch_valid_1 = RegInit(false.B)

	io.icache_req.address := io.active_pc
	io.icache_req.op := MemOp.LW
	io.icache_req.write_data := 0.U
	io.icache_req.read := true.B
	io.icache_req.write := false.B
	io.icache_start := false.B

	io.fetch_result.valid := fetch_valid_0
	io.fetch_result.bits := fetch_result_0

	io.next_pc := io.active_pc

	val redirecting = io.execute && io.fetch_request.fetch_op === FetchOp.RD
	val dequeuing = io.execute && io.fetch_request.fetch_op === FetchOp.DQ

	val pop = dequeuing && fetch_valid_0
	val push = io.icache_valid && !ignore_instruction && !redirecting

	val pending = fetch_valid_0.asUInt +& fetch_valid_1.asUInt +& in_flight.asUInt
	val effective_pending = pending - pop.asUInt
	val can_issue = io.icache_ready && (effective_pending <= 1.U)

	def issue(instruction_pointer: UInt): Unit = {
		io.icache_req.address := instruction_pointer
		io.icache_start := true.B
		request_instruction_pointer := instruction_pointer
		io.next_pc := instruction_pointer + 4.U
	}

	when(io.execute) {
		switch(io.fetch_request.fetch_op) {
			is(FetchOp.DQ) { 
				when(can_issue) { 
					issue(io.active_pc)
				}
			}

			is(FetchOp.ST) {
				when(can_issue) {
					issue(io.active_pc)
				}
			}

			is(FetchOp.RD) {
				when(can_issue) {
					issue(io.fetch_request.redirect_addr)
				}.otherwise {
					io.next_pc := io.fetch_request.redirect_addr
				}
				
				ignore_instruction := in_flight && !io.icache_valid
			}
		}
	}

	when(io.icache_valid && ignore_instruction) { ignore_instruction := false.B }

	when(redirecting) {
		fetch_valid_0 := false.B        
		fetch_valid_1 := false.B
	}.otherwise {
		when(pop) {
			when(push) {
				when(fetch_valid_1) {
					fetch_result_0 := fetch_result_1
					fetch_result_1.pc := request_instruction_pointer
					fetch_result_1.inst := io.icache_data
				}.otherwise {
					fetch_result_0.pc := request_instruction_pointer
					fetch_result_0.inst := io.icache_data
					fetch_valid_0 := true.B
					fetch_valid_1 := false.B
				}
			}.otherwise {
				when(fetch_valid_1) { fetch_result_0 := fetch_result_1; fetch_valid_1 := false.B }
				.otherwise { fetch_valid_0 := false.B }
			}
		}.otherwise {
			when(push) {
				when(!fetch_valid_0) {
					fetch_result_0.pc := request_instruction_pointer
					fetch_result_0.inst := io.icache_data
					fetch_valid_0 := true.B
				}.elsewhen(!fetch_valid_1) {
					fetch_result_1.pc := request_instruction_pointer
					fetch_result_1.inst := io.icache_data
					fetch_valid_1 := true.B
				}
			}
		}
	}

	in_flight := Mux(io.icache_start, true.B,Mux(io.icache_valid, false.B, in_flight))
}