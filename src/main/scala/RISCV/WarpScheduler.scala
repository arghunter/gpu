package RISCV

import chisel3._
import chisel3.util._
import _root_.circt.stage.ChiselStage
import scala.math._

class WarpScheduler() extends Module {
    val io = IO(new Bundle {
		val execute = Input(Bool())

        val active_warp = Output(UInt(2.W))
        val active_warp_id = Output(UInt(32.W))

        val warp_swap = Input(Bool())
        val warp_terminate = Input(Bool())

        val warp_swap_flush = Output(Bool())

        val allocate_warps = Input(Bool())
        val warp_count = Input(UInt(32.W))

		val allocate_warp = Output(Bool())
		val allocate_id = Output(UInt(2.W))

        val complete = Output(Bool())
    })

	val active_warp = RegInit(0.U(2.W))
	val active_warps = RegInit(VecInit(Seq.fill(4.toInt)(false.B)))
	val warp_ids = RegInit(VecInit(Seq.fill(4.toInt)(0.U(32.W))))

	val warp_count = RegInit(0.U(32.W))
	val next_warp = RegInit(0.U(32.W))

	when(io.allocate_warps) {
		warp_count := io.warp_count
		next_warp := 0.U

		for(i <- 0 until 4) {
			active_warps(i.U) := false.B
			warp_ids(i.U) := 0.U
		}

		printf("Allocating %d warps!\n", io.warp_count)
	}

	io.complete := next_warp === warp_count && !active_warps(0.U) && !active_warps(1.U) && !active_warps(2.U) && !active_warps(3.U)

	io.active_warp := active_warp
	io.active_warp_id := warp_ids(active_warp)

	io.warp_swap_flush := false.B

	io.allocate_warp := false.B
	io.allocate_id := 0.U

	when(io.execute) {
		when(next_warp < warp_count) {
			when(!active_warps(0.U)) {
				active_warps(0.U) := true.B
				warp_ids(0.U) := next_warp

				next_warp := next_warp + 1.U

				io.allocate_warp := true.B
				io.allocate_id := 0.U

				printf("Launching warp %d at index 0!\n", next_warp)
			}.elsewhen(!active_warps(1.U)) {
				active_warps(1.U) := true.B
				warp_ids(1.U) := next_warp

				next_warp := next_warp + 1.U

				io.allocate_warp := true.B
				io.allocate_id := 1.U

				printf("Launching warp %d at index 1!\n", next_warp)
			}.elsewhen(!active_warps(2.U)) {
				active_warps(2.U) := true.B
				warp_ids(2.U) := next_warp

				next_warp := next_warp + 1.U

				io.allocate_warp := true.B
				io.allocate_id := 2.U

				printf("Launching warp %d at index 2!\n", next_warp)
			}.elsewhen(!active_warps(3.U)) {
				active_warps(3.U) := true.B
				warp_ids(3.U) := next_warp

				next_warp := next_warp + 1.U

				io.allocate_warp := true.B
				io.allocate_id := 3.U

				printf("Launching warp %d at index 3!\n", next_warp)
			}
		}

		when(io.warp_swap) {
			printf("Swapped warp due to warp swap request! Current Warp: %d\n", active_warp)

			when(io.warp_terminate) {
				printf("Warp terminated!\n")

				active_warps(active_warp) := false.B
			}

			io.warp_swap_flush := true.B
			active_warp := active_warp + 1.U
		}

		when(!active_warps(active_warp)) {
			printf("Swapped warp due inactive warp! Current Warp: %d\n", active_warp)

			io.warp_swap_flush := true.B
			active_warp := active_warp + 1.U
		}
	}
}