#include <stdint.h>
#include "mmio.h"

#define UART0_BASE  (get_mmio_base() + 0x201000)
#define UART0_DR    ((volatile uint32_t*)(UART0_BASE + 0x00))
#define UART0_FR    ((volatile uint32_t*)(UART0_BASE + 0x18))
#define UART0_IBRD  ((volatile uint32_t*)(UART0_BASE + 0x24))
#define UART0_FBRD  ((volatile uint32_t*)(UART0_BASE + 0x28))
#define UART0_LCRH  ((volatile uint32_t*)(UART0_BASE + 0x2C))
#define UART0_CR    ((volatile uint32_t*)(UART0_BASE + 0x30))
#define UART0_IMSC  ((volatile uint32_t*)(UART0_BASE + 0x38))
#define UART0_ICR   ((volatile uint32_t*)(UART0_BASE + 0x44))

static inline void delay(int32_t count)
{
  while (count-- > 0) {
    __asm__ volatile("nop");
  }
}

void uart_init(void)
{
  // Disable UART0
  *UART0_CR = 0;

  // Mask all interrupts
  *UART0_IMSC = 0;

  // Clear interrupts
  *UART0_ICR = 0x77FF;

  // Set baud rate (115200 at 48 MHz reference clock)
  *UART0_IBRD = 26;
  *UART0_FBRD = 3;

  // 8 bits, enable FIFO
  *UART0_LCRH = (1 << 4) | (1 << 5) | (1 << 6);

  // Enable UART, TX, RX
  *UART0_CR = (1 << 0) | (1 << 8) | (1 << 9);
}

void uart_putc(char c)
{
  while (*UART0_FR & (1 << 5)) {/* Wait until transmit FIFO has space */}
  
  *UART0_DR = c;
}

void uart_puts(const char* str)
{
  while (*str) {

    if (*str == '\n') {
      uart_putc('\r');
    }

    uart_putc(*str++);
  }
}
