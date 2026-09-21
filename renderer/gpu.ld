OUTPUT_ARCH(riscv)
ENTRY(_start)



SECTIONS {
    . = 0x00000000;

    .text : {
        KEEP(*(.text.init))
        *(.text .text.*)
    }

    .rodata : {
        *(.rodata .rodata.*)
        *(.srodata .srodata.*)
    }

    . = ALIGN(8);
    PROVIDE(__global_pointer$ = . + 0x800);

    .data : {
        *(.data .data.*)
        *(.sdata .sdata.*)
    }

 
    .bss (NOLOAD) : {
        . = ALIGN(4);
        __bss_start = .;
        *(.sbss .sbss.*)
        *(.bss .bss.*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end = .;
    }

    /* Outside __bss_start/__bss_end on purpose: the framebuffer and depth
     * buffer are 600 KB together and are fully overwritten by raster_clear
     * every frame, so zeroing them at boot would cost millions of cycles for
     * nothing. */
    .noinit (NOLOAD) : {
        . = ALIGN(4);
        *(.noinit .noinit.*)
    }

    _end = .;


    __stack_top = 0x08000000;

    /DISCARD/ : { *(.comment) *(.note.*) *(.eh_frame) }
}
