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

        val warp_ids_out = Output(Vec(4, UInt(32.W)))

        val warp_swap = Input(Bool())
        val warp_terminate = Input(Bool())

        val warp_swap_flush = Output(Bool())



				val allocate_warp = Output(Bool())
				val allocate_id = Output(UInt(2.W))
				val allocate_pc = Output(UInt(32.W))

        val complete = Output(Bool())

				val spawn = Input(Bool())
				val spawn_count = Input(UInt(32.W))
				val spawn_pc_in = Input(UInt(32.W))

				val barrier = Input(Bool())
				val barrier_target = Input(UInt(32.W))
				val lsu_busy = Input(Bool())
    })

	val active_warp = RegInit(0.U(2.W))
	val warp_ids = RegInit(VecInit(Seq.fill(4.toInt)(0.U(32.W))))
	val active_warps = RegInit(VecInit(true.B, false.B, false.B, false.B))
  val warp_count = RegInit(1.U(32.W))
  val next_warp = RegInit(1.U(32.W))
  val spawn_pc = RegInit(0.U(32.W))

  val barrier_waiting = RegInit(VecInit(Seq.fill(4)(false.B)))
  val barrier_count = RegInit(0.U(3.W))
  val barrier_target = RegInit(0.U(32.W))

  when(io.spawn) {
    warp_count := io.spawn_count
    spawn_pc   := io.spawn_pc_in
  }

	
	io.complete := next_warp === warp_count && !active_warps(0.U) && !active_warps(1.U) && !active_warps(2.U) && !active_warps(3.U)

	io.active_warp := active_warp
	io.active_warp_id := warp_ids(active_warp)
	io.warp_ids_out := warp_ids

	io.warp_swap_flush := false.B

	io.allocate_warp := false.B
	io.allocate_id := 0.U
  io.allocate_pc := 0.U

	when(io.execute) {
		when(next_warp < warp_count) {
			val free = (~active_warps.asUInt).asUInt
			val slot = PriorityEncoder(free)
			when(next_warp < warp_count && free.orR) {
				active_warps(slot) := true.B
				warp_ids(slot) := next_warp
				barrier_waiting(slot) := false.B
				next_warp := next_warp + 1.U
				io.allocate_warp := true.B
				io.allocate_id := slot
				io.allocate_pc := spawn_pc
			}
		}

		val reached = (barrier_count + io.barrier.asUInt) >= barrier_target && barrier_target =/= 0.U
		when(reached && !io.lsu_busy) {
			barrier_count  := 0.U
			barrier_target := 0.U
			for (i <- 0 until 4) barrier_waiting(i) := false.B
		}.elsewhen(io.barrier) {
			barrier_count  := barrier_count + 1.U
			barrier_target := io.barrier_target
			barrier_waiting(active_warp) := true.B
		}

		when(io.warp_swap) {
			// printf("Swapped warp due to warp swap request! Current Warp: %d\n", active_warp)

			when(io.warp_terminate) {
				printf("Warp terminated!\n")

				active_warps(active_warp) := false.B
			}

			io.warp_swap_flush := true.B
			active_warp := active_warp + 1.U
		}

		when(!active_warps(active_warp) || barrier_waiting(active_warp)) {
			// printf("Swapped warp due inactive warp! Current Warp: %d\n", active_warp)

			io.warp_swap_flush := true.B
			active_warp := active_warp + 1.U
		}
	}
}