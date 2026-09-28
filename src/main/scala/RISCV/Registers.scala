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

    
    val sel_a_now = lvt(io.read_address_a)
    val sel_b_now = lvt(io.read_address_b)

    val sel_a = RegEnable(sel_a_now, 0.U(cfg.nLanes.W), io.read_enable)
    val sel_b = RegEnable(sel_b_now, 0.U(cfg.nLanes.W), io.read_enable)
    val a_x0 = RegEnable(is_x0(io.read_address_a), true.B, io.read_enable)
    val b_x0 = RegEnable(is_x0(io.read_address_b), true.B, io.read_enable)

    for (i <- 0 until cfg.nLanes) {
      val wr1 = w1 && mask1(i)
      val wr2 = w2 && mask2(i)
      val banks = Seq(bank0(i), bank1(i))

      val p0 = Seq(0, 1).map { b =>
        val hit = if (b == 1) sel_a_now(i) else !sel_a_now(i)
        val wr  = wr1 && !hit
        banks(b).readWrite(Mux(wr, io.write_address, io.read_address_a), io.in(i),
          (io.read_enable && hit) || wr, wr)
      }
      val p1 = Seq(0, 1).map { b =>
        val hit = if (b == 1) sel_b_now(i) else !sel_b_now(i)
        val wr  = wr2 && !hit
        banks(b).readWrite(Mux(wr, io.write_address2, io.read_address_b), io.in2(i),
          (io.read_enable && hit) || wr, wr)
      }

      io.out_a(i) := Mux(a_x0, 0.U, Mux(sel_a(i), p0(1), p0(0)))
      io.out_b(i) := Mux(b_x0, 0.U, Mux(sel_b(i), p1(1), p1(0)))
    }

    
    val v1 = ~sel_a_now
    val v2 = ~sel_b_now
    val m2_at_1 = Mux(w2 && same, mask2, 0.U)

    when(w1) {
      lvt(io.write_address) := (lvt(io.write_address) & ~mask1 & ~m2_at_1) | (v1 & mask1) | (v2 & m2_at_1)
    }
    when(w2 && !(w1 && same)) {
      lvt(io.write_address2) := (lvt(io.write_address2) & ~mask2) | (v2 & mask2)
    }
}
