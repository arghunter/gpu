package RISCV

import chisel3._
import _root_.circt.stage.ChiselStage

/* 
 * The register file module for RISC-V
 * 32 registers, each 32 bits wide
 * Dual read ports, single write port
 * Register x0 is hardwired to 0
 * 
 * This register file supports a simultaneous combinational read from two registers via the two read addresses and output ports
 * as well as a synchronous write to one register on the rising edge of the clock when write_enable is high.
 * 
 * I/O:
    * in: 32-bit input data to write to register
    * write_address: 5-bit address of register to write to
    * read_address_a: 5-bit address of register to read from (port A)
    * read_address_b: 5-bit address of register to read from (port B)
    * write_enable: boolean signal to enable writing to register
    * out_a: 32-bit output data from read port A
    * out_b: 32-bit output data from read port B
 *
 */

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

    // Dual read ports
    io.out_a := (regs(io.read_address_a))
    io.out_b := (regs(io.read_address_b))

    //printf("Regs: [%d]=%d, [%d]=%d, WE=%b, WA=%d, IN=%d\n", io.read_address_a, io.out_a, io.read_address_b, io.out_b, io.write_enable, io.write_address, io.in)

    when (io.write_enable && (io.write_address =/= 0.U)) {
        regs(io.write_address) := io.in
    }
    when (io.write_enable2 && (io.write_address2 =/= 0.U) && !(io.write_enable&&io.write_address === io.write_address2)) {
        regs(io.write_address2) := io.in2
    }

  // val REG_COUNT = 32

  // val bank_a = SyncReadMem(REG_COUNT, UInt(32.W))
  // val bank_b = SyncReadMem(REG_COUNT, UInt(32.W))

  // when(io.write_enable && io.write_address =/= 0.U) {
  //   bank_a.write(io.write_address, io.in)
  //   bank_b.write(io.write_address, io.in)
  // }

  // val raw_a = bank_a.read(io.read_address_a, true.B)
  // val raw_b = bank_b.read(io.read_address_b, true.B)

  // io.out_a := Mux(RegNext(io.read_address_a) === 0.U, 0.U, raw_a)
  // io.out_b := Mux(RegNext(io.read_address_b) === 0.U, 0.U, raw_b)
}