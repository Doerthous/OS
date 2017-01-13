ENTRY(kernel_entry);
SECTIONS {
  . = 0x100000;
  _kernel_base = .;
  .text : {
    *(.text)
  }
  . = ALIGN(4);
  .rodata : {
    *(.rodata)
  }
  .rdata : {
    *(.rdata)
  }
  .data : {
    *(.data)
  }
  . = ALIGN(4);
  .bss : {
    *(.bss)
    *(COMMON)
  }
  . = ALIGN(4);
  _kernel_end = .;
}

