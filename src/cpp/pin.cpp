
#include "libmanyuc.h"

Pin::Pin(PinName pin_name, PinMode mode) {
	this->pin = Pin_Get(pin_name);
	this->mode(mode);
}

// TODO: ver tema de inlines

int Pin::read(){
	return Pin_Read(this->pin);	
}

void Pin::write(int value) {
	if (value) {
		Pin_On(this->pin);
	} else {
		Pin_Off(this->pin);
	}
}

void Pin::mode(PinMode mode) {
	switch (mode) {
		case Output:
			Pin_Output(this->pin);
			break;
		default:
			Pin_Input(this->pin);
			Pin_Input_Mode(this->pin, mode);
	}
}

Pin& Pin::operator= (int value) {
	this->write(value);
	return *this;
}

Pin::operator int() {
	return this->read();
}

