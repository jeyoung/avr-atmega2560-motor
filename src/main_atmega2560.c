#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "main.h"

/*
 * Two-stage debounce algorithm:
 *
 * Stage 1 (ISR): On the first falling edge, the ISR disables its own
 * external interrupt and sets a flag.  Disabling the interrupt acts as
 * an immediate lockout — subsequent bounce edges cannot retrigger the
 * ISR, so a single mechanical press produces exactly one flag.
 *
 * Stage 2 (main context): main_process_buttons() polls the flags each
 * iteration of the main loop.  When a flag is found, it waits
 * DEBOUNCE_MS (50 ms) for the contacts to finish settling, then calls
 * the application-level handler and re-enables the interrupt so the
 * next press can be detected.
 */
#define DEBOUNCE_MS 50

static volatile uint8_t main_button_flags;

#define BUTTON_START  (1 << 0)
#define BUTTON_SECOND (1 << 1)
#define BUTTON_MINUTE (1 << 2)

void main_initialize()
{
	PORTD |= (1 << PD2) | (1 << PD1) | (1 << PD0);
	EICRA |= (1 << ISC21) | (1 << ISC11) | (1 << ISC01);
	EIMSK |= (1 << INT2) | (1 << INT1) | (1 << INT0);
	sei();

	main_initialized();
}

void main_delay_ms(uint16_t ms)
{
	for (uint16_t i = 0; i < ms; i++)
		_delay_ms(1);
}

void main_process_buttons()
{
	uint8_t flags;

	if (!main_button_flags)
		return;

	_delay_ms(DEBOUNCE_MS);    /* let contacts settle */

	flags = main_button_flags;
	main_button_flags = 0;

	if (flags & BUTTON_START) {
		main_start_button_released();
		EIMSK |= (1 << INT0);   /* re-arm the interrupt */
	}
	if (flags & BUTTON_SECOND) {
		main_second_button_released();
		EIMSK |= (1 << INT1);
	}
	if (flags & BUTTON_MINUTE) {
		main_minute_button_released();
		EIMSK |= (1 << INT2);
	}
}

ISR(INT0_vect)
{
	EIMSK &= ~(1 << INT0);          /* lock out bounce edges */
	main_button_flags |= BUTTON_START;
}

ISR(INT1_vect)
{
	EIMSK &= ~(1 << INT1);
	main_button_flags |= BUTTON_SECOND;
}

ISR(INT2_vect)
{
	EIMSK &= ~(1 << INT2);
	main_button_flags |= BUTTON_MINUTE;
}
