
#ifndef PIN_CPP_H
#define PIN_CPP_H

#include "port.h"

class Pin {
	private:
		Pin_t pin;
	public:
		Pin(PinName pin_name, PinMode mode);
		int read();
		void write(int value);
		void mode(PinMode mode);
		Pin& operator= (int value);
		operator int();
};

#endif
