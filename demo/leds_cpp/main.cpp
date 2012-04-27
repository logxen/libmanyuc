#include "libmanyuc.h"

/* This example turns the leds on and off, one by one. */

int main() {

	Pin leds[] = { Pin(LED1, Output), Pin(LED2, Output),
		Pin(LED3, Output), Pin(LED4, Output) };
    while(1) {
		for (int i = 0; i < 4; i++) {
			leds[i] = 1;
			wait(0.2);
			leds[i] = 0;
		}
    }
}
