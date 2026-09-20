package RISCV
import chisel3._
import chisel3.util._
import _root_.circt.stage.ChiselStage

object ExecState extends ChiselEnum {
  val IDLE, MEM_WAIT = Value
}

class Execute(cfg: GpuConfig) extends Module {
  val io = IO(new Bundle {
    val instruction = Input(Valid(new InstructionBundle(cfg)))
    val next_instruction = Output(Valid(new InstructionBundle(cfg)))
    val flush = Input(Bool())
    val stall = Input(Bool())

    val pc_redirect = Output(Valid(UInt(32.W)))

    val lsu_req = Decoupled(new VecMemReq(cfg))

    val memory_stall = Output(Bool())
		val jump_flush = Output(Bool())

    val mem_issue = Output(Bool())
    val mem_issue_rd = Output(UInt(5.W))
    val mem_issue_count = Output(UInt(log2Up(cfg.nLanes + 1).W))
  })

  val alus = Seq.fill(cfg.nLanes)(Module(new ALU()))
  val malus = Seq.fill(cfg.nLanes)(Module(new MALU()))
  val malu_ready = malus.map(_.io.ready).reduce(_ && _) //checsks if all ready/all valid
  val malu_valid = malus.map(_.io.valid).reduce(_ && _)

  val state = RegInit(ExecState.IDLE)
  val bundle = RegInit(0.U.asTypeOf(new InstructionBundle(cfg)))
  val valid = RegInit(false.B)

  val lmask = RegInit(((BigInt(1)<< cfg.nLanes)-1).U(cfg.nLanes.W))
  val active_lane = PriorityEncoder(lmask)

  // defaults
  io.mem_issue := false.B
  io.mem_issue_rd := 0.U
  io.mem_issue_count := 0.U
  io.lsu_req.valid := false.B
  io.lsu_req.bits.base  := io.instruction.bits.rs1_val
  io.lsu_req.bits.wdata := io.instruction.bits.rs2_val
  io.lsu_req.bits.imm   := io.instruction.bits.immediate
  io.lsu_req.bits.mask  := lmask
  io.lsu_req.bits.rd    := io.instruction.bits.rd
  io.lsu_req.bits.func3 := io.instruction.bits.func3
  io.lsu_req.bits.write := false.B
  io.pc_redirect.valid := false.B
  io.pc_redirect.bits := 0.U
 
  io.memory_stall := false.B
  io.next_instruction.valid := false.B
  io.next_instruction.bits := bundle
  io.jump_flush := false.B


 
  for (i <- 0 until cfg.nLanes) {
    alus(i).io.func7 := io.instruction.bits.func7
    alus(i).io.isR := io.instruction.bits.opcode === "b0110011".U
    alus(i).io.func3 := io.instruction.bits.func3
    alus(i).io.a := io.instruction.bits.rs1_val(i)
    alus(i).io.b := 0.U

    malus(i).io.func7 := io.instruction.bits.func7
    malus(i).io.func3 := io.instruction.bits.func3
    malus(i).io.a := io.instruction.bits.rs1_val(i)
    malus(i).io.b := 0.U
    malus(i).io.start := false.B
  }



  val flush_delay = RegNext(io.jump_flush, false.B)
  switch(state) {
    is(ExecState.IDLE) {
      when(io.flush) {
        valid := false.B
      }.elsewhen(io.stall) {
        valid := valid
        bundle := bundle
      }.elsewhen(io.instruction.valid) {

        val inst = io.instruction.bits
        bundle := inst
        val pc_plus_4 = inst.pc + 4.U
        val pc_plus_imm = inst.pc + inst.immediate
        val addr = inst.rs1_val(active_lane) + inst.immediate
        bundle.mask := lmask
        bundle.rd_wen := false.B
        bundle.rd_val := VecInit(Seq.fill(cfg.nLanes)(0.U(32.W)))
        valid := true.B
  
        switch(inst.opcode) {
          

          // ALU reg-imm / reg-reg
          is("b0010011".U, "b0110011".U) {
            val isM = inst.opcode === "b0110011".U && inst.func7 === "b0000001".U
            for (i <- 0 until cfg.nLanes) {
              val neg   = Mux(inst.opcode === "b0110011".U && inst.func7 === "b0100000".U && inst.func3 === "b000".U, -inst.rs2_val(i), inst.rs2_val(i))
              val alu_b = Mux(inst.opcode === "b0010011".U, inst.immediate, neg)
              alus(i).io.b := alu_b
              malus(i).io.b := alu_b
              malus(i).io.start := isM && malu_ready
              bundle.rd_val(i) := Mux(isM, malus(i).io.output, alus(i).io.output)
            }
            bundle.rd_wen := true.B
            io.memory_stall :=  isM && !malu_valid


          }
          is("b0001011".U){
            bundle.mask := Fill(cfg.nLanes, 1.U)
            when(inst.func7 ==="b0000000".U ){
              for( i <- 0 until cfg.nLanes){
                bundle.rd_wen := true.B
                bundle.rd_val(i) := i.U
              }
            }.elsewhen(inst.func7 === "b0000100".U){// ballots, tells which bitmask that is the correct one
              bundle.rd_wen := true.B //maps the numbers of not zeros to bits
              val bits = VecInit((0 until cfg.nLanes).map(l => inst.rs1_val(l) =/= 0.U)).asUInt
              for(i<-0 until cfg.nLanes){
                bundle.rd_val(i) :=  bits & lmask
              }
            }.elsewhen(inst.func7 === "b0000101".U){ //lmask, sets the mask
              bundle.rd_wen := true.B
              for(i<-0 until cfg.nLanes){
                bundle.rd_val(i) :=  lmask
              }
              lmask := inst.rs1_val(active_lane)(cfg.nLanes - 1, 0)


            }

          }

          // Branch
          is("b1100011".U) {

            val eq = inst.rs1_val(active_lane) === inst.rs2_val(active_lane)
            val lt_signed = inst.rs1_val(active_lane).asSInt < inst.rs2_val(active_lane).asSInt
            val lt_unsigned = inst.rs1_val(active_lane) < inst.rs2_val(active_lane)
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
            bundle.rd_val := VecInit(Seq.fill(cfg.nLanes)(inst.immediate))
            bundle.rd_wen := true.B
            
          }

          // AUIPC
          is("b0010111".U) {
            bundle.rd_val := VecInit(Seq.fill(cfg.nLanes)(pc_plus_imm))
            bundle.rd_wen := true.B
           
          }

          // JAL
          is("b1101111".U) {
                        // printf("JAL target pc: %d inst pc: %d\n",pc_plus_imm, inst.pc)

            bundle.rd_val := VecInit(Seq.fill(cfg.nLanes)(pc_plus_4))
            bundle.rd_wen := true.B
            bundle.pc := pc_plus_imm
            io.pc_redirect.valid := true.B
            io.pc_redirect.bits := pc_plus_imm
            io.jump_flush := true.B
          }

          // JALR
          is("b1100111".U) {

            val target = addr & ~1.U(32.W)
            bundle.rd_val := VecInit(Seq.fill(cfg.nLanes)(pc_plus_4))
            bundle.rd_wen := true.B
            io.pc_redirect.valid := true.B
            io.pc_redirect.bits  := target
            io.jump_flush := true.B
          }

  
          is("b0000011".U) {
            io.lsu_req.valid := true.B
            io.lsu_req.bits.write := false.B
            io.memory_stall := !io.lsu_req.ready
            valid := io.lsu_req.ready
            bundle.rd_wen := false.B
            io.mem_issue := io.lsu_req.ready
            io.mem_issue_rd := inst.rd
            io.mem_issue_count := PopCount(lmask)
          }

          is("b0100011".U) {
            io.lsu_req.valid := true.B
            io.lsu_req.bits.write := true.B
            io.memory_stall := !io.lsu_req.ready
            valid := io.lsu_req.ready
            bundle.rd_wen := false.B
          }

          // FENCE — treat as NOP
          is("b0001111".U) {
            bundle.rd_wen := false.B
          }
        }
      }.otherwise {
        valid := false.B
      }
    }
  }

  when(state === ExecState.IDLE) {
    val is_jump_or_branch = bundle.opcode === "b1101111".U || 
                          bundle.opcode === "b1100111".U || 
                          bundle.opcode === "b1100011".U

  io.next_instruction.valid := valid && (!io.flush || is_jump_or_branch)
  io.next_instruction.bits := bundle
  }
}