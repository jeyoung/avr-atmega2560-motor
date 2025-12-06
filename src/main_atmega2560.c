#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "main.h"

void main_initialize()
{
	PORTD |= (0x1 << PORTD2) | (0x1 << PORTD1) | (0x1 << PORTD0);
	EICRA |= (0x1 << ISC21) | (0x1 << ISC11) | (0x1 << ISC01);
	EIMSK |= (0x1 << INT2) | (0x1 << INT1) | (0x1 << INT0);
	sei();

	main_initialized();
}

void main_delay_ms(uint16_t ms)
{
	for (uint16_t i = 0; i < ms; i++)
		_delay_ms(1);
}

ISR(INT0_vect)
{
	main_start_button_released();
}

ISR(INT1_vect)
{
	main_second_button_released();
}

ISR(INT2_vect)
{
	main_minute_button_released();
}
