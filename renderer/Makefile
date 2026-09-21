

KERNEL ?= demo_spin
CYCLES ?= 12000000
FRAME  ?= 0

ifeq ($(origin CC),default)
  CC := $(firstword $(wildcard ../xpack-riscv-none-elf-gcc-*/bin/riscv-none-elf-gcc) \
                    $(wildcard ../../dawn-cpu/xpack-riscv-none-elf-gcc-*/bin/riscv-none-elf-gcc) \
                    $(shell command -v riscv-none-elf-gcc 2>/dev/null) \
                    $(shell command -v riscv64-unknown-elf-gcc 2>/dev/null))
endif
OBJCOPY := $(CC:gcc=objcopy)
OBJDUMP := $(CC:gcc=objdump)

MARCH  ?= rv32im_zbb
MABI   ?= ilp32


# EXTRA appends extra -D flags without retyping the whole line. Overriding
# CFLAGS wholesale works too, but one shell-quoting slip drops the source file
# and gcc reports "no input files".
EXTRA   ?=
CFLAGS  := -O3 -march=$(MARCH) -mabi=$(MABI) -ffreestanding -fno-builtin -fwrapv \
           -Wall -Wextra -Wno-unused-parameter -I. -DDEMO_FRAME=$(FRAME) $(EXTRA)
LDFLAGS := -nostdlib -T gpu.ld -Wl,--gc-sections -Wl,--no-warn-rwx-segments

# Sources shared by the GPU and host builds. Add renderer modules here.
COMMON := camera.c sintab.c geom.c raster.c

# Renderer kernels expose render_frame() and get main() from main_gpu.o.
# Standalone kernels that define their own main (mandelbrot) must clear this:
#   make KERNEL=mandelbrot ENTRY=
ENTRY ?= main_gpu.o
EXTRA_OBJS ?=
OBJS  := crt0.o $(ENTRY) $(KERNEL).o $(EXTRA_OBJS) $(COMMON:.c=.o)

all: $(KERNEL).bin

# demo_all links every scene file, so it needs their objects and the guard
# that suppresses each one's standalone main().
combined:
	$(MAKE) KERNEL=demo_all ENTRY= EXTRA_OBJS="demo_spin.o demo_phys.o demo_fluid.o" EXTRA="-DDEMO_COMBINED"

# make tracks file timestamps, not flag changes, so a new FRAME= would leave
# main_gpu.o compiled against the old -DDEMO_FRAME and the GPU would silently
# render a different frame than the host reference. The stamp forces the
# rebuild.
.PHONY: FORCE
FORCE:
.frame-stamp: FORCE
	@echo '$(FRAME) $(EXTRA)' | cmp -s - $@ || echo '$(FRAME) $(EXTRA)' > $@

$(OBJS): .frame-stamp

crt0.o: crt0.S
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL).elf: $(OBJS) gpu.ld
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS) -lgcc

$(KERNEL).bin: $(KERNEL).elf
	$(OBJCOPY) -O binary $< $@
	@echo "$@: $$(stat -c %s $@) bytes"

dis: $(KERNEL).elf
	$(OBJDUMP) -d $<

run: $(KERNEL).bin
	cd .. && SIM_CXXFLAGS="-O3 -march=native -fno-stack-protector -fomit-frame-pointer -DSIM_SLOW_CLOCK" \
	    ./simulate.sh renderer/$(KERNEL).bin $(CYCLES)

# Host reference build: same renderer sources, NLANES == 1, writes a PPM.
# Compare against the simulated frame to separate SIMT bugs from maths bugs.
HOST_CC ?= gcc
host: host/ref
HDRS := $(wildcard *.h)
host/ref: host/host.c $(KERNEL).c $(COMMON) $(HDRS)
	$(HOST_CC) -O2 -Wall -Wextra -fwrapv -DGPU_HOST -I. -o $@ host/host.c $(KERNEL).c $(COMMON) -lm

# .frame-stamp for the same reason main_gpu.o needs it: without it a new
# FRAME= silently compares the GPU against a reference rendered from a
# different frame, which looks exactly like a renderer bug.
# Named per frame: a single shared ref.ppm lets a background compare at one
# frame be silently diffed against a reference another invocation rewrote for
# a different frame, which reads as a catastrophic renderer bug.
REF := ref-$(FRAME).ppm
$(REF): host/ref
	./host/ref $(FRAME) $(REF)

# Render the same frame on both targets and diff them. Any nonzero result is
# a real divergence: both sides quantise to the same 12-bit colour.
compare: $(KERNEL).bin $(REF)
	@cd .. && SIM_PPM=1 SIM_CXXFLAGS="-O3 -march=native -fno-stack-protector -fomit-frame-pointer -DSIM_SLOW_CLOCK" \
	    ./simulate.sh renderer/$(KERNEL).bin $(CYCLES) >/tmp/simout.txt 2>&1
	@# main_gpu prints this only after render_frame returns. Without the
	@# check, a render truncated by the cycle limit reports as a pixel
	@# difference and reads exactly like a renderer bug.
	@grep -q '^frame ' /tmp/simout.txt || { \
	    echo "RENDER INCOMPLETE: no completion marker after $(CYCLES) cycles."; \
	    echo "  raise CYCLES= before trusting any pixel diff."; exit 1; }
	@python3 tools/compare.py ../generated/frame.ppm $(REF)

# Native unit tests for the fixed-point and vector layers.
test:
	@set -e; for t in test/test_*.c; do \
	    echo "--- $$t"; \
	    $(HOST_CC) -O2 -Wall -Wextra -I. -o /tmp/rt_$$(basename $$t .c) $$t camera.c sintab.c -lm; \
	    /tmp/rt_$$(basename $$t .c); \
	done

# View the host reference without a PPM viewer.
ref.png: $(REF)
	python3 tools/ppm2png.py $(REF) ref.png

clean:
	rm -f *.o *.elf *.bin *.png host/ref ref-*.ppm .frame-stamp

.PHONY: all run dis clean host test compare
