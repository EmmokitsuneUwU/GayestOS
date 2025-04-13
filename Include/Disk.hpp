#ifndef DISK_HPP
#define DISK_HPP
#include <stdint.h>
#include "IO.hpp"

extern void ataWait();
extern void ataRead(uint32_t lba, void* buffer);
extern void ataWrite(uint32_t lba, const void* buffer);

#endif // DISK_HPP