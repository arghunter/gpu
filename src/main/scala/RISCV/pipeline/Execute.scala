package RISCV
import chisel3._
import chisel3.util._
import _root_.circt.stage.ChiselStage

object ExecState extends ChiselEnum {
  val IDLE, MEM_WAIT = Value
}

class Execute() extends Module {
	val io = IO(new Bundle {
		val instruction = Input(Valid(new InstructionBundle()))
		val next_instruction = Output(Valid(new InstructionBundle()))

		val pc_redirect = Output(Valid(UInt(32.W)))

		val dcache_req = Output(new MemReq)
		val dcache_start = Output(Bool())
		val dcache_ready = Input(Bool())
		val dcache_valid = Input(Bool())
		val dcache_data = Input(UInt(32.W))
		val dcache_rd = Output(UInt(5.W))
		val dcache_wen = Output(Bool())

		val memory_stall = Output(Bool())
		val jump_flush = Output(Bool())

		val warp_swap = Output(Bool())
	})

	val alu = Module(new ALU())
	val malu = Module(new MALU())

	val state = RegInit(ExecState.IDLE)
	val bundle = RegInit(0.U.asTypeOf(new InstructionBundle()))
	val valid = RegInit(false.B)

	// defaults
	io.pc_redirect.valid := false.B
	io.pc_redirect.bits := 0.U
	io.dcache_start := false.B
	io.dcache_req.address := 0.U
	io.dcache_req.write_data := 0.U
	io.dcache_req.op := MemOp.LW
	io.dcache_req.read := false.B
	io.dcache_req.write := false.B
	io.memory_stall := false.B
	io.jump_flush := false.B
	io.dcache_rd := 0.U
	io.dcache_wen := false.B
	io.warp_swap := false.B

	alu.io.func7 := io.instruction.bits.func7
	// func7 is instruction(31,25), which on an I-type op is really imm[11:5], so the ALU has to
	// know the format before it trusts a func7 that looks like Zbb.
	alu.io.isR := io.instruction.bits.opcode === "b0110011".U
	alu.io.func3 := io.instruction.bits.func3
	alu.io.a := io.instruction.bits.rs1_val
	alu.io.b := 0.U

	malu.io.func7 := io.instruction.bits.func7
	malu.io.func3 := io.instruction.bits.func3
	malu.io.a := io.instruction.bits.rs1_val
	malu.io.b := 0.U
	malu.io.start := false.B

	valid := false.B

  	val flush_delay = RegNext(io.jump_flush, false.B)
	when(state === ExecState.IDLE) {
		when(io.instruction.valid) {
			val inst = io.instruction.bits
			val pc_plus_4 = inst.pc + 4.U
			val pc_plus_imm = inst.pc + inst.immediate
			val addr = inst.rs1_val + inst.immediate
			
			bundle := inst
			bundle.rd_wen := false.B
			bundle.rd_val := 0.U
			valid := true.B

			switch(inst.opcode) {
				// ALU reg-imm / reg-reg
				is("b0010011".U, "b0110011".U) {
					val neg   = Mux(inst.opcode === "b0110011".U && inst.func7 === "b0100000".U && inst.func3 === "b000".U, -inst.rs2_val, inst.rs2_val)
					val alu_b = Mux(inst.opcode === "b0010011".U, inst.immediate, neg)
					val isM = inst.opcode === "b0110011".U && inst.func7 === "b0000001".U
					alu.io.b := alu_b
					malu.io.b := alu_b
					malu.io.start := isM && malu.io.ready
					bundle.rd_val := Mux(isM,malu.io.output,alu.io.output)
					bundle.rd_wen := true.B
					io.memory_stall :=  isM && !malu.io.valid
				}

				// Branch
				is("b1100011".U) {

					val eq = inst.rs1_val === inst.rs2_val
					val lt_signed = inst.rs1_val.asSInt < inst.rs2_val.asSInt
					val lt_unsigned = inst.rs1_val < inst.rs2_val
					val lt_sel = Mux(inst.func3(1), lt_unsigned, lt_signed)
					val lt_eq_sel = Mux(inst.func3(2), lt_sel, eq)
					val take_branch = lt_eq_sel ^ inst.func3(0)
					val target = Mux(take_branch, pc_plus_imm, pc_plus_4)
					io.pc_redirect.valid := take_branch
					io.pc_redirect.bits := target
					bundle.rd_wen := false.B
					io.jump_flush := take_branch
				}

				// LUI
				is("b0110111".U) {
					bundle.rd_val := inst.immediate
					bundle.rd_wen := true.B
				}

				// AUIPC
				is("b0010111".U) {
					bundle.rd_val := pc_plus_imm
					bundle.rd_wen := true.B
				}

				// JAL
				is("b1101111".U) {
					bundle.rd_val := pc_plus_4
					bundle.rd_wen := true.B
					bundle.pc := pc_plus_imm
					io.pc_redirect.valid := true.B
					io.pc_redirect.bits := pc_plus_imm
					io.jump_flush := true.B
				}

				// JALR
				is("b1100111".U) {
					val target = addr & ~1.U(32.W)
					bundle.rd_val := pc_plus_4
					bundle.rd_wen := true.B
					io.pc_redirect.valid := true.B
					io.pc_redirect.bits  := target
					io.jump_flush := true.B
				}

				// Load
				is("b0000011".U) {
					io.dcache_req.address := addr
					io.dcache_req.read := true.B
					io.dcache_req.write := false.B
					io.dcache_req.op := MuxLookup(inst.func3, MemOp.LW)(Seq(
					"b000".U -> MemOp.LB,
					"b001".U -> MemOp.LH,
					"b010".U -> MemOp.LW,
					"b100".U -> MemOp.LBU,  
					"b101".U -> MemOp.LHU   
					))

					io.dcache_start := io.dcache_ready
					io.dcache_rd := inst.rd
					io.dcache_wen := true.B

					io.memory_stall := !io.dcache_ready
					io.warp_swap := !io.dcache_ready

					bundle.rd_wen := false.B

					valid := io.dcache_ready
				}

				// Store
				is("b0100011".U) {
					io.dcache_req.address := addr
			
					io.dcache_req.write_data := inst.rs2_val
					io.dcache_req.read := false.B
					io.dcache_req.write := true.B
					io.dcache_req.op := MuxLookup(inst.func3, MemOp.SW)(Seq(
					"b000".U -> MemOp.SB,
					"b001".U -> MemOp.SH,
					"b010".U -> MemOp.SW
					))
					io.dcache_start := io.dcache_ready
					io.dcache_rd := 0.U
					io.dcache_wen := false.B
					
					io.memory_stall := !io.dcache_ready
					io.warp_swap := !io.dcache_ready

					bundle.rd_wen := false.B
				}

				// FENCE — treat as NOP
				is("b0001111".U) {
					bundle.rd_wen := false.B
				}
			}
		}
	}

	io.next_instruction.valid := valid
	io.next_instruction.bits := bundle
}