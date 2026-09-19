package RISCV


import chisel3._
import chisel3.util._

import _root_.circt.stage.ChiselStage
import scala.math._

class Core() extends Module {
    val io = IO(new Bundle {
        val execute = Input(Bool())

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
        val dcache_rd = Output(UInt(5.W))
        val dcache_wen = Output(Bool())

        val mem_rd = Input(UInt(5.W))
        val mem_wen = Input(Bool())
    })

	val warp_scheduler = Module(new WarpScheduler())
    val registers = Module(new Registers())
    val fetch = Module(new Fetch())
    val decode = Module(new Decode())
    val read = Module(new Read())
    val execute = Module(new Execute())
    val writeback = Module(new Writeback())

    val raw_stall = read.io.raw_hazard_stall
    val memory_stall = execute.io.memory_stall
    val jump_flush = execute.io.jump_flush
    val warp_swap_flush = warp_scheduler.io.warp_swap_flush

    val fetch_stall = raw_stall || memory_stall || !io.execute
    val fetch_stall_prev = RegNext(fetch_stall, true.B)
    val fetch_op = Mux(warp_swap_flush, FetchOp.WS, Mux(jump_flush, FetchOp.RD, Mux(fetch_stall, FetchOp.ST, Mux(false.B, FetchOp.ST, FetchOp.DQ))))

	warp_scheduler.io.warp_swap := execute.io.warp_swap

    fetch.io.execute := io.execute
    fetch.io.active_warp := warp_scheduler.io.active_warp
	fetch.io.mark := writeback.io.mark
	fetch.io.mark_pc := writeback.io.mark_pc
	fetch.io.mark_warp := writeback.io.mark_warp
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

    execute.io.dcache_ready := io.dcache_ready
    execute.io.dcache_valid := io.dcache_valid
    execute.io.dcache_data := io.dcache_data

    io.dcache_rd := execute.io.dcache_rd
    io.dcache_wen := execute.io.dcache_wen
	io.dcache_start := execute.io.dcache_start
	io.dcache_req := execute.io.dcache_req

    writeback.io.instruction := execute.io.next_instruction
    writeback.io.mem_write_data := io.dcache_data
    writeback.io.mem_rd := io.mem_rd
    writeback.io.mem_wen := io.mem_wen

	registers.io.read_address_a := read.io.register_read_a
    registers.io.read_address_b := read.io.register_read_b
    registers.io.write_enable := writeback.io.write_enable
    registers.io.write_address := writeback.io.write_address
    registers.io.in := writeback.io.write_val
    registers.io.write_enable2  := writeback.io.mem_write_enable
    registers.io.write_address2 := writeback.io.mem_write_address
    registers.io.in2 := writeback.io.mem_write_val
}

object Core extends App {
    ChiselStage.emitSystemVerilogFile(
      new Core(),
      firtoolOpts = Array(
        "-disable-all-randomization",
        "-strip-debug-info",
        "-default-layer-specialization=enable"
      ),
      args = Array("--target-dir", "generated")
    )
}
