#include "Speaker.hpp"
#include "IO.hpp"
void play_sound(uint32_t nFrequence) {
    uint32_t Div;
    uint8_t tmp;

    Div = 1193180 / nFrequence;
    outb(0x43, 0xb6);
    outb(0x42, (uint8_t) (Div) );
    outb(0x42, (uint8_t) (Div >> 8));

    tmp = inb(0x61);
     if (tmp != (tmp | 3)) {
        outb(0x61, tmp | 3);
    }
}

//make it shut up
void nosound() {
    uint8_t tmp = inb(0x61) & 0xFC;
    
    outb(0x61, tmp);
}

//Make a beep
void beep(uint32_t nFrequence) {
     play_sound(nFrequence);
     delay(300000);
     nosound();
         //set_PIT_2(old_frequency);
}
