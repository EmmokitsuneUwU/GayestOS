#ifndef VGA_HPP
#define VGA_HPP
#include <stdint.h>
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

extern unsigned int VGATextMemorySector;
extern int VGATextCharacters;

extern void clearScreen();
extern void charPrint(unsigned char chr,uint8_t color);
extern void strPrint(const char str[], uint8_t color);
extern void hexPrint(unsigned int value, uint8_t color);
extern void clearLastChar();

#endif
