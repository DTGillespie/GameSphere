#ifndef BOARD_H
#define BOARD_H

#if defined(RASPI3)
  #define PERIPHERAL_BASE   0x20000000
#elif defined(RASPI4)
  #define PERIPHERAL_BASE   0xFE000000
#else
  #error "Unknown RPi model. Please provide an argument for a supported platform."
#endif

#define MAILBOX_OFFSET  0xB880
#define MAILBOX_BASE    (PERIPHERAL_BASE + MAILBOX_OFFSET)

#endif // BOARD_H