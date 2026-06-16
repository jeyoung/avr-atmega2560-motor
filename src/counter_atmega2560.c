#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "counter.h"

static uint8_t counter_initialized = 0;
static uint16_t countdown = 0;

static void counter_initialize()
{
	DDRF |= (0x1 << DDF4) | (0x1 << DDF3) | (0x1 << DDF2) | (0x1 << DDF1) | (0x1 << DDF0);
	counter_initialized = 1;
}

void counter_on()
{
	if (!counter_initialized)
		counter_initialize();
	PORTF &= ~(0x1 << PORTF1);
}

void counter_off()
{
	if (!counter_initialized)
		counter_initialize();
	PORTF |= (0x1 << PORTF1);
}

static void internal_counter_set()
{
	if (!counter_initialized)
		counter_initialize();

	uint8_t bits_minutes = countdown / 60;
	uint8_t bits_seconds = ((countdown % 60) / 15) << 4;
	uint8_t value = bits_minutes | bits_seconds;

	// Clear the shift register
	PORTF &= ~(0x1 << PORTF4);
	PORTF |= (0x1 << PORTF4);

	PORTF &= ~((0x1 << PORTF3) | (0x1 << PORTF2));

	// Shift bit
	for (int i = 7; i >= 0; i--) {
		uint8_t bit = (value >> i) & 0x1;
		if (bit)
			PORTF |= (0x1 << PORTF0);
		else
			PORTF &= ~(0x1 << PORTF0);
		PORTF |= (0x1 << PORTF3);
		PORTF &= ~(0x1 << PORTF3);
	}

	// Set the storage register
	PORTF |= (0x1 << PORTF2);
	PORTF &= ~(0x1 << PORTF2);
}

void counter_set(uint8_t minutes, uint8_t seconds)
{
	countdown = (minutes * 60) + seconds;
	internal_counter_set();
}

void counter_decrement()
{
	if (countdown > 0) {
		countdown--;
		internal_counter_set();
	}
}

uint16_t counter_get()
{
	return countdown;
}
