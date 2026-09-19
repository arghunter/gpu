package RISCV

import chisel3._
import chisel3.util._
import _root_.circt.stage.ChiselStage


class ALU(val width: Int = 32) extends Module {
    val io = IO(new Bundle {
        val func7 = Input(UInt(7.W));
        val func3 = Input(UInt(3.W));
        val isR = Input(Bool()); // opcode is 0110011; on an I-type op func7 is really imm[11:5]
        // val isM = Input(Bool());
        val a = Input(UInt(width.W)); // First operand
        val b = Input(UInt(width.W)); // Second operand
        val output = Output(UInt(width.W)); // Result of the operation
    })
    io.output := 0.U;
    val i_alu = Wire(UInt(width.W));
    i_alu := 0.U;


  



    val a_s = io.a.asSInt
    val b_s = io.b.asSInt

    val sh = io.b(4, 0)
    val ish = (32.U - sh)(4, 0)
    val rotr = (io.a >> sh) | (io.a << ish)(31, 0)
    val rotl = (io.a << sh)(31, 0) | (io.a >> ish)
    val orcb = Cat(Fill(8, io.a(31,24).orR), Fill(8, io.a(23,16).orR),
                   Fill(8, io.a(15, 8).orR), Fill(8, io.a( 7, 0).orR))
    val rev8 = Cat(io.a(7,0), io.a(15,8), io.a(23,16), io.a(31,24))
    
    when(io.isR && io.func7 === "b0000101".U){
        switch(io.func3){
            //min
            is("b100".U) {
                i_alu := Mux(io.a.asSInt < io.b.asSInt,io.a,io.b)
            }
            //max
            is("b110".U) {
                i_alu := Mux(io.a.asSInt > io.b.asSInt,io.a,io.b)
            }
            //minu
            is("b101".U) {
                i_alu := Mux(io.a < io.b,io.a,io.b)
            }
            //maxu
            is("b111".U) {
                i_alu := Mux(io.a > io.b,io.a,io.b)
            }
        }
    }.elsewhen(io.isR && io.func7 === "b0100000".U && io.func3 =/= "b000".U && io.func3 =/= "b101".U){
        switch(io.func3){
            //andn
            is("b111".U) { i_alu := io.a & (~io.b).asUInt }
            //orn
            is("b110".U) { i_alu := io.a | (~io.b).asUInt }
            //xnor
            is("b100".U) { i_alu := (~(io.a ^ io.b)).asUInt }
        }
    }.elsewhen(io.isR && io.func7 === "b0000100".U && io.func3 === "b100".U){
        //zext.h
        i_alu := Cat(0.U(16.W), io.a(15, 0))
    }.elsewhen(io.func7 === "b0110000".U && (io.func3 === "b001".U || io.func3 === "b101".U)){
        when(io.func3 === "b101".U){
            //ror, rori
            i_alu := rotr
        }.elsewhen(io.isR){
            //rol
            i_alu := rotl
        }.otherwise{
            switch(sh){
                //clz
                is(0.U) { i_alu := Mux(io.a === 0.U, 32.U, PriorityEncoder(Reverse(io.a))) }
                //ctz
                is(1.U) { i_alu := Mux(io.a === 0.U, 32.U, PriorityEncoder(io.a)) }
                //cpop
                is(2.U) { i_alu := PopCount(io.a) }
                //sext.b
                is(4.U) { i_alu := Cat(Fill(24, io.a(7)), io.a(7, 0)) }
                //sext.h
                is(5.U) { i_alu := Cat(Fill(16, io.a(15)), io.a(15, 0)) }
            }
        }
    }.elsewhen(!io.isR && io.func3 === "b101".U && io.func7 === "b0110100".U){
        i_alu := rev8
    }.elsewhen(!io.isR && io.func3 === "b101".U && io.func7 === "b0010100".U){
        i_alu := orcb
    }.otherwise{
        switch(io.func3){
            is("b000".U){
                i_alu := io.a + io.b

            }
            //SLLI
            is("b001".U){
                i_alu := io.a << io.b(4,0) 
        
            }
            //SLTI
            is("b010".U){
                i_alu := Mux(io.a.asSInt < io.b.asSInt, 1.U, 0.U)
            }
            //SLTIU
            is("b011".U){
                i_alu := Mux(io.a < io.b, 1.U, 0.U)
            }
            //XOR
            is("b100".U){
                i_alu := io.a ^ io.b;
            }
            //SRAI, SRLI
            is("b101".U) {
                when(io.func7(5)) {
                    i_alu := (io.a.asSInt >> io.b(4, 0)).asUInt

                }.otherwise {
                    i_alu := io.a >> io.b(4, 0)
                }
            }
            // OR
            is("b110".U) {
                i_alu := io.a | io.b
            }
            //AND
            is("b111".U) {
                i_alu := io.a & io.b
            }

        }
    }
       
            
        
  
    

    io.output := i_alu

  }