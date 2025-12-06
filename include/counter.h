#ifndef COUNTER_H
#define COUNTER_H

#include <stdint.h>

void counter_on();
void counter_off();
void counter_set(uint8_t minutes, uint8_t seconds);
void counter_decrement();
uint16_t counter_get();

#endif
