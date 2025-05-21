#ifndef KEYBOARD_UTILS
#define KEYBOARD_UTILS
#define KEYBOARD_PORT 0x60
#include <stdint.h>

extern char scancodeToIntChar(uint8_t scancode);
extern char read_key_polling();

#endif

