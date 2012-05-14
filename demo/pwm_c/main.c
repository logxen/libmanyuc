/*
 * libmanyuc - Turn leds on in C example
 * Copyright (C) 2012 - Margarita Manterola Rivero
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, 
 * MA 02110-1301 USA
 */

#include "libmanyuc.h"

/* This example turns on the leds using the PWM output. The leds fade in and
 * fade out indefinitely, each on their own time. */
int main(void) {

	PWMPin_t pwm_leds[4] = {
		PWMPin_Get(LED1),
		PWMPin_Get(LED2),
		PWMPin_Get(LED3),
		PWMPin_Get(LED4)};

	uint8_t nleds = 4;
	uint8_t i = 0;
	// One period set is enough
	PWMPin_Set_Period_ms(pwm_leds[0], 10);

	// Starting duty cycles and change rates
	float duty[4] = {0.75, 0.5, 0.25, 0};
	float change[4] = {0.0625, 0.0625, 0.0625, -0.0625};

	// Change the duty cycles approaching 100% and 0%.
    while(1) {
		for (i = 0; i < nleds; i++) {
			if ((duty[i] > 0.90) || (duty[i] < 0.05)) {
				change[i] = -change[i];
			} 
			duty[i] += change[i];
			PWMPin_Set_Duty_Cycle(pwm_leds[i], duty[i]);
		}
		wait(0.0625);
    }
}
