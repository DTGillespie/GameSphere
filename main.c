#include <stdint.h>
#include "mmio.h"
#include "videocore.h"
#include "uart.h"

// Debug register for testing
#define DEBUG_REG ((volatile uint32_t*)(get_mmio_base() + 0x3000))

void main(void)
{
  // Dynamically configure MMIO base based on the detected board model
  configure_mmio_base();

  // Initialize UART
  uart_init();

  // Print a message
  uart_puts("Hello World from AArch64 bare metal on Raspberry Pi!\n");

  // Debug marker
  *DEBUG_REG = 0xDEADBEEF;

  while (1) {
    // Main loop
  }
}
