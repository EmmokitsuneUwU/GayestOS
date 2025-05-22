#ifndef UTIL_HPP
#define UTIL_HPP
#include <stdint.h>
#include <stddef.h>

extern bool StrCmp(const char* str1, const char* str2);
extern void reboot();
extern void cpyStrTBuffer(uint8_t *d, const char *o);
extern void cpyDatTBuffer(uint8_t *d, const char *o,unsigned int s);
extern int  chainToInt(char *str);

#ifdef __cplusplus
extern "C" {
#endif

void simple_alloc_init(void* heap_start, size_t heap_size);
void* simple_malloc(size_t size);
void simple_free(void* ptr);

#ifdef __cplusplus
}
#endif

#endif // UTIL_HPP