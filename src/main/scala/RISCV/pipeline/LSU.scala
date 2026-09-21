package RISCV
import chisel3._
import _root_.circt.stage.ChiselStage
import scala.math._
import chisel3.util._


class VecMemReq(cfg: GpuConfig) extends Bundle {
  val base = Vec(cfg.nLanes, UInt(32.W))  
  val wdata = Vec(cfg.nLanes, UInt(32.W))  
  val imm = UInt(32.W)
  val mask = UInt(cfg.nLanes.W)
  val rd = UInt(7.W)
  val func3 = UInt(3.W)
  val write = Bool()
}

class LSU(cfg: GpuConfig) extends Module {
  val laneW = log2Up(cfg.nLanes).max(1)

  val io = IO(new Bundle {
    val req = Flipped(Decoupled(new VecMemReq(cfg)))

    val dcache_req  = Output(new MemReq)
    val dcache_start = Output(Bool())
    val dcache_ready = Input(Bool())
    val dcache_rd = Output(UInt(7.W))
    val dcache_lane  = Output(UInt(laneW.W))
    val dcache_wen  = Output(Bool())
    val busy = Output(Bool())          
  })



  val q = Queue(io.req, 2)
  val lane = RegInit(0.U(log2Up(cfg.nLanes + 1).W))

  val creq = q.bits
  val active = creq.mask(lane)
  val last = lane === (cfg.nLanes - 1).U

  io.dcache_req.address := creq.base(lane) + creq.imm
  io.dcache_req.write_data := creq.wdata(lane)
  io.dcache_req.read := !creq.write
  io.dcache_req.write := creq.write
  io.dcache_req.op := Mux(creq.write,
    MuxLookup(creq.func3, MemOp.SW)(Seq(
      "b000".U -> MemOp.SB,
      "b001".U -> MemOp.SH,
      "b010".U -> MemOp.SW)),
    MuxLookup(creq.func3, MemOp.LW)(Seq(
      "b000".U -> MemOp.LB,
      "b001".U -> MemOp.LH,
      "b010".U -> MemOp.LW,
      "b100".U -> MemOp.LBU,
      "b101".U -> MemOp.LHU)))


  io.dcache_rd := Mux(creq.write, 0.U, creq.rd)
  io.dcache_wen := !creq.write
  io.dcache_lane := lane(laneW - 1, 0)

  io.dcache_start := q.valid && active && io.dcache_ready
  val step = q.valid && (!active || io.dcache_ready)

  q.ready := false.B
  when(step) {
    when(last) {
      lane := 0.U
      q.ready := true.B         
    }.otherwise {
      lane := lane + 1.U
    }
  }

  io.busy := q.valid
}