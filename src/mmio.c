#include "mmio.h"

// Detect MMIO base for QEMU
static volatile uint32_t MMIO_BASE = 0x3F000000UL;

uint32_t get_mmio_base(void)
{
  return MMIO_BASE;
}

volatile uint32_t* mmio_get_registeR(uint32_t offset)
{
  return (volatile uint32_t*)(MMIO_BASE + offset);
}