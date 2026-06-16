#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

void main_initialize();
void main_process_buttons();
void main_start_button_released();
void main_second_button_released();
void main_minute_button_released();
void main_delay_ms(uint16_t ms);
void main_initialized();

#endif
