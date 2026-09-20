package RISCV


import chisel3._
import chisel3.util._

import _root_.circt.stage.ChiselStage
import scala.math._

class Core(cfg : GpuConfig) extends Module {
    val io = IO(new Bundle {
        val execute = Input(Bool())

		val allocate_warps = Input(Bool())
        val warp_count = Input(UInt(32.W))

		val complete = Output(Bool())

        val icache_req = Output(new MemReq)
        val icache_start = Output(Bool())
        val icache_ready = Input(Bool())
        val icache_valid = Input(Bool())
        val icache_data = Input(UInt(32.W))

        val dcache_req = Output(new MemReq)
        val dcache_start = Output(Bool())
        val dcache_ready = Input(Bool())
        val dcache_valid = Input(Bool())
        val dcache_data = Input(UInt(32.W))
        val dcache_rd = Output(UInt(7.W))
        val dcache_lane = Output(UInt(log2Up(cfg.nLanes).max(1).W))
        val dcache_wen = Output(Bool())

        val mem_rd = Input(UInt(7.W))
        val mem_lane = Input(UInt(log2Up(cfg.nLanes).max(1).W))
        val mem_wen = Input(Bool())
    })

    val registers = Module(new Registers(cfg))
    registers.io.read_address_a := 0.U(5.W)
    registers.io.read_address_b := 0.U(5.W)
    val warp_scheduler = Module(new WarpScheduler())
    val fetch = Module(new Fetch())

    val decode = Module(new Decode(cfg))
    val read = Module(new Read(cfg))
    val execute = Module(new Execute(cfg))
    val writeback = Module(new Writeback(cfg))
    val lsu = Module(new LSU(cfg))


    val raw_stall = read.io.raw_hazard_stall
    val memory_stall = execute.io.memory_stall
    val jump_flush = execute.io.jump_flush
    val warp_swap_flush = warp_scheduler.io.warp_swap_flush

    val fetch_stall = raw_stall || memory_stall || !io.execute
    val fetch_stall_prev = RegNext(fetch_stall, true.B)
    val fetch_op = Mux(warp_swap_flush, FetchOp.WS, Mux(jump_flush, FetchOp.RD, Mux(fetch_stall, FetchOp.ST, Mux(false.B, FetchOp.ST, FetchOp.DQ))))

	warp_scheduler.io.execute := io.execute
	warp_scheduler.io.warp_swap := execute.io.warp_swap
	warp_scheduler.io.warp_terminate := execute.io.warp_terminate
	warp_scheduler.io.allocate_warps := io.allocate_warps
	warp_scheduler.io.warp_count := io.warp_count
	io.complete := warp_scheduler.io.complete

    fetch.io.execute := io.execute
    fetch.io.active_warp := warp_scheduler.io.active_warp
	fetch.io.mark := execute.io.mark
	fetch.io.mark_pc := execute.io.mark_pc
	fetch.io.mark_warp := execute.io.mark_warp
	fetch.io.allocate_warp := warp_scheduler.io.allocate_warp
	fetch.io.allocate_id := warp_scheduler.io.allocate_id
    fetch.io.fetch_request.fetch_op := fetch_op
    fetch.io.fetch_request.redirect_addr := execute.io.pc_redirect.bits
    fetch.io.icache_ready := io.icache_ready
    fetch.io.icache_valid := io.icache_valid
    fetch.io.icache_data := io.icache_data
    
	io.icache_start := fetch.io.icache_start
	io.icache_req := fetch.io.icache_req
    io.icache_start := fetch.io.icache_start
	
    decode.io.fetch_result := fetch.io.fetch_result
    decode.io.flush := jump_flush || warp_swap_flush
    decode.io.stall := fetch_stall
	decode.io.active_warp := warp_scheduler.io.active_warp

	val register_use_map = (execute.io.next_instruction.valid.asUInt << execute.io.next_instruction.bits.rd) |
          (read.io.next_instruction.valid.asUInt << read.io.next_instruction.bits.rd) |
          (writeback.io.write_enable.asUInt << writeback.io.write_address) |
          writeback.io.reg_mem_rum

    read.io.instruction := decode.io.decoded
    read.io.register_value_a := registers.io.out_a
    read.io.register_value_b := registers.io.out_b
    read.io.flush := jump_flush || warp_swap_flush
    read.io.stall := memory_stall
    read.io.rum := register_use_map

    execute.io.instruction := read.io.next_instruction

    execute.io.flush := RegNext(jump_flush)
    execute.io.stall := false.B
    execute.io.lsu_req <> lsu.io.req



    io.dcache_req := lsu.io.dcache_req
    io.dcache_start := lsu.io.dcache_start
    lsu.io.dcache_ready := io.dcache_ready
    io.dcache_rd := lsu.io.dcache_rd
    io.dcache_lane := lsu.io.dcache_lane
    io.dcache_wen := lsu.io.dcache_wen

    writeback.io.instruction := execute.io.next_instruction
    writeback.io.mem_write_data := VecInit(Seq.fill(cfg.nLanes)(io.dcache_data))
    writeback.io.mem_rd := io.mem_rd
    writeback.io.mem_wen := io.mem_wen
    registers.io.write_mask2 := writeback.io.mem_write_mask 
    registers.io.write_mask := writeback.io.write_mask
    

    writeback.io.mem_mask :=  UIntToOH(io.mem_lane,cfg.nLanes)
    writeback.io.mem_issue := execute.io.mem_issue
    writeback.io.mem_issue_rd := execute.io.mem_issue_rd
    writeback.io.mem_issue_count := execute.io.mem_issue_count

	registers.io.read_address_a := read.io.register_read_a
    registers.io.read_address_b := read.io.register_read_b
    registers.io.read_enable := read.io.register_read_enable
    registers.io.write_enable := writeback.io.write_enable
    registers.io.write_address := writeback.io.write_address
    registers.io.in := writeback.io.write_val

    registers.io.write_enable2 := writeback.io.mem_write_enable
    registers.io.write_address2 := writeback.io.mem_write_address
    registers.io.in2 := writeback.io.mem_write_val

    execute.io.warp_ids := warp_scheduler.io.warp_ids_out
}

// object Core extends App {
//     ChiselStage.emitSystemVerilogFile(
//       new Core(),
//       firtoolOpts = Array(
//         "-disable-all-randomization",
//         "-strip-debug-info",
//         "-default-layer-specialization=enable"
//       ),
//       args = Array("--target-dir", "generated")
//     )
// }
