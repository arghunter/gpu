package RISCV

import chisel3._
import chisel3.util._
import _root_.circt.stage.ChiselStage
import scala.math._

class WarpScheduler() extends Module {
    val io = IO(new Bundle {
        val active_warp = Output(UInt(2.W))
    })

	val active_warp = RegInit(0.U(2.W))
	val warp_enabled = RegInit(VecInit(Seq.fill(4.toInt)(true.B)))

	io.active_warp := active_warp
}