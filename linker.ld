SECTIONS
{
  /* Place everything starting at 0x80000. */
  . = 0x80000;

  .text : {
    KEEP(*(.text.boot))   /* keep startup code if needed */
    *(.text*)
  }

  .rodata : {
    *(.rodata*)
  }

  .data : {
    *(.data*)
  }

  .bss : {
    __bss_start__ = .;
    *(.bss*)
    *(COMMON)
    . = ALIGN(8);
    __bss_end__ = .;
  }
}