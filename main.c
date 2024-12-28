#include <stdint.h>
#include "src/mmio.h"
#include "src/videocore.h"
#include "src/uart.h"

void main(void)
{
  // Dynamically configure MMIO base based on the detected board model
  configure_mmio_base();

  /*
  // Initialize UART
  uart_init();

  // Print a message
  uart_puts("Hello World from AArch64 bare metal on Raspberry Pi!\n");

  while (1) {
    // Main loop
  }
  */
}
