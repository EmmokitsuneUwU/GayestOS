#ifndef SPEAKER_HPP
#define SPEAKER_HPP
#include <stdint.h>

extern void play_sound(uint32_t nFrequence);
extern void nosound();
extern void beep(uint32_t nFrequence);

#endif // SPEAKER_HPP