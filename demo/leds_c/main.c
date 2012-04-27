#include "libmanyuc.h"

/* This example turns all 4 leds on and then off */

int main(void) {

	Pin_t leds[] = { Pin_Get(LED4), Pin_Get(LED3), 
		Pin_Get(LED2), Pin_Get(LED1) };
	int nleds = 4;

	int i;
	for (i = 0; i < nleds; i++) {
		Pin_Output(leds[i]);
	}

    while(1) {
		for (i = 0; i < nleds; i++) {
			Pin_On(leds[i]);
        	wait(0.1);         // Delay 100 Msec
		}
		for (i = 0; i < nleds; i++) {
			Pin_Off(leds[i]);
        	wait(0.1);         // Delay 100 Msec
		}
    }
}
