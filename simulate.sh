#!/usr/bin/env bash
# Build the simulator and run a program on it. One entry point for all three
# kinds of input -- it dispatches on the extension:
#
#   ./simulate.sh ./programs/mandelbrot.c          # compile a C file, then run
#   ./simulate.sh ./programs/renderer.hex          # ASCII hex, one word per line
#   ./simulate.sh ./renderer/src/render.bin        # raw binary image
#   ./simulate.sh                                  # built-in default program
#
# Optional second argument caps the run; omit it and the sim runs until Ctrl-C.
#   ./simulate.sh ./programs/mandelbrot.c 3000000
#
# SIM_PGO=1 builds with profile-guided optimization (~1.4x faster here).
set -e

cd "$(dirname "$0")"
ROOT="$PWD"

# ---- locate a RISC-V toolchain (only needed for .c input) -----------------
# The xpack tree is ~1.6 GB, so rather than keep a second copy here we look in
# the usual places. Set RISCV_GCC to override.
find_riscv_gcc() {
  if [ -n "${RISCV_GCC:-}" ]; then echo "$RISCV_GCC"; return; fi
  local c
  for c in "$ROOT"/xpack-riscv-none-elf-gcc-*/bin/riscv-none-elf-gcc \
           "$ROOT"/../dawn-cpu/xpack-riscv-none-elf-gcc-*/bin/riscv-none-elf-gcc; do
    [ -x "$c" ] && { echo "$c"; return; }
  done
  for c in riscv-none-elf-gcc riscv64-elf-gcc riscv64-unknown-elf-gcc; do
    command -v "$c" >/dev/null 2>&1 && { command -v "$c"; return; }
  done
  echo ""
}

# Matches renderer/src/Makefile's target ISA. Override with SIM_MARCH.
SIM_MARCH="${SIM_MARCH:-rv32im_zbb}"

compile_c() {
  local src="$1"
  local gcc; gcc="$(find_riscv_gcc)"
  if [ -z "$gcc" ]; then
    echo "simulate.sh: no RISC-V gcc found." >&2
    echo "  set RISCV_GCC=/path/to/riscv-none-elf-gcc, or drop an xpack toolchain in $ROOT" >&2
    exit 1
  fi
  local objcopy="${gcc%gcc}objcopy"
  mkdir -p generated
  echo "[cc] $(basename "$src")  (-march=$SIM_MARCH, $(basename "$gcc"))" >&2
  "$gcc" -c -O3 -march="$SIM_MARCH" -mabi=ilp32 "$src" -o generated/program.o
  "$gcc" -march="$SIM_MARCH" -mabi=ilp32 -nostdlib \
      "-Wl,--section-start=.text=0x0,--entry=_start" \
      -o generated/program.elf generated/program.o -lgcc
  "$objcopy" -O binary generated/program.elf generated/program.bin
  echo "$ROOT/generated/program.bin"
}

# ---- resolve the program --------------------------------------------------
# The first positional is always the program slot, even when it is empty --
# consuming it unconditionally keeps `simulate.sh "" 900000` from shifting the
# cycle limit into the program position (or, before that, into argv[3], where
# it was ignored and the run silently became unbounded).
PROG="$ROOT/programs/renderer.hex"   # default when no program is named

if [ $# -gt 0 ]; then
  IN="$1"; shift
  if [ -n "$IN" ]; then
    # realpath succeeds on a path whose parent exists even if the file does
    # not, so check for the file itself rather than letting a missing program
    # surface later as a confusing error from the build or the loader.
    if [ ! -f "$IN" ]; then
      echo "simulate.sh: no such program: $IN" >&2
      case "$IN" in
        */render.bin|render.bin)
          echo "  renderer/src/render.bin is a build artifact -- produce it with ./buildrenderer.sh," >&2
          echo "  or run the prebuilt ./programs/renderer.hex instead." >&2 ;;
      esac
      exit 1
    fi
    IN="$(realpath "$IN")"
    case "$IN" in
      *.c) PROG="$(compile_c "$IN" | tail -1)" ;;
      *)   PROG="$IN" ;;
    esac
  fi
fi

if [ ! -f "$PROG" ]; then
  echo "simulate.sh: program not found: $PROG" >&2
  exit 1
fi

# ---- build and run --------------------------------------------------------
SIM_PGO_TRAIN="${SIM_PGO_TRAIN:-$PROG}" ./build_sim.sh

cd generated
OBJ=obj_dir; [ -n "${SIM_PGO:-}" ] && OBJ=obj_dir_pgo
exec "./$OBJ/VMain" "$PROG" "$@"
