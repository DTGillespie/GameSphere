#include "mailbox.h"
#include "mmio.h"

#define MAILBOX_BASE  0xB880
#define MAILBOX_EMPTY 0x40000000
#define MAILBOX_FULL  0x80000000
#define MAILBOX_READ    (MAILBOX_BASE + 0x00)
#define MAILBOX_STATUS  (MAILBOX_BASE + 0x18)
#define MAILBOX_WRITE   (MAILBOX_BASE + 0x20)

int mailbox_call(uint8_t channel, uint32_t* buffer)
{
  volatile uint32_t* write_reg  = mmio_get_register(MAILBOX_WRITE);
  volatile uint32_t* read_reg   = mmio_get_register(MAILBOX_READ);
  volatile uint32_t* status_reg = mmio_get_register(MAILBOX_STATUS);

  uint32_t addr = ((uintptr_t)buffer & ~0xF) | (channel & 0xF);

  while (*status_reg & MAILBOX_FULL) { }
  *write_reg = addr;

  while (1) {
    while (*status_reg & MAILBOX_EMPTY) { }
    uint32_t response = *read_reg;

    if ((response & 0xF) == channel) {
      return response & 0xF0; // Return success/error
    }
  }
}