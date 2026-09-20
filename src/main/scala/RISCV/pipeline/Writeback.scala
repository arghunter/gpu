package RISCV
import chisel3._
import _root_.circt.stage.ChiselStage
import scala.math._
import chisel3.util._

class Writeback(cfg: GpuConfig) extends Module {
  val io = IO(new Bundle {
    val instruction = Input(Valid(new InstructionBundle(cfg)))
    val write_enable = Output(Bool())
    val write_address = Output(UInt(5.W))
    val write_mask = Output(UInt(cfg.nLanes.W))
    val write_val = Output(Vec(cfg.nLanes, UInt(32.W)))

    val mem_write_data = Input(Vec(cfg.nLanes, UInt(32.W)))
    val mem_rd = Input(UInt(5.W))
    val mem_wen = Input(Bool())
    val mem_mask = Input(UInt(cfg.nLanes.W))

    val reg_mem_rum = Output(UInt(32.W))

<<<<<<< HEAD
    val mem_write_enable = Output(Bool())
    val mem_write_address = Output(UInt(5.W))
    val mem_write_mask = Output(UInt(cfg.nLanes.W))
    val mem_write_val = Output(Vec(cfg.nLanes, UInt(32.W)))

    val mem_issue = Input(Bool())
    val mem_issue_rd = Input(UInt(5.W))
    val mem_issue_count = Input(UInt((log2Up(cfg.nLanes)+1).W))


||||||| 6fe8822
    val mem_write_enable    = Output(Bool())
    val mem_write_address   = Output(UInt(5.W))
    val mem_write_val       = Output(UInt(32.W))

    val stall = Input(Bool())
    

=======
    val mem_write_enable    = Output(Bool())
    val mem_write_address   = Output(UInt(5.W))
    val mem_write_val       = Output(UInt(32.W))
>>>>>>> origin/warps
  })




  
  val hijack = (io.mem_rd === io.instruction.bits.rd) && io.mem_wen

  io.write_enable := io.instruction.valid && io.instruction.bits.rd_wen
  io.write_address := io.instruction.bits.rd
  io.write_mask := io.instruction.bits.mask

  for (i <- 0 until cfg.nLanes) {
    io.write_val(i) := Mux(hijack && io.mem_mask(i), io.mem_write_data(i), io.instruction.bits.rd_val(i))
  }

  io.mem_write_enable := io.mem_wen
  io.mem_write_address := io.mem_rd
  io.mem_write_mask := io.mem_mask
  io.mem_write_val := io.mem_write_data


<<<<<<< HEAD
  val mem_pending = RegInit(VecInit(Seq.fill(32)(0.U((log2Up(cfg.nLanes)+1).W))))
  io.reg_mem_rum := VecInit(mem_pending.map(_ =/= 0.U)).asUInt
||||||| 6fe8822
  val mem_rum = RegInit(0.U(32.W))
  val mem_rum_w = WireDefault(mem_rum)  
  val mem_rum_w2 =  WireDefault(mem_rum)  
=======
  val mem_rum = RegInit(0.U(32.W))
  val mem_rum_w = WireDefault(mem_rum)  
  val mem_rum_w2 =  WireDefault(mem_rum)
>>>>>>> origin/warps

<<<<<<< HEAD
  for(i <- 0 until 32){
    val inc = io.mem_issue && io.mem_issue_rd === i.U 
    val dec = io.mem_write_enable && io.mem_write_address === i.U 
    when(inc){
      mem_pending(i) := mem_pending(i) + io.mem_issue_count - Mux(dec, 1.U,0.U)
    }.elsewhen(!inc && dec){
      mem_pending(i) := mem_pending(i) - 1.U
    }
  
  }

  // when(io.mem_issue)        { printf("PEND+ rd=%d\n", io.mem_issue_rd) }
  // when(io.mem_write_enable) { printf("PEND- rd=%d\n", io.mem_rd) }

||||||| 6fe8822
  
  when(io.mem_wen){
    // printf("WRITING MEM: rd: %d   val: %d", io.mem_rd, io.mem_write_data )
  }
  when(io.instruction.valid || io.mem_write_enable){
    when(io.instruction.valid && io.instruction.bits.opcode === "b0000011".U){
      mem_rum_w := mem_rum | (1.U(32.W) << io.instruction.bits.rd)
    }
    mem_rum_w2 := mem_rum_w
    when(io.mem_write_enable){
      mem_rum_w2 := mem_rum_w & ~(1.U(32.W) << io.mem_rd)
    }
  }
  mem_rum := mem_rum_w2
  io.reg_mem_rum := mem_rum

// when(io.mem_rd === 8.U){
//   printf("\n\n8 recieved 8 recieved\n\n")
// }

//check if its the current oSne in the stage if it is replace, otherwise pipe through

=======
  when(io.instruction.valid || io.mem_write_enable){
    when(io.instruction.valid && io.instruction.bits.opcode === "b0000011".U){
      mem_rum_w := mem_rum | (1.U(32.W) << io.instruction.bits.rd)
    }
    mem_rum_w2 := mem_rum_w
    when(io.mem_write_enable){
      mem_rum_w2 := mem_rum_w & ~(1.U(32.W) << io.mem_rd)
    }
  }
  mem_rum := mem_rum_w2
  io.reg_mem_rum := mem_rum
>>>>>>> origin/warps
}