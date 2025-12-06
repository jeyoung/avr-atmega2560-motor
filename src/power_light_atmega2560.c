#include <avr/io.h>

static void init()
{
	DDRL |= (0x1 << DDL7);
}

void power_light_on()
{
	init();
	PORTL |= (0x1 << PORTL7);
}

void power_light_off()
{
	init();
	PORTL &= ~(0x1 << PORTL7);
}

