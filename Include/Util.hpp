#ifndef UTIL_HPP
#define UTIL_HPP
#include <stdint.h>

extern bool StrCmp(const char* str1, const char* str2);
extern void reboot();
extern void cpyStrTBuffer(uint8_t *d, const char *o);
extern void cpyDatTBuffer(uint8_t *d, const char *o,unsigned int s);

#endif // UTIL_HPP