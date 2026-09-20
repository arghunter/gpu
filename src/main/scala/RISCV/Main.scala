package RISCV

import chisel3._
import _root_.circt.stage.ChiselStage
import scala.math._
import chisel3.util._

case class GpuConfig(nLanes: Int = 1)


class Main(lineWidth: Int = 512) extends Module {
    val io = IO(new Bundle {
		val execute = Input(Bool())

		val allocate_warps = Input(Bool())
        val warp_count = Input(UInt(32.W))

		val complete = Output(Bool())

		val vga_clk = Input(Clock())
		val hsync = Output(Bool())
		val vsync = Output(Bool())
		val rgb = Output(UInt(24.W))
		val blanking = Output(Bool())

		val mem_req   = Decoupled(new MemLineReq(lineWidth))   
		val mem_resp  = Input(UInt(lineWidth.W))
		val mem_valid = Input(Bool()) 

		val rxd = Input(Bool())
		val txd = Output(Bool())
    })

    val gpucfg = GpuConfig(16)
    val memory = Module(new MemoryWrapper(lineWidth, cfg = gpucfg))
    val core = Module(new Core(gpucfg))

    memory.io.icache_req := core.io.icache_req
    memory.io.icache_start := core.io.icache_start
    core.io.icache_ready := memory.io.icache_ready
    core.io.icache_valid := memory.io.icache_valid
    core.io.icache_data := memory.io.icache_data

    memory.io.dcache_req := core.io.dcache_req
    memory.io.dcache_start := core.io.dcache_start
    core.io.dcache_ready := memory.io.dcache_ready
    core.io.dcache_valid := memory.io.dcache_valid
    core.io.dcache_data := memory.io.dcache_data
    memory.io.dcache_rd := core.io.dcache_rd
    memory.io.dcache_lane := core.io.dcache_lane
    memory.io.dcache_wen := core.io.dcache_wen 

    core.io.execute := io.execute
	core.io.allocate_warps := io.allocate_warps
	core.io.warp_count := io.warp_count
	io.complete := core.io.complete

    io.mem_req       <> memory.io.mem_req
    memory.io.mem_resp := io.mem_resp
    memory.io.mem_valid := io.mem_valid
    core.io.mem_rd := memory.io.dcache_rd_out
    core.io.mem_lane := memory.io.dcache_lane_out
    core.io.mem_wen := memory.io.dcache_wen_out

    memory.io.rxd := io.rxd
    io.txd := memory.io.txd

    val vga_controller = Module(new VGAController())
    vga_controller.io.address := memory.io.address_vga
    vga_controller.io.write := memory.io.write_vga
    vga_controller.io.write_value := memory.io.write_value_vga
    vga_controller.io.read_clk := io.vga_clk
    io.hsync := vga_controller.io.hsync
    io.vsync := vga_controller.io.vsync
    io.rgb := vga_controller.io.rgb
    io.blanking := vga_controller.io.blanking
    vga_controller.io.switch := memory.io.switch
}

object Main extends App {
    ChiselStage.emitSystemVerilogFile(
      new Main(),
      firtoolOpts = Array(
        "-disable-all-randomization",
        "-strip-debug-info",
        "-default-layer-specialization=enable"
      ),
      args = Array("--target-dir", "generated")
    )
}