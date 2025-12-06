#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

/**
 * Is called at initialisation
 */
void main_initialize();

/**
 * Is called when the power button is released
 */
void main_start_button_released();
void main_second_button_released();
void main_minute_button_released();

void main_delay_ms(uint16_t ms);

void main_initialized();

#endif
