#!/usr/bin/env bash
# Builds the Verilator simulation binary.
#   ./build_sim.sh                 -> generated/obj_dir/VMain
#   SIM_PGO=1 ./build_sim.sh       -> generated/obj_dir_pgo/VMain  (~1.3x faster)
#
# Called by simulate.sh; safe to run on its own.
set -e

cd "$(dirname "$0")"
ROOT="$PWD"
SIM_CPP="$ROOT/simulation/vga-image.cpp"   # absolute: the PGO pass rebuilds from generated/

if [ ! -f generated/filelist.f ]; then
  echo "build_sim.sh: generated/filelist.f missing -- run ./generate-verilog.sh first" >&2
  exit 1
fi

# nix's cc wrapper strips -march=native by default to keep builds reproducible.
export NIX_ENFORCE_NO_NATIVE=0

# Override if you need a portable binary, e.g. SIM_ARCH=x86-64-v3
SIM_ARCH="${SIM_ARCH:-native}"

# -DSIM_SLOW_CLOCK falls back to the portable two-eval-per-cycle clocking if
# a Verilator upgrade ever renames the internal edge-detect variable.
SIM_CXXFLAGS="${SIM_CXXFLAGS:--O3 -march=$SIM_ARCH -fno-stack-protector -fomit-frame-pointer}"

# --expand-limit: a wide VecInit over a register array becomes a long concat
#   chain. Above --expand-limit words (default 64) Verilator emits it as chained
#   VL_CONCAT_WWI calls, each of which zeroes its whole output then copies the
#   accumulated prefix back in -- O(n^2) memset+memmove. Raising the limit emits
#   plain word assignments that gcc folds away.
# --output-split-cfuncs: keeps the NBA region from becoming one enormous
#   function that gcc's scheduler and register allocator give up on. It is also
#   what makes PGO pay off -- with one huge function PGO is a net loss.
VERILATOR_ARGS=(
  --cc --exe --build -j 0
  -O3
  --expand-limit 1024
  --output-split-cfuncs 700
  --x-assign unique --x-initial unique
  "$SIM_CPP" -f filelist.f --top Main
)

cd "$ROOT/generated"

if [ -z "${SIM_PGO:-}" ]; then
  exec verilator "${VERILATOR_ARGS[@]}" --Mdir obj_dir -o VMain -CFLAGS "$SIM_CXXFLAGS"
fi

# ---- profile-guided build -------------------------------------------------
# Does not remove work; it lifts IPC by laying out the enormous NBA branch
# trees the way the workload actually runs them. The profile is cached in
# generated/pgo, so only the first build pays for instrumentation and a
# training run. Use SIM_PGO=regen after RTL changes. -Wno-coverage-mismatch is
# load-bearing: without it gcc makes a profile that no longer matches the
# source a hard build error rather than a graceful fallback.
PROF_DIR="$ROOT/generated/pgo"
[ "$SIM_PGO" = regen ] && rm -rf "$PROF_DIR"

if [ ! -d "$PROF_DIR" ] || [ -z "$(ls -A "$PROF_DIR" 2>/dev/null)" ]; then
  TRAIN="${SIM_PGO_TRAIN:-${SIM_PROGRAM:-}}"
  if [ -z "$TRAIN" ] || [ ! -f "$TRAIN" ]; then
    echo "build_sim.sh: SIM_PGO needs a training program." >&2
    echo "  set SIM_PGO_TRAIN=/path/to/program.hex, or run simulate.sh with SIM_PGO=1" >&2
    exit 1
  fi
  TRAIN="$(realpath "$TRAIN")"
  rm -rf obj_dir_pgo; mkdir -p "$PROF_DIR"

  echo "[pgo 1/3] instrumented build"
  verilator "${VERILATOR_ARGS[@]}" --Mdir obj_dir_pgo -o VMain \
    -CFLAGS "$SIM_CXXFLAGS -fprofile-generate=$PROF_DIR -fprofile-update=single" \
    -LDFLAGS "-fprofile-generate=$PROF_DIR"

  echo "[pgo 2/3] training on $(basename "$TRAIN") for ${SIM_PGO_CYCLES:-1500000} cycles"
  ./obj_dir_pgo/VMain "$TRAIN" "${SIM_PGO_CYCLES:-1500000}" > /dev/null

  echo "[pgo 3/3] optimized build"
fi

exec verilator "${VERILATOR_ARGS[@]}" --Mdir obj_dir_pgo -o VMain \
  -CFLAGS "$SIM_CXXFLAGS -fprofile-use=$PROF_DIR -fprofile-correction -Wno-missing-profile -Wno-coverage-mismatch"
