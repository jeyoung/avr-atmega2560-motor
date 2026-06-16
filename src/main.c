#include <stdint.h>
#include "counter.h"
#include "main.h"
#include "motor.h"
#include "power_light.h"

static uint8_t main_power = 0;
static uint8_t minutes = 0;
static uint8_t seconds = 0;

static void loop();

int main(int argc, char **argv)
{
	main_initialize();
	while (1) {
		main_process_buttons();
		loop();
	}
	return 0;
}

static void loop()
{
	if (main_power) {
		motor_on();
		counter_decrement();
		if (counter_get() > 0)
			main_delay_ms(1000);
		else {
			main_power = 0;
			counter_set(minutes, seconds);
		}
	} else
		motor_off();
}

void main_start_button_released()
{
	if (counter_get() > 0)
		main_power ^= 1;
}

void main_second_button_released()
{
	if (main_power)
		return;
	if ((seconds+=15) >= 60)
		seconds = 0;
	counter_set(minutes, seconds);
}

void main_minute_button_released()
{
	if (main_power)
		return;
	if (++minutes > 15)
		minutes = 0;
	counter_set(minutes, seconds);
}

void main_initialized()
{
	counter_set(0, 0);
	counter_on();
}

void motor_turned_on()
{
	power_light_on();
}

void motor_turned_off()
{
	power_light_off();
}
