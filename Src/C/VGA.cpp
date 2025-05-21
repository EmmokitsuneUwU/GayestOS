#include "VGA.hpp"

unsigned int VGATextMemorySector = 0xb8000;
#define VGA_WIDTH 320
#define VGA_HEIGHT 200
#define VGA_GRAPHICSMEMORY ((volatile unsigned char*)0xA0000)
int VGATextCharacters = 0;

void clearScreen()
{
    VGATextMemorySector = 0xB8000;
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        *(char*)(VGATextMemorySector + i * 2) = ' ';
        *(char*)(VGATextMemorySector + i * 2 + 1) = 0x0F;
    }
    VGATextCharacters = 0;
    VGATextMemorySector = 0xb8000;
}

void charPrint(unsigned char chr,uint8_t color = 0x0F)
{
    if (VGATextMemorySector <= 0xB8FA0 - 2)
    {
        if (chr == '\n') {
            unsigned int offset = VGATextMemorySector - 0xB8000;
            unsigned int row = offset / (VGA_WIDTH * 2);
            VGATextMemorySector = 0xB8000 + (row + 1) * VGA_WIDTH * 2;
            VGATextCharacters += 80;
        } else {
            *(char*)VGATextMemorySector = chr;
            *(char*)(VGATextMemorySector + 1) = color;
            VGATextMemorySector += 2;
        }
        VGATextCharacters += 1;
    }
    else{
        clearScreen();
    }

}

void strPrint(const char str[], uint8_t color = 0x0F)
{
    int i = 0;
    while(str[i] != '\0')
    {
        charPrint(str[i],color);
        i += 1;
    }
}
void hexPrint(unsigned int value, uint8_t color = 0x0F)
{
    const char hexDigits[] = "0123456789ABCDEF";
    char hexBuffer[11];
    int index = 0;

    hexBuffer[index++] = '0';
    hexBuffer[index++] = 'x';

    bool leading = true;
    for (int i = 28; i >= 0; i -= 4) {
        uint8_t hexDigit = (value >> i) & 0xF;

        if (hexDigit != 0 || !leading || i == 0) {
            leading = false;
            hexBuffer[index++] = hexDigits[hexDigit];
        }
    }

    hexBuffer[index] = '\0';
    strPrint(hexBuffer, color);
}
