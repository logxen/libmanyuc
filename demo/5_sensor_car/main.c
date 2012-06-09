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

#define LED1 PA0
#define LED2 PA1
#define LED3 PA2

#define SW1 PA13

#define LED_EN PA20

/*#define SENS0 PA5
#define SENS1 PA6
#define SENS2 PA7
#define SENS3 PA8
#define SENS4 PA9*/

#define SENS0 AD7
#define SENS1 AD6
#define SENS2 AD5
#define SENS3 AD4
#define SENS4 PA9

#define PWM_DIR PA17

#define TWD0  PA3
#define TWCK0 PA4


/* This example turns all 4 leds on and then off */
int main(void) {

    // Access 4 leds predefined as LED1, LED2, LED3, LED4
    Pin_t leds[] = {
        Pin_Get(LED1),
        Pin_Get(LED2),
        Pin_Get(LED3),
    };
    int nleds = 3, i = 0;

    // Set all pins as output
    for (i = 0; i < nleds; i++) {
        Pin_Output(leds[i]);
        Pin_On(leds[i]);
    }

    Pin_t button = Pin_Get(SW1);
    Pin_Input(button),
    Pin_Mode(button, PullUp);

    // Get the sensor enabler
    Pin_t enabler = Pin_Get(LED_EN);
    Pin_Output(enabler),
    Pin_On(enabler);

    // Get AnalogIns
    uint32_t sensors[] = {
        AnalogIn_Get(SENS0),
        AnalogIn_Get(SENS1),
        AnalogIn_Get(SENS2),
        AnalogIn_Get(SENS3),
        AnalogIn_Get(SENS4) };
    int nsensors = 5;

    while (1) {
        if (Pin_Read(button) == SW_ON) {
            Pin_Off(leds[2]);
        } else {
            Pin_On(leds[2]);
        }
        if (AnalogIn_Read(sensors[0]) > 0) {
            Pin_Off(leds[1]);
        } else {
            Pin_On(leds[1]);
        }


/*      for (i = 0; i < nleds; i++) {
            Pin_On(leds[i]);
            Delay(0.2);
        }
        for (i = 0; i < nleds; i++) {
            Pin_Off(leds[i]);
            Delay(0.2);
        }*/
    }
}
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
