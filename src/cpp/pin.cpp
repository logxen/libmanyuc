
#include "libmanyuc.h"

Pin::Pin(PinName pin_name, PinMode mode) {
	pin = Pin_Get(pin_name);
	switch (mode) {
		case Output:
			Pin_Output(pin);
			break;
	}
}

// TODO: ver tema de inlines

int Pin::read(){
	return Pin_Read(this->pin);	
}

void Pin::write(int value) {
// TODO: ver si es posible evitar el IF
	if (value) {
		Pin_On(this->pin);
	} else {
		Pin_Off(this->pin);
	}
}

Pin& Pin::operator= (int value) {
	this->write(value);
	return *this;
}

Pin::operator int() {
	return this->read();
}

