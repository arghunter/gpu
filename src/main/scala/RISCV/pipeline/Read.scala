package RISCV
import chisel3._
import _root_.circt.stage.ChiselStage
import scala.math._
import chisel3.util._ 

<<<<<<< HEAD
class Read(cfg: GpuConfig) extends Module {
  val io = IO(new Bundle {
    val instruction = Input(Valid(new InstructionBundle(cfg)))
    val register_read_a = Output(UInt(5.W))
    val register_read_b = Output(UInt(5.W))
    val register_value_a = Input(Vec(cfg.nLanes, UInt(32.W)))
    val register_value_b = Input(Vec(cfg.nLanes, UInt(32.W)))
    val next_instruction = Output(Valid(new InstructionBundle(cfg)))
    val flush = Input(Bool())
    val stall = Input(Bool())
    val rum  = Input(UInt(32.W))
    val raw_hazard_stall = Output(Bool())
  })
||||||| 6fe8822
class Read() extends Module {
  val io = IO(new Bundle {
    val instruction = Input(Valid(new InstructionBundle()))
    val register_read_a = Output(UInt(5.W))
    val register_read_b = Output(UInt(5.W))
    val register_value_a = Input(UInt(32.W))
    val register_value_b = Input(UInt(32.W))
    val next_instruction = Output(Valid(new InstructionBundle()))
    val flush = Input(Bool())
    val stall = Input(Bool())
    val rum  = Input(UInt(32.W))
    val raw_hazard_stall = Output(Bool())
  })
=======
class Read() extends Module {
	val io = IO(new Bundle {
		val instruction = Input(Valid(new InstructionBundle()))
		val register_read_a = Output(UInt(5.W))
		val register_read_b = Output(UInt(5.W))
		val register_value_a = Input(UInt(32.W))
		val register_value_b = Input(UInt(32.W))
		val next_instruction = Output(Valid(new InstructionBundle()))
		val flush = Input(Bool())
		val stall = Input(Bool())
		val rum  = Input(UInt(128.W))
		val raw_hazard_stall = Output(Bool())
	})
>>>>>>> origin/warps

	val raw_hazard = io.instruction.valid && (
		(io.rum(io.instruction.bits.rs1) && io.instruction.bits.rs1 =/= 0.U) ||
		(io.rum(io.instruction.bits.rs2) && io.instruction.bits.rs2 =/= 0.U) ||
		(io.instruction.bits.rd_wen && io.rum(io.instruction.bits.rd) && io.instruction.bits.rd =/= 0.U)
	)

	io.raw_hazard_stall := raw_hazard

<<<<<<< HEAD
  val bundle = RegInit(0.U.asTypeOf(new InstructionBundle(cfg)))
  val valid  = RegInit(false.B)
  val bundle_w = WireDefault(bundle)
  when(io.flush) {
      valid := false.B
  }.elsewhen(io.stall) {
  }.elsewhen(raw_hazard) {
      valid := false.B
  }.otherwise {
      bundle := io.instruction.bits
      valid := io.instruction.valid
      bundle.rs1_val := io.register_value_a
      bundle.rs2_val := io.register_value_b
  }
||||||| 6fe8822
  val bundle = RegInit(0.U.asTypeOf(new InstructionBundle()))
  val valid  = RegInit(false.B)
  val bundle_w = WireDefault(bundle)
  when(io.flush) {
      valid := false.B
  }.elsewhen(io.stall) {
  }.elsewhen(raw_hazard) {
      valid := false.B
  }.otherwise {
      bundle := io.instruction.bits
      valid := io.instruction.valid
      bundle.rs1_val := io.register_value_a
      bundle.rs2_val := io.register_value_b
  }
=======
	io.register_read_a := io.instruction.bits.rs1
	io.register_read_b := io.instruction.bits.rs2
>>>>>>> origin/warps

	val bundle = RegInit(0.U.asTypeOf(new InstructionBundle()))
	val valid  = RegInit(false.B)
	val bundle_w = WireDefault(bundle)
	
	when(io.flush) {
		valid := false.B
	}.elsewhen(io.stall) {
	}.elsewhen(raw_hazard) {
		valid := false.B
	}.otherwise {
		bundle := io.instruction.bits
		valid := io.instruction.valid
		bundle.rs1_val := io.register_value_a
		bundle.rs2_val := io.register_value_b
	}

<<<<<<< HEAD
  io.next_instruction.bits := bundle_w
  io.next_instruction.valid := valid

  
  
||||||| 6fe8822
  io.next_instruction.bits := bundle_w


  io.next_instruction.valid := valid

  
  
=======
	io.next_instruction.bits := bundle_w
	io.next_instruction.valid := valid
>>>>>>> origin/warps
}