#include <stdint.h>
#include "mmio.h"
#include "videocore.h"

// Default MMIO base (QEMU)
static volatile uint32_t MMIO_BASE = 0x3F000000ULL;

void configure_mmio_base(void)
{
  volatile uint32_t* debug_reg = (volatile uint32_t*)(0x3F000000 + 0x3000);

  uint32_t revision = detect_pi_model();

  if (revision  == 0xA02082 || revision  == 0xA22082) {
    // Pi 3B/3B+
    MMIO_BASE = 0x3F000000UL;
  } else if (revision >= 0xA03111) {
    // Pi 4 or higher
    MMIO_BASE = 0xFE000000UL;
  }

  debug_reg = (volatile uint32_t*)(MMIO_BASE + 0x3000);

  *debug_reg = MMIO_BASE;
}

uint32_t get_mmio_base(void)
{
  return MMIO_BASE;
}

volatile uint32_t* mmio_get_register(uint32_t offset)
{
  return (volatile uint32_t*)((uintptr_t)MMIO_BASE + offset);
}

uint32_t GET32(uint64_t addr)
{
  return *(volatile uint32_t *)addr;
}

void PUT32(uint64_t addr, uint32_t value)
{
  *(volatile uint32_t *)addr = value;
}