package RISCV

import chisel3._
import _root_.circt.stage.ChiselStage

class Registers(cfg: GpuConfig) extends Module {
  val io = IO(new Bundle {
    val write_enable = Input(Bool())
    val write_address = Input(UInt(7.W))
    val write_mask = Input(UInt(cfg.nLanes.W))
    val in = Input(Vec(cfg.nLanes,UInt(32.W)))
    val write_enable2  = Input(Bool())
    val write_address2 = Input(UInt(7.W))
    val write_mask2 = Input(UInt(cfg.nLanes.W))
    val in2  = Input(Vec(cfg.nLanes,UInt(32.W)))
    val read_address_a = Input(UInt(7.W))
    val read_address_b = Input(UInt(7.W))
    val out_a = Output(Vec(cfg.nLanes,UInt(32.W)))
    val out_b = Output(Vec(cfg.nLanes,UInt(32.W)))

  })

    // val regs = RegInit(VecInit(Seq.fill(32.toInt)(0.U(32.W))))
    val regs = RegInit(0.U.asTypeOf(Vec(128, Vec(cfg.nLanes, UInt(32.W)))))


    // Dual read ports
    io.out_a := (regs(io.read_address_a))
    io.out_b := (regs(io.read_address_b))



    val w1= io.write_enable && io.write_address =/= 0.U && (io.write_address =/= 32.U) && (io.write_address =/= 64.U) && (io.write_address =/= 96.U)
    val w2 = io.write_enable2 && io.write_address2 =/= 0.U && (io.write_address2 =/= 32.U) && (io.write_address2 =/= 64.U) && (io.write_address2 =/= 96.U)
    val same = io.write_address === io.write_address2

    for (i<-0 until cfg.nLanes) {
      when(w1 && io.write_mask(i)){
        regs(io.write_address)(i) := io.in(i)
      }
      when(w2 && io.write_mask2(i)&& !(w1 && same && io.write_mask(i))) {
        regs(io.write_address2)(i) := io.in2(i)
      }
    }
}