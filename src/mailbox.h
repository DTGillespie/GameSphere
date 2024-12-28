#ifndef MAILBOX_H
#define MAILBOX_H

#include <stdint.h>

int mailbox_call(uint8_t channel, uint32_t* buffer);

#endif // MAILBOX_H