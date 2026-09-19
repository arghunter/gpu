// package RISCV

// import chisel3._
// import chisel3.simulator.EphemeralSimulator._
// import org.scalatest.flatspec.AnyFlatSpec
// import org.scalatest.matchers.should.Matchers
// import scala.util.Random

// class DivTest extends AnyFlatSpec with Matchers {

//   // RV32M funct3 encodings
//   val DIV  = 4 // b100 (signed)
//   val DIVU = 5 // b101 (unsigned)
//   val REM  = 6 // b110 (signed)
//   val REMU = 7 // b111 (unsigned)

//   def mask32(x: BigInt): BigInt = x & ((BigInt(1) << 32) - 1)

//   def toSigned32(x: BigInt): BigInt = {
//     val u = mask32(x)
//     if (u >= (BigInt(1) << 31)) u - (BigInt(1) << 32) else u
//   }

//   val MIN_INT = BigInt("80000000", 16) // as unsigned bit pattern
//   val MAX_INT = BigInt("7FFFFFFF", 16)
//   val ALL_ONES = BigInt("FFFFFFFF", 16) // -1 signed / 0xFFFFFFFF unsigned

//   // ---- reference model, matches the RV32M spec exactly ----
//   def expectedDiv(aBits: BigInt, bBits: BigInt, func3: Int): BigInt = func3 match {
//     case DIV =>
//       val a = toSigned32(aBits); val b = toSigned32(bBits)
//       if (b == 0) mask32(BigInt(-1))
//       else if (a == toSigned32(MIN_INT) && b == -1) MIN_INT
//       else mask32(a / b) // Scala BigInt division truncates toward zero, matches RV32M
//     case DIVU =>
//       val a = mask32(aBits); val b = mask32(bBits)
//       if (b == 0) ALL_ONES else a / b
//     case REM =>
//       val a = toSigned32(aBits); val b = toSigned32(bBits)
//       if (b == 0) mask32(a)
//       else if (a == toSigned32(MIN_INT) && b == -1) BigInt(0)
//       else mask32(a % b)
//     case REMU =>
//       val a = mask32(aBits); val b = mask32(bBits)
//       if (b == 0) a else a % b
//   }

//   def opName(f: Int): String = f match {
//     case DIV => "DIV"; case DIVU => "DIVU"; case REM => "REM"; case REMU => "REMU"
//   }

//   // Drives one divide/rem transaction through the start/ready/valid handshake
//   // and returns the 32-bit (masked) result. No settling gap is added beyond
//   // what's needed to see `ready`/`valid`, so consecutive calls on the same
//   // `dut` are genuinely back-to-back.
//   def runDiv(dut: Div, aBits: BigInt, bBits: BigInt, func3: Int, maxCycles: Int = 100): BigInt = {
//     var timeout = 0
//     while (!dut.io.ready.peek().litToBoolean && timeout < maxCycles) {
//       dut.clock.step(1)
//       timeout += 1
//     }
//     dut.io.ready.expect(true.B, "DUT should be ready to accept a new op")

//     dut.io.a.poke(mask32(aBits).U(32.W))
//     dut.io.b.poke(mask32(bBits).U(32.W))
//     dut.io.func3.poke(func3.U(3.W))
//     dut.io.start.poke(true.B)
//     dut.clock.step(1)
//     dut.io.start.poke(false.B)

//     timeout = 0
//     while (!dut.io.valid.peek().litToBoolean && timeout < maxCycles) {
//       dut.clock.step(1)
//       timeout += 1
//     }
//     dut.io.valid.expect(true.B, s"DUT did not assert valid within $maxCycles cycles")
//     mask32(dut.io.output.peek().litValue)
//   }

//   def checkOne(dut: Div, aBits: BigInt, bBits: BigInt, func3: Int): Unit = {
//     val exp = expectedDiv(aBits, bBits, func3)
//     val got = runDiv(dut, aBits, bBits, func3)
//     withClue(
//       s"${opName(func3)}  a=0x${mask32(aBits).toString(16)} (${toSigned32(aBits)})  " +
//       s"b=0x${mask32(bBits).toString(16)} (${toSigned32(bBits)})  " +
//       s"got=0x${got.toString(16)}  expected=0x${exp.toString(16)}: "
//     ) {
//       got shouldBe exp
//     }
//   }

//   "Div" should "handle the full boundary-value cross product back-to-back, no gaps" in {
//     simulate(new Div()) { dut =>
//       dut.io.start.poke(false.B)
//       dut.clock.step(2)

//       // signed-interesting boundary values (as raw 32-bit bit patterns)
//       val signedBoundaries = Seq(
//         BigInt(0), BigInt(1), ALL_ONES /* -1 */, BigInt(2), mask32(BigInt(-2)),
//         MAX_INT, MIN_INT, MAX_INT - 1, mask32(MIN_INT + 1)
//       )

//       var count = 0
//       for (a <- signedBoundaries; b <- signedBoundaries; f <- Seq(DIV, REM)) {
//         checkOne(dut, a, b, f)
//         count += 1
//       }

//       // unsigned-interesting boundary values
//       val unsignedBoundaries = Seq(
//         BigInt(0), BigInt(1), BigInt(2), ALL_ONES, ALL_ONES - 1, MIN_INT, MAX_INT
//       )
//       for (a <- unsignedBoundaries; b <- unsignedBoundaries; f <- Seq(DIVU, REMU)) {
//         checkOne(dut, a, b, f)
//         count += 1
//       }

//       println(s"Boundary cross-product: $count back-to-back operations, all correct.")
//     }
//   }

//   it should "handle hundreds of randomized signed/unsigned operations back-to-back" in {
//     simulate(new Div()) { dut =>
//       dut.io.start.poke(false.B)
//       dut.clock.step(2)

//       val rng = new Random(0xC0FFEE) // fixed seed -> reproducible failures

//       def randomOperand(): BigInt = {
//         // 25% of the time, pick from a pool of "spicy" values to bias
//         // coverage toward edges even inside the random stream; otherwise
//         // a uniformly random 32-bit pattern.
//         if (rng.nextInt(4) == 0) {
//           Seq(BigInt(0), BigInt(1), ALL_ONES, MIN_INT, MAX_INT, mask32(MIN_INT + 1), MAX_INT - 1)(rng.nextInt(7))
//         } else {
//           BigInt(32, rng) // uniform random 32-bit value
//         }
//       }

//       val iterations = 30000
//       var count = 0
//       for (_ <- 0 until iterations) {
//         val a = randomOperand()
//         val b = randomOperand()
//         // exercise all four ops against the same random operand pair each round
//         for (f <- Seq(DIV, REM, DIVU, REMU)) {
//           checkOne(dut, a, b, f)
//           count += 1
//         }
//       }

//       println(s"Randomized fuzz: $count back-to-back operations, all correct.")
//     }
//   }

//   it should "handle a fully randomized, mixed-op sequence with no idle gaps" in {
//     simulate(new Div()) { dut =>
//       dut.io.start.poke(false.B)
//       dut.clock.step(2)

//       val rng = new Random(42)
//       val ops = Seq(DIV, DIVU, REM, REMU)

//       val iterations = 50000
//       var count = 0
//       for (_ <- 0 until iterations) {
//         val f = ops(rng.nextInt(4))
//         // ~10% chance of a zero divisor, ~10% chance of the signed overflow
//         // pattern (only meaningful for DIV/REM, harmless otherwise), else
//         // fully random operands.
//         val roll = rng.nextInt(10)
//         val (a, b) =
//           if (roll == 0) (BigInt(32, rng), BigInt(0))
//           else if (roll == 1 && (f == DIV || f == REM)) (MIN_INT, ALL_ONES)
//           else (BigInt(32, rng), BigInt(32, rng))

//         checkOne(dut, a, b, f)
//         count += 1
//       }

//       println(s"Mixed-op randomized stress: $count back-to-back operations, all correct.")
//     }
//   }
// }