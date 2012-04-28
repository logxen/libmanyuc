
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
	Pin_t pin = { address / 32, address % 32, 1 << (address % 32) };
	return pin;
}


// Switch Pin On 
__INLINE void Pin_On (Pin_t pin) {
    LPC_GPIO[pin.port].FIOPIN |= (pin.mask);
}

// Switch Pin Off 
__INLINE void Pin_Off (Pin_t pin) {
    LPC_GPIO[pin.port].FIOPIN &= ~(pin.mask);
}

// Set pin as output 
__INLINE void Pin_Output(Pin_t pin) {
    LPC_GPIO[pin.port].FIODIR |= pin.mask;
}

// Set pin as input 
__INLINE void Pin_Input(Pin_t pin) {
    LPC_GPIO[pin.port].FIODIR &= ~(pin.mask);
}

// Set pin input mode
void Pin_Input_Mode(Pin_t pin, PinMode mode) {
// TODO: lock for concurrency
    if (mode < 4) {
		uint32_t port = pin.port + pin.address / 16;
		uint32_t shift = 2 * pin.address;
        LPC_PINCON->PINMODE[port] &= ~(3 << shift);
        LPC_PINCON->PINMODE[port] |= (mode << shift);
    }
}

// Read pin state 
__INLINE int Pin_Read (Pin_t pin) {
    return ((LPC_GPIO[pin.port].FIOPIN & pin.mask) ? 1 : 0); 
}
