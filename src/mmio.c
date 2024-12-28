#include "mmio.h"
#include "videocore.h"

// Default MMIO base (QEMU)
static volatile uint32_t MMIO_BASE = 0x3F000000UL;

void configure_mmio_base(void)
{
  uint32_t revision = detect_pi_model();

  if (revision  == 0xA02082 || revision  == 0xA22082) {
    // Pi 3B/3B+
    MMIO_BASE = 0x3F000000UL;
  } else if (revision >= 0xA03111) {
    // Pi 4 or higher
    MMIO_BASE = 0xFE000000UL;
  }
}

uint32_t get_mmio_base(void)
{
  return MMIO_BASE;
}

volatile uint32_t* mmio_get_register(uint32_t offset)
{
  return (volatile uint32_t*)((uintptr_t)MMIO_BASE + offset);
}