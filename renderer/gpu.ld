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

    _end = .;


    __stack_top = 0x08000000;

    /DISCARD/ : { *(.comment) *(.note.*) *(.eh_frame) }
}
