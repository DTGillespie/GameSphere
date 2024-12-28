SECTIONS {
  . = 0x80000;              /* Base address */

  .text : ALIGN(8) {
    KEEP(*(.text.boot))     /* Keep startup code */
    *(.text*)
  }

  .rodata : {
    *(.rodata*)
  }

  .data : {
    *(.data*)
  }

  .bss : ALIGN(8) {
    __bss_start__ = .;      /* Mark the start of .bss */
    *(.bss*)                /* All .bss sections */
    *(COMMON)               /* Common symbols */
    . = ALIGN(8);           /* Ensure 8-byte alignment */
    __bss_end__ = .;        /* Mark the end of .bss */
  }
}