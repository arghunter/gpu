package RISCV

import chisel3._
import chisel3.util._
import _root_.circt.stage.ChiselStage
import scala.math._

class WarpScheduler() extends Module {
    val io = IO(new Bundle {
        val active_warp = Output(UInt(2.W))

        val warp_swap = Input(Bool())

        val warp_swap_flush = Output(Bool())
    })

	val active_warp = RegInit(0.U(2.W))
	val active_warps = RegInit(VecInit(Seq.fill(4.toInt)(false.B)))
	active_warps(0) := true.B

	io.active_warp := active_warp

	io.warp_swap_flush := false.B

	when(io.warp_swap) {
		printf("Swapped warp due to warp swap request! Current Warp: %d\n", active_warp)

		io.warp_swap_flush := true.B
		active_warp := active_warp + 1.U
	}

	when(!active_warps(active_warp)) {
		printf("Swapped warp due inactive warp! Current Warp: %d\n", active_warp)

		io.warp_swap_flush := true.B
		active_warp := active_warp + 1.U
	}
}