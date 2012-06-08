/*
 * libmanyuc - LPC ADC file
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

#include "adc.h"
#include "io.h"

// To select the ADC Modes
const static int modes[] = { Alt1, Alt1, Alt1, Alt1, Alt3, Alt3, Alt2, Alt2 };
const static uint32_t names[] = { ADC0, ADC1, ADC2, ADC3, ADC4, ADC5, ADC6, ADC7 };

// Amount of ADC available
#define ADC_AMOUNT          8

// Power Register
#define ADC_POWER_BITMASK  ((uint32_t) 1 << 12)

// Control Register
#define ADC_CR_CH_SEL(n)    ((1 << n))  // Selects each channel
#define ADC_CR_CLKDIV(n)    ((n << 8))  // Sets the clock divider
#define ADC_CR_BURST        ((1 <<16))  // Sets the BURST signal
#define ADC_CR_ENABLE       ((1 <<21))  // ADC Enable
#define ADC_CR_START(s)     ((s <<24))  // Selects the start mode
#define ADC_CR_START_MASK   ((7 <<24))  // Mask for the start mode
#define ADC_CR_START_NOW    ((1 <<24))
#define ADC_CR_START_EINT0  ((2 <<24))
#define ADC_CR_START_CAP01  ((3 <<24))
#define ADC_CR_START_MAT01  ((4 <<24))
#define ADC_CR_START_MAT03  ((5 <<24))
#define ADC_CR_START_MAT10  ((6 <<24))
#define ADC_CR_START_MAT11  ((7 <<24))
#define ADC_CR_EDGE         ((1 <<27))  // Selects the start edge

// ADC Data Registers
#define ADC_DR_GET_RESULT(n)    (((n>>4)&0xFFF)) // Returns the result
#define ADC_DR_OVERRUN_FLAG     ((1 <<30))       // overrun flag
#define ADC_DR_DONE_FLAG        ((1 <<31))       // done flag

// Initializes de ADC.  To be used only once.
void ADC_Init() {

    // Power up ADC
    LPC_SC->PCONP |= ADC_POWER_BITMASK;

    // Reset the Control Register
    // This sets:
    // * all selections to 0
    // * the clock divider to 2 (12.5 MHz).
    // * the power bit to 1.
    LPC_ADC->ADCR = ADC_CR_CLKDIV(1) | ADC_CR_ENABLE;
}

AnalogIn_t AnalogIn_Init(PinName pin_name) {

    // Check if the global initialization is needed.
    if (!(LPC_SC->PCONP & ADC_POWER_BITMASK)) {
        ADC_Init();
    }

    AnalogIn_t analog_in = AnalogIn_Get(pin_name);
 
    // Set the pin bit function
    Pin_t pin = Pin_Get(pin_name);
    Pin_Input(pin);
    Pin_Mode(pin, PullNone);
    Pin_Mode(pin, modes[analog_in.channel]);

    return analog_in;
}

AnalogIn_t AnalogIn_Get(PinName pin_name) {
    // Find out the id number of the pin.
    // TODO: is there a better way of doing this?
    int id = 0;
    for (; id < ADC_AMOUNT; id++) {
        if (names[id] == pin_name) break;
    }
    AnalogIn_t analog_in = { id };
    return analog_in;
}


void static inline _analog_in_enable_channel(uint8_t channel) {
    // Enable the ADC channel in the ADC Control Register
    LPC_ADC->ADCR &= ~(0xFF);
    LPC_ADC->ADCR |= ADC_CR_CH_SEL(channel);
}

// Read one value and return it
uint32_t static inline _analog_in_read_one(uint8_t channel) {
    uint16_t result;
    LPC_ADC->ADCR |= ADC_CR_START_NOW;
    while (!(LPC_ADC->ADDR[channel] & ADC_DR_DONE_FLAG));
    return ADC_DR_GET_RESULT(LPC_ADC->ADDR[channel]);
}

// Read three values and return the median
uint32_t static inline _analog_in_read_three(uint8_t channel) {
    // Get 3 values
    uint16_t results[3];
    int i = 0;
    for (; i < 3; i++) {
        LPC_ADC->ADCR |= ADC_CR_START_NOW;
        // Wait until the result is here
        while (!(LPC_ADC->ADDR[channel] & ADC_DR_DONE_FLAG));
        results[i] = ADC_DR_GET_RESULT(LPC_ADC->ADDR[channel]);
    }
    // Return the median value of the result
    if (((results[0] > results[1]) && (results[0] < results[2])) || 
       ((results[0] < results[1]) && (results[0] > results[2]))) {
        return results[0];
    } else if (((results[1] > results[0]) && (results[1] < results[2])) ||
        ((results[1] < results[0]) && (results[1] > results[2]))) {
        return results[1];
    } else {
        return results[2];
    }
}

uint32_t AnalogIn_Read(AnalogIn_t pin, AnalogInMode mode) {
    _analog_in_enable_channel(pin.channel);
    if (mode == ADC_NORMAL) {
        return _analog_in_read_one(pin.channel);
    } else {
        return _analog_in_read_three(pin.channel);
    }
}

static ADC_Int_Func _analog_in_func = 0;
static uint8_t _analog_in_channel;
void AnalogIn_Attach(AnalogIn_t pin, AnalogInMode mode, ADC_Int_Func func) {
    // Store function
    _analog_in_func = func;
    _analog_in_channel = pin.channel;
    // Enable channel
    _analog_in_enable_channel(pin.channel);
    // Enable channel interrupt
    LPC_ADC->ADINTEN = ADC_CR_CH_SEL(pin.channel);
    // Start reading
    LPC_ADC->ADCR |= ADC_CR_START_NOW;
}

void ADC_IRQHandler(void) {
    uint32_t result = ADC_DR_GET_RESULT(LPC_ADC->ADDR[_analog_in_channel]);
    if (_analog_in_func) {
        _analog_in_func(result);
    }
    _analog_in_func = 0;
}


// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
