#include "Util.hpp"
#include "IO.hpp"
#define MAX_ARGS 5

bool StrCmp(const char* str1, const char* str2)
{
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return false;
        }
            str1++;
            str2++;
        }
    
    return (*str1 == '\0' && *str2 == '\0');
}
void reboot()
{
    while ((inb(0x64) & 0x02) != 0);
    outb(0x64, 0xFE); 
}
void cpyTBuffer(uint8_t *d, const char *o)
{
    while (*o) {
        *d = (uint8_t)*o;
        o++;
        d++;
    }
    *d = 0; // Null terminator si es texto
}
void cpyDatTBuffer(uint8_t *d, const char *o,unsigned int s)
{
    for (unsigned int i = 0; i < s; i++) {
        d[i] = (uint8_t)o[i];
    }
}
