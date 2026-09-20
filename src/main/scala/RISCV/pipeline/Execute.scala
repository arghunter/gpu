package RISCV
import chisel3._
import chisel3.util._
import _root_.circt.stage.ChiselStage

object ExecState extends ChiselEnum {
  val IDLE, MEM_WAIT = Value
}

<<<<<<< HEAD
class Execute(cfg: GpuConfig) extends Module {
  val io = IO(new Bundle {
    val instruction = Input(Valid(new InstructionBundle(cfg)))
    val next_instruction = Output(Valid(new InstructionBundle(cfg)))
    val flush = Input(Bool())
    val stall = Input(Bool())
||||||| 6fe8822
class Execute() extends Module {
  val io = IO(new Bundle {
    val instruction = Input(Valid(new InstructionBundle()))
    val next_instruction = Output(Valid(new InstructionBundle()))
    val flush = Input(Bool())
    val stall = Input(Bool())
=======
class Execute() extends Module {
	val io = IO(new Bundle {
		val instruction = Input(Valid(new InstructionBundle()))
		val next_instruction = Output(Valid(new InstructionBundle()))
>>>>>>> origin/warps

		val pc_redirect = Output(Valid(UInt(32.W)))

<<<<<<< HEAD
    val lsu_req = Decoupled(new VecMemReq(cfg))
||||||| 6fe8822
    val dcache_req = Output(new MemReq)
    val dcache_start = Output(Bool())
    val dcache_ready = Input(Bool())
    val dcache_valid = Input(Bool())
    val dcache_data = Input(UInt(32.W))
    val dcache_rd = Output(UInt(5.W))
    val dcache_wen = Output(Bool())
=======
		val dcache_req = Output(new MemReq)
		val dcache_start = Output(Bool())
		val dcache_ready = Input(Bool())
		val dcache_valid = Input(Bool())
		val dcache_data = Input(UInt(32.W))
		val dcache_rd = Output(UInt(5.W))
		val dcache_wen = Output(Bool())
>>>>>>> origin/warps

		val memory_stall = Output(Bool())
		val jump_flush = Output(Bool())
<<<<<<< HEAD

    val mem_issue = Output(Bool())
    val mem_issue_rd = Output(UInt(5.W))
    val mem_issue_count = Output(UInt(log2Up(cfg.nLanes + 1).W))
  })
||||||| 6fe8822
  })
=======
>>>>>>> origin/warps

<<<<<<< HEAD
  val alus = Seq.fill(cfg.nLanes)(Module(new ALU()))
  val malus = Seq.fill(cfg.nLanes)(Module(new MALU()))
  val malu_ready = malus.map(_.io.ready).reduce(_ && _) //checsks if all ready/all valid
  val malu_valid = malus.map(_.io.valid).reduce(_ && _)
||||||| 6fe8822
  val alu = Module(new ALU())
  val malu = Module(new MALU())
=======
		val warp_swap = Output(Bool())
		val warp_terminate = Output(Bool())
>>>>>>> origin/warps

<<<<<<< HEAD
  val state = RegInit(ExecState.IDLE)
  val bundle = RegInit(0.U.asTypeOf(new InstructionBundle(cfg)))
  val valid = RegInit(false.B)
||||||| 6fe8822
  val state = RegInit(ExecState.IDLE)
  val bundle = RegInit(0.U.asTypeOf(new InstructionBundle()))
  val valid = RegInit(false.B)
=======
		val mark = Output(Bool())
		val mark_pc = Output(UInt(32.W))
		val mark_warp = Output(UInt(2.W))
>>>>>>> origin/warps

<<<<<<< HEAD
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
||||||| 6fe8822
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
  io.next_instruction.valid := false.B
  io.next_instruction.bits := bundle
  io.jump_flush := false.B
  io.dcache_rd := 0.U
  io.dcache_wen := false.B
=======
		val active_warp_id = Input(UInt(32.W))
	})
>>>>>>> origin/warps

<<<<<<< HEAD
||||||| 6fe8822
  alu.io.func7 := io.instruction.bits.func7
  // func7 is instruction(31,25), which on an I-type op is really imm[11:5], so the ALU has to
  // know the format before it trusts a func7 that looks like Zbb.
  alu.io.isR := io.instruction.bits.opcode === "b0110011".U
  alu.io.func3 := io.instruction.bits.func3
  alu.io.a := io.instruction.bits.rs1_val
  alu.io.b := 0.U
=======
	val alu = Module(new ALU())
	val malu = Module(new MALU())
>>>>>>> origin/warps

<<<<<<< HEAD
 
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
||||||| 6fe8822
  malu.io.func7 := io.instruction.bits.func7
  malu.io.func3 := io.instruction.bits.func3
  malu.io.a := io.instruction.bits.rs1_val
  malu.io.b := 0.U
  malu.io.start := false.B
=======
	val state = RegInit(ExecState.IDLE)
	val bundle = RegInit(0.U.asTypeOf(new InstructionBundle()))
	val valid = RegInit(false.B)
>>>>>>> origin/warps

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

	alu.io.func7 := io.instruction.bits.func7
	// func7 is instruction(31,25), which on an I-type op is really imm[11:5], so the ALU has to
	// know the format before it trusts a func7 that looks like Zbb.
	alu.io.isR := io.instruction.bits.opcode === "b0110011".U
	alu.io.func3 := io.instruction.bits.func3
	alu.io.a := io.instruction.bits.rs1_val
	alu.io.b := 0.U

<<<<<<< HEAD
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
          
||||||| 6fe8822
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
        val pc_plus_4 = inst.pc + 4.U
        val pc_plus_imm = inst.pc + inst.immediate
        val addr = inst.rs1_val + inst.immediate
        
        bundle := inst
        bundle.rd_wen := false.B
        bundle.rd_val := 0.U
        valid := true.B
  
        switch(inst.opcode) {
          
=======
	malu.io.func7 := io.instruction.bits.func7
	malu.io.func3 := io.instruction.bits.func3
	malu.io.a := io.instruction.bits.rs1_val
	malu.io.b := 0.U
	malu.io.start := false.B
>>>>>>> origin/warps

<<<<<<< HEAD
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
||||||| 6fe8822
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
=======
	valid := false.B
>>>>>>> origin/warps

	io.warp_swap := false.B
	io.warp_terminate := false.B

<<<<<<< HEAD
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
||||||| 6fe8822
          }
=======
	io.mark := false.B
	io.mark_pc := 0.U
	io.mark_warp := 0.U
>>>>>>> origin/warps

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

<<<<<<< HEAD
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
||||||| 6fe8822
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
=======
			io.mark := true.B
			io.mark_warp := inst.warp
			io.mark_pc := inst.pc + 4.U
>>>>>>> origin/warps

<<<<<<< HEAD
            

          }
||||||| 6fe8822
          }
=======
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
>>>>>>> origin/warps

<<<<<<< HEAD
          // LUI
          is("b0110111".U) {
            bundle.rd_val := VecInit(Seq.fill(cfg.nLanes)(inst.immediate))
            bundle.rd_wen := true.B
            
          }
||||||| 6fe8822
          // LUI
          is("b0110111".U) {
            bundle.rd_val := inst.immediate
            bundle.rd_wen := true.B
            
          }
=======
				// Branch
				is("b1100011".U) {
>>>>>>> origin/warps

<<<<<<< HEAD
          // AUIPC
          is("b0010111".U) {
            bundle.rd_val := VecInit(Seq.fill(cfg.nLanes)(pc_plus_imm))
            bundle.rd_wen := true.B
           
          }
||||||| 6fe8822
          // AUIPC
          is("b0010111".U) {
            bundle.rd_val := pc_plus_imm
            bundle.rd_wen := true.B
           
          }
=======
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
>>>>>>> origin/warps

					io.mark_pc := Mux(take_branch, target, inst.pc + 4.U)
				}

<<<<<<< HEAD
            bundle.rd_val := VecInit(Seq.fill(cfg.nLanes)(pc_plus_4))
            bundle.rd_wen := true.B
            bundle.pc := pc_plus_imm
            io.pc_redirect.valid := true.B
            io.pc_redirect.bits := pc_plus_imm
            io.jump_flush := true.B
          }
||||||| 6fe8822
            bundle.rd_val := pc_plus_4
            bundle.rd_wen := true.B
            bundle.pc := pc_plus_imm
            io.pc_redirect.valid := true.B
            io.pc_redirect.bits := pc_plus_imm
            io.jump_flush := true.B
          }
=======
				// LUI
				is("b0110111".U) {
					bundle.rd_val := inst.immediate
					bundle.rd_wen := true.B
				}
>>>>>>> origin/warps

				// AUIPC
				is("b0010111".U) {
					bundle.rd_val := pc_plus_imm
					bundle.rd_wen := true.B
				}

<<<<<<< HEAD
            val target = addr & ~1.U(32.W)
            bundle.rd_val := VecInit(Seq.fill(cfg.nLanes)(pc_plus_4))
            bundle.rd_wen := true.B
            io.pc_redirect.valid := true.B
            io.pc_redirect.bits  := target
            io.jump_flush := true.B
          }
||||||| 6fe8822
            val target = addr & ~1.U(32.W)
            bundle.rd_val := pc_plus_4
            bundle.rd_wen := true.B
            io.pc_redirect.valid := true.B
            io.pc_redirect.bits  := target
            io.jump_flush := true.B
          }
=======
				// JAL
				is("b1101111".U) {
					bundle.rd_val := pc_plus_4
					bundle.rd_wen := true.B
					bundle.pc := pc_plus_imm
					io.pc_redirect.valid := true.B
					io.pc_redirect.bits := pc_plus_imm
					io.jump_flush := true.B
>>>>>>> origin/warps

<<<<<<< HEAD
  
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
||||||| 6fe8822
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
            // printf("LOADLOADLOALDOALDOLAODLOLADO RD: %d addr: %d\n\n", inst.rd,addr)
            io.dcache_wen := true.B
            io.memory_stall := !io.dcache_ready
          //   when(inst.rd === 8.U){
          //   printf("\n\n8 dumps 8 dumped stall: %b\n\n",  !io.dcache_ready)
          // }
            

            bundle.rd_wen := false.B
            valid := io.dcache_ready
        
           
          }
=======
					io.mark_pc := pc_plus_imm
				}

				// JALR
				is("b1100111".U) {
					val target = addr & ~1.U(32.W)
					bundle.rd_val := pc_plus_4
					bundle.rd_wen := true.B
					io.pc_redirect.valid := true.B
					io.pc_redirect.bits  := target
					io.jump_flush := true.B

					io.mark_pc := target
				}
>>>>>>> origin/warps

<<<<<<< HEAD
          is("b0100011".U) {
            io.lsu_req.valid := true.B
            io.lsu_req.bits.write := true.B
            io.memory_stall := !io.lsu_req.ready
            valid := io.lsu_req.ready
            bundle.rd_wen := false.B
          }
||||||| 6fe8822
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
            bundle.rd_wen := false.B
          }
=======
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
>>>>>>> origin/warps

<<<<<<< HEAD
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
||||||| 6fe8822
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
=======
					io.dcache_start := io.dcache_ready
					io.dcache_rd := inst.rd
					io.dcache_wen := true.B

					io.memory_stall := !io.dcache_ready
					io.warp_swap := !io.dcache_ready

					bundle.rd_wen := false.B
>>>>>>> origin/warps

					valid := io.dcache_ready

					io.mark := io.dcache_ready
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

					io.mark := io.dcache_ready
				}

				// FENCE — treat as NOP
				is("b0001111".U) {
					bundle.rd_wen := false.B
				}

				// Lane Instructions
				is("b00001011".U) {
					when(inst.func7 === "b0000010".U) {
						io.warp_terminate := true.B
						io.warp_swap := true.B
					}.otherwise {
						bundle.rd_val := io.active_warp_id
						bundle.rd_wen := true.B
					}
				}
			}
		}
	}

	io.next_instruction.valid := valid
	io.next_instruction.bits := bundle
}