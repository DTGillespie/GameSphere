#include <stdint.h>
#include "src/util.h"
#include "src/mmio.h"
#include "src/videocore.h"
#include "src/uart.h"
#include "src/gpio.h"

void main(void)
{
  // Testing Embedded LED/GPIO binding & control
  gpio_set_output(14);

  while(1) {
    gpio_set(14);   // LED On
    delay(10000000);
    gpio_clear(14); // LED Off
    delay(10000000);
  }

  return 0;

  // Dynamically configure MMIO base based on the detected board model
  //configure_mmio_base();

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
