

KERNEL ?= mandelbrot
CYCLES ?= 12000000

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


CFLAGS  := -O3 -march=$(MARCH) -mabi=$(MABI) -ffreestanding -fno-builtin \
           -Wall -Wextra -Wno-unused-parameter -I.
LDFLAGS := -nostdlib -T gpu.ld -Wl,--gc-sections

OBJS := crt0.o $(KERNEL).o

all: $(KERNEL).bin

crt0.o: crt0.S
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c gpu.h
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

clean:
	rm -f *.o *.elf *.bin

.PHONY: all run dis clean
