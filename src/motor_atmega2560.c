#include <avr/io.h>
#include <stdint.h>
#include "motor.h"

#define TOP 0x4e20

static uint8_t motor_initialized = 0;

static void motor_initialize()
{
	DDRB |= (0x1 << DDB6);
	TCCR1A |= (0x1 << COM1B1) | (0x1 << WGM11) | (0x1 << WGM10);
	TCCR1B |= (0x1 << WGM13) | (0x1 << CS11);
	OCR1A = TOP;

	motor_initialized = 1;
}

void motor_on()
{
	if (!motor_initialized)
		motor_initialize();

	OCR1B = TOP;
	motor_turned_on();
}

void motor_off()
{
	if (!motor_initialized)
		motor_initialize();

	OCR1B = 0x0;
	motor_turned_off();
}
