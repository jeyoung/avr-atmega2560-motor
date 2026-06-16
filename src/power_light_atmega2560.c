#include <avr/io.h>

static uint8_t power_light_initialized = 0;

static void power_light_initialize()
{
	DDRL |= (1 << DDL7);
	power_light_initialized = 1;
}

void power_light_on()
{
	if (!power_light_initialized)
		power_light_initialize();
	PORTL |= (1 << PORTL7);
}

void power_light_off()
{
	if (!power_light_initialized)
		power_light_initialize();
	PORTL &= ~(1 << PORTL7);
}

