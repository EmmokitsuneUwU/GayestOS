#include "IO.hpp"
#include <stdint.h>

void delay(volatile unsigned int count) {
    while (count--) {
        __asm__ __volatile__("nop");
    }
}