#ifndef MMIO_H
#define MMIO_H

#include <stdint.h>

void configure_mmio_base(void);
uint32_t get_mmio_base(void);
volatile uint32_t* mmio_get_register(uint32_t offset);
uint32_t GET32(uint64_t addr);
void PUT32(uint64_t addr, uint32_t value);

#endif // MMIO_H