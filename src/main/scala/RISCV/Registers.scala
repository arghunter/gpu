package RISCV

import chisel3._
import _root_.circt.stage.ChiselStage

class Registers() extends Module {
	val io = IO(new Bundle {
		val write_enable   = Input(Bool())
		val write_address  = Input(UInt(7.W))
		val in             = Input(UInt(32.W))
		val write_enable2   = Input(Bool())
		val write_address2  = Input(UInt(7.W))
		val in2            = Input(UInt(32.W))
		val read_address_a = Input(UInt(7.W))
		val read_address_b = Input(UInt(7.W))
		val out_a          = Output(UInt(32.W))
		val out_b          = Output(UInt(32.W))
	})

    val regs = RegInit(VecInit(Seq.fill(128.toInt)(0.U(32.W))))

    io.out_a := regs(io.read_address_a)
    io.out_b := regs(io.read_address_b)

    when (io.write_enable && (io.write_address =/= 0.U) && (io.write_address =/= 32.U) && (io.write_address =/= 64.U) && (io.write_address =/= 96.U)) {
        regs(io.write_address) := io.in
    }

    when (io.write_enable2 && (io.write_address2 =/= 0.U) && (io.write_address2 =/= 32.U) && (io.write_address2 =/= 64.U) && (io.write_address2 =/= 96.U) && !(io.write_enable && io.write_address === io.write_address2)) {
        regs(io.write_address2) := io.in2
    }
}