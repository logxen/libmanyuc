/*
 * libmanyuc - ATSAM3 ADC file
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

#include "port.h"

// To select the ADC Modes
const static uint32_t names[] = { 
    ARM_AD0, ARM_AD1, ARM_AD2, ARM_AD3, ARM_AD4, ARM_AD5, ARM_AD6, ARM_AD7, 
    ARM_AD8, ARM_AD9, ARM_AD10, ARM_AD11, ARM_AD12, ARM_AD13, ARM_AD14 };

// Amount of ADC available
#define ADC_AMOUNT          8

// Power Register
#define ADC_POWER_BITMASK  ((uint32_t) 1 << 29)

// Control Register
#define ADC_CR_SWRST (1 << 0) // Software Reset 
#define ADC_CR_START (1 << 1) // Start Conversion 

// Mode Register
#define ADC_MR_TRGEN         (1 << 0)   // Trigger Enable 
#define ADC_MR_LOWRES        (1 << 4)   // Select Resolution 
#define ADC_MR_SLEEP         (1 << 5)   // Sleep Mode
#define ADC_MR_FWUP          (1 << 6)   // Fast Wake Up
#define ADC_MR_FREERUN       (1 << 7)   // Free Run Mode
#define ADC_MR_PRESCAL(n)   ((n << 8))  // Sets the clock divider
#define ADC_MR_STARTUP(n)   ((n << 16)) // Sets the number of startup periods
#define ADC_MR_SETTLING(n)  ((n << 20)) // Sets the number of settling periods
#define ADC_MR_ANACH         (1 << 23)  // Analog Change
#define ADC_MR_TRACKTIM(n)  ((n << 24)) // Sets the tracking time
#define ADC_MR_TRANSFER(n)  ((n << 28)) // Sets the transfer time
#define ADC_MR_USEQ          (1 << 31)  // Use Sequence Enable

#define ADC_MR_TRGSEL_EXT  (0 << 1) // External trigger 
#define ADC_MR_TRGSEL_TIO0 (1 << 1) // TIO Output of the Timer Counter Channel 0 
#define ADC_MR_TRGSEL_TIO1 (2 << 1) // TIO Output of the Timer Counter Channel 1 
#define ADC_MR_TRGSEL_TIO2 (3 << 1) // TIO Output of the Timer Counter Channel 2 
#define ADC_MR_TRGSEL_PWM0 (4 << 1) // PWM Event Line 0 
#define ADC_MR_TRGSEL_PWM1 (5 << 1) // PWM Event Line 1 

// Channel enable/disable registers
#define ADC_CHANNEL_MASK(n)   ((1 << n))  // Enables/Disables the channel

// Channel Data Register
#define ADC_CDR_GET_RESULT(n)   ((0xFFF & n))

// Initializes de ADC.  To be used only once.
static void ADC_Init() {

    // Power up ADC
    PMC->PMC_PCER0 |= ADC_POWER_BITMASK;

    // Reset the controller
    ADC->ADC_CR = ADC_CR_SWRST;

    // Reset the Control Register
    // This sets:
    // * Hardware triggers are disabled. Only software triggers.
    // * No trigger selected.
    // * High resolution selected.
    // * No sleep mode, no fast wake up, no free run.
    // * The clock divider to 4 (12 MHz).
    // * No analog change
    // * No sequence
    ADC->ADC_MR = ADC_MR_PRESCAL(1) | ADC_MR_STARTUP(8) | 
        ADC_MR_TRANSFER(1) | ADC_MR_TRACKTIM(0) | ADC_MR_SETTLING(3);
}

uint32_t AnalogIn_Get(PinName pin_name) {

    // Check if the global initialization is needed.
    if (!(PMC->PMC_PCER0 & ADC_POWER_BITMASK)) {
        ADC_Init();
    }

    // Find out the id number of the pin.
    // TODO: is there a better way of doing this?
    int id = 0;
    for (; id < ADC_AMOUNT; id++) {
        if (names[id] == pin_name) break;
    }

    // Set the pin bit function
    Pin_t pin = Pin_Get(pin_name);
    Pin_Input(pin);
    Pin_Mode(pin, PullNone);
    Pin_Mode(pin, PD);

    return id;
}

uint16_t AnalogIn_Read(uint32_t channel) {

    uint32_t channel_mask = ADC_CHANNEL_MASK(channel);

    // Enable the ADC channel in the ADC Control Register
    ADC->ADC_CHER = channel_mask;
    ADC->ADC_IER = channel_mask;

    // Start conversion
    ADC->ADC_CR |= ADC_CR_START;

    // Wait until the result is here
    while (!(ADC->ADC_ISR & channel_mask));
    wait(0.01);
    uint16_t result = ADC_CDR_GET_RESULT(ADC->ADC_CDR[channel]);

    // Disable the ADC channel in the ADC Control Register
    ADC->ADC_CHDR = channel_mask;

    return result;
}


// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
