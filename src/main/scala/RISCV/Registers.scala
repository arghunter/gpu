package RISCV

import chisel3._
import chisel3.util._
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
    val read_enable = Input(Bool())
    val read_address_a = Input(UInt(7.W))
    val read_address_b = Input(UInt(7.W))
    val out_a = Output(Vec(cfg.nLanes,UInt(32.W)))
    val out_b = Output(Vec(cfg.nLanes,UInt(32.W)))

  })

    def is_x0(a: UInt): Bool = a(4, 0) === 0.U

    val bank0 = Seq.fill(cfg.nLanes)(SyncReadMem(128, UInt(32.W)))
    val bank1 = Seq.fill(cfg.nLanes)(SyncReadMem(128, UInt(32.W)))
    val lvt   = RegInit(VecInit(Seq.fill(128)(0.U(cfg.nLanes.W))))

    val w1 = io.write_enable && !is_x0(io.write_address)
    val w2 = io.write_enable2 && !is_x0(io.write_address2)
    val same = io.write_address === io.write_address2
    val mask1 = io.write_mask
    val mask2 = Mux(w1 && same, io.write_mask2 & ~io.write_mask, io.write_mask2)

    for (i <- 0 until cfg.nLanes) {
      when(w1 && mask1(i)) { bank0(i).write(io.write_address, io.in(i)) }
      when(w2 && mask2(i)) { bank1(i).write(io.write_address2, io.in2(i)) }
    }

    when(w1) {
      lvt(io.write_address) := (lvt(io.write_address) & ~mask1) | Mux(w2 && same, mask2, 0.U)
    }
    when(w2 && !(w1 && same)) {
      lvt(io.write_address2) := lvt(io.write_address2) | mask2
    }

    val sel_a = RegEnable(lvt(io.read_address_a), 0.U(cfg.nLanes.W), io.read_enable)
    val sel_b = RegEnable(lvt(io.read_address_b), 0.U(cfg.nLanes.W), io.read_enable)
    val a_x0 = RegEnable(is_x0(io.read_address_a), true.B, io.read_enable)
    val b_x0 = RegEnable(is_x0(io.read_address_b), true.B, io.read_enable)

    for (i <- 0 until cfg.nLanes) {
      io.out_a(i) := Mux(a_x0, 0.U, Mux(sel_a(i),
        bank1(i).read(io.read_address_a, io.read_enable),
        bank0(i).read(io.read_address_a, io.read_enable)))
      io.out_b(i) := Mux(b_x0, 0.U, Mux(sel_b(i),
        bank1(i).read(io.read_address_b, io.read_enable),
        bank0(i).read(io.read_address_b, io.read_enable)))
    }
}
