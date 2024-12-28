#include "videocore.h"
#include "mailbox.h"

uint32_t detect_pi_model(void)
{
  uint32_t buffer[7] __attribute__((aligned(16))); // C11 Syntax: alignas(16) uint32_t buffer[7];
  
  buffer[0] = 7 * sizeof(uint32_t); // Size of buffer
  buffer[1] = 0;                    // Request code
  buffer[2] = 0x00010002;           // Tag: GET_BOARD_REVISION
  buffer[3] = 4;                    // Value buffer size
  buffer[4] = 0;                    // Request/response length
  buffer[5] = 0;                    // Placeholder for revision
  buffer[6] = 0;                    // End tag

  if (mailbox_call(8, buffer) != 0) {
    return 0; // Error
  }

  return buffer[5];
}