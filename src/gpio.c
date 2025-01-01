#include "gpio.h"
#include "mmio.h"

#define GPIO_BASE       0XFE200000UL
#define GPFSEL1_OFFSET  0x04
#define GPSET0_OFFSET   0x1C
#define GPCLR0_OFFSET   0x28

#define GPFSEL1         (GPIO_BASE + GPFSEL1_OFFSET)
#define GPSET0          (GPIO_BASE + GPSET0_OFFSET)
#define GPCLR0          (GPIO_BASE + GPCLR0_OFFSET)

void gpio_set_output(unsigned int gpio)
{
  unsigned int reg   = GPFSEL1 + ((gpio / 10) * 4);
  unsigned int shift = (gpio % 10) * 3;
  unsigned int val   = GET32(reg);

  val &= ~(7 << shift); // Clear function bits
  val |= (1 << shift);  // Set function to output

  PUT32(reg, val);
}

void gpio_set(unsigned int gpio)
{
  PUT32(GPSET0 + ((gpio / 32) * 4), (1 << (gpio % 32)));
}

void gpio_clear(unsigned int gpio)
{
  PUT32(GPCLR0 + ((gpio / 32) * 4), (1 << (gpio % 32)));
}