ENTRY(_start)             /* Set entry point to _start */

SECTIONS {
  . = 0x80000;            /* Base address */

  .text : ALIGN(8) {
    KEEP(*(.text.boot))   /* Keep startup code, including _start */
    *(.text*)
  }

  .rodata : {
    *(.rodata*)
  }

  .data : {
    *(.data*)
  }

  .bss : ALIGN(8) {
    __bss_start__ = .;    /* Mark the start of .bss */
    *(.bss*)
    *(COMMON)
    . = ALIGN(8);         /* Ensure 8-byte alignment */
    __bss_end__ = .;      /* Mark the end of .bss */
  }
}
