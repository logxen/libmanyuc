#include "libmanyuc.h"

/* This example turns the first and second leds on, when buttons located
   in P19 and P20 are pressed.  Buttons are in PullUp mode, return 0 when
   pressed. */

int main() {

    Pin leds[] = { Pin(LED1, Output), Pin(LED2, Output),
        Pin(LED3, Output), Pin(LED4, Output) };

    Pin buttons[] = { Pin(P20, PullUp), Pin(P19, PullUp) };

    while(1) {
        for (int i = 0; i < 2; i++) {
            if (buttons[i] == 0) {
                leds[i] = 1;
            } else {
                leds[i] = 0;
            }
        }
    }
}
