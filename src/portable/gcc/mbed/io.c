
#include "port.h"
#include "portmacro.h"


/*----------------------------------------------------------------------------
  Digital Input / Output 
 *----------------------------------------------------------------------------*/

/* Convert the pin name to a pin struct. */
Pin_t Pin_Get (PinName pin_name) {
	// TODO: improve this
	uint32_t address = pin_name - LPC_GPIO_BASE;
	//Pin_t pin = { 0, 1 << (address % 32) };
	Pin_t pin = { 0, 1 << (address % 32) };
	uint32_t port = address / 32;
	switch (port) {
		case 0:
			pin.port = LPC_GPIO0;
			break;
		case 1:
			pin.port = LPC_GPIO1;
			break;
		case 2:
			pin.port = LPC_GPIO2;
			break;
		case 3:
			pin.port = LPC_GPIO3;
			break;
		case 4:
			pin.port = LPC_GPIO4;
			break;
	}
	return pin;
}


// Switch Pin On 
__INLINE void Pin_On (Pin_t pin) {
    pin.port->FIOPIN |=  (pin.address);
}

// Switch Pin Off 
__INLINE void Pin_Off (Pin_t pin) {
    pin.port->FIOPIN &= ~(pin.address);
}

// Set pin as output 
__INLINE void Pin_Output(Pin_t pin) {
    pin.port->FIODIR |= pin.address;
}

// Set pin as input 
__INLINE void Pin_Input(Pin_t pin) {
    pin.port->FIODIR &= ~(pin.address); 
}

// Read pin state 
__INLINE int Pin_Read (Pin_t pin) {
    return ((pin.port->FIOPIN & pin.address) ? 1 : 0); 
}
