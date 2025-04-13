#include "Disk.hpp"
#include <stdint.h>
#include "IO.hpp"

void ataWait() {
    while (inb(0x1F7) & 0x80);
    while (!(inb(0x1F7) & 0x08));
}

void ataRead(uint32_t lba, void* buffer) {
    outb(0x1F6, 0xE0 | ((lba >> 24) & 0x0F));
    outb(0x1F2, 1);
    outb(0x1F3, lba & 0xFF);
    outb(0x1F4, (lba >> 8) & 0xFF);
    outb(0x1F5, (lba >> 16) & 0xFF);
    outb(0x1F7, 0x20);

    ataWait();
    insw(0x1F0, buffer, 256);
}

void ataWrite(uint32_t lba, const void* buffer) {
    outb(0x1F6, 0xE0 | ((lba >> 24) & 0x0F));
    outb(0x1F2, 1);
    outb(0x1F3, lba & 0xFF);
    outb(0x1F4, (lba >> 8) & 0xFF);
    outb(0x1F5, (lba >> 16) & 0xFF);
    outb(0x1F7, 0x30);

    ataWait();
    outsw(0x1F0, buffer, 256);

    while (inb(0x1F7) & 0x80);
}