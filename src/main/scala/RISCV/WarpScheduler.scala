package RISCV

import chisel3._
import chisel3.util._
import _root_.circt.stage.ChiselStage
import scala.math._

class WarpScheduler() extends Module {
    val io = IO(new Bundle {
        val active_warp = Output(UInt(2.W))
        val active_pc = Output(UInt(32.W))

        val next_pc = Input(UInt(32.W))
    })

	val active_warp = RegInit(0.U(2.W))

	io.active_warp := active_warp
	
	val warp_instruction_pointers = RegInit(VecInit(Seq.fill(4.toInt)(0.U(32.W))))

	io.active_pc := warp_instruction_pointers(active_warp)
	warp_instruction_pointers(active_warp) := io.next_pc
}