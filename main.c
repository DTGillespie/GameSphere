#include <stdint.h>

// Pi 4 uses 0xF3000000 for the base of the peripheral registers
//#define MMIMO_BASE    0xFE000000UL

// Pi 3b (QEMU)
#define MMIMO_BASE    0x3F000000UL
#define DEBUG_REG ((volatile uint32_t*)(MMIMO_BASE + 0x3000)) // Arbitrary address in MMIO range

// For the PL011 UART (UART0) on Pi 4, offsets are the same but base is 0xFE201000
#define UART0_BASE  (MMIMO_BASE + 0x201000)
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

static void uart_init(void)
{
  // Disable UART0
  *UART0_CR = 0;

  // Mask all interrupts
  *UART0_IMSC = 0;

  // Clear interrupts
  *UART0_ICR = 0x77FF;

   /*
   * The Pi 4 may require configuring GPIO pins 14/15 in ALT0 for TX/RX.
   * That’s done via GPFSEL registers at 0xFE200000 + offsets.
   * For brevity, we omit it here, but typically you'd do:
   *
   *   #define GPFSEL1 (MMIO_BASE + 0x200004)
   *   // set GPIO14, GPIO15 to ALT0
   *
   * Also consider disabling pull-up/down for those pins.
   */

  // Set baud rate

  // For 115200 at 48 MHz reference clock => IBRD=26, FBRD=3 is approximate
  *UART0_IBRD = 26;
  *UART0_FBRD = 3;

  // 8 bits, enable FIFO
  *UART0_LCRH = (1 << 4) | (1 << 5) | (1 << 6); // 8 bits, FIFO enabled

  // Enable UART, TX, RX
  *UART0_CR = (1 << 0) | (1 << 8) | (1 << 9);
}

static void uart_putc(char c)
{
  // Wait until transmit FIFO has space
  while (*UART0_FR & (1 << 5)) {
    // Wait
  }

  *UART0_DR = c;
}

static void uart_puts(const char* str)
{
  while (*str) {

    if (*str == '\n') {
      uart_putc('\r');
    }

    uart_putc(*str++);
  }
}

void main(void)
{
  uart_init();
  uart_puts("Hello World from AArch64 bare metal on Pi 4b!\n");
  *DEBUG_REG = 0xDEADBEEF; // Debug marker

  while (1) {
    // Spin
  }
}
