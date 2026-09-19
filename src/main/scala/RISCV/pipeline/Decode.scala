package RISCV
import chisel3._
import _root_.circt.stage.ChiselStage
import scala.math._
import chisel3.util._ 

class InstructionBundle extends Bundle {
  val rs1 = UInt(7.W)
  val rs1_val = UInt(32.W)
  val rs2 = UInt(7.W)
  val rs2_val = UInt(32.W)
  val rd = UInt(7.W)
  val rd_val = UInt(32.W)
  val rd_wen = Bool()
  val immediate = UInt(32.W)
  val opcode = UInt(7.W)
  val func3 = UInt(3.W)
  val func7 = UInt(7.W)
  val pc = UInt(32.W)
  val warp = UInt(2.W)
}

class Decode() extends Module {
	val io = IO(new Bundle {
		val fetch_result = Input(Valid(new FetchResult))
		val decoded = Output(Valid(new InstructionBundle()))
		val flush = Input(Bool())
		val stall = Input(Bool())
		val active_warp = Input(UInt(2.W))
	})

	val decoder = Module(new Decoder())
	decoder.io.instruction := io.fetch_result.bits.inst

	val rs1 = RegInit(0.U(7.W))
	val rs2 = RegInit(0.U(7.W))
	val rd  = RegInit(0.U(7.W))
	val immediate = RegInit(0.U(32.W))
	val opcode = RegInit(0.U(7.W))
	val func3 = RegInit(0.U(3.W))
	val func7 = RegInit(0.U(7.W))
	val pc = RegInit(0.U(32.W))
	val warp = RegInit(0.U(2.W))
	val valid = RegInit(false.B)
	val wen = RegInit(false.B)

	when(io.flush) {
		valid := false.B
	}.elsewhen(!io.stall) {
		rs1 := decoder.io.rs1 + (io.fetch_result.bits.warp << 5)
		rs2 := decoder.io.rs2 + (io.fetch_result.bits.warp << 5)
		rd := decoder.io.rd + (io.fetch_result.bits.warp << 5)
		immediate := decoder.io.immediate
		opcode := decoder.io.opcode
		func3 := decoder.io.func3
		func7 := decoder.io.func7
		pc := io.fetch_result.bits.pc
		warp := io.active_warp
		valid := io.fetch_result.valid
		wen := decoder.io.wen
	}

  io.decoded.bits.rs1 := rs1
  io.decoded.bits.rs2 := rs2
  io.decoded.bits.rs1_val := 0.U
  io.decoded.bits.rs2_val := 0.U
  io.decoded.bits.rd_val := 0.U
  io.decoded.bits.rd_wen := wen
  io.decoded.bits.rd := rd
  io.decoded.bits.immediate := immediate
  io.decoded.bits.opcode := opcode
  io.decoded.bits.func3 := func3
  io.decoded.bits.func7 := func7
  io.decoded.bits.pc := pc
  io.decoded.bits.warp := warp
  io.decoded.valid := valid
}