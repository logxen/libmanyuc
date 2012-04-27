
#include "port.h"
#include "timers.h"

void wait(float s) {
	//Delay(200);
	Delay(s*1000);
}

void wait_ms(int ms) {
	Delay(ms);
}

void wait_us(int us) {
// TODO: can't do it with delay
	Delay(0);
}



