/*
 * libmanyuc - Template ADC file
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

// Create and initialize an AnalogIn structure
AnalogIn_t AnalogIn_Init(PinName pin_name) {

    // Create an AnalogIn structure
    AnalogIn_t analog_in = AnalogIn_Get(pin_name);
 

    // Return the structure
    return analog_in;
}

AnalogIn_t AnalogIn_Get(PinName pin_name) {
    // Populate the structure as apropriate
    AnalogIn_t analog_in;
    return analog_in;
}

// Read values according to the different possibilities
uint32_t AnalogIn_Read(AnalogIn_t pin, AnalogInMode mode) {

    return 0;
}

// Store the AnalogIn function to be called when INTERRUPT mode is
// resquested.
void AnalogIn_Attach(AnalogIn_t pin, ADC_Int_Func func) {

}

// Detach the function for this pin
void AnalogIn_Detach(AnalogIn_t pin) {

}

// Read values continuously
void AnalogIn_Read_All(uint32_t speed) {

}

// Stop reading values
void AnalogIn_Stop_Reading() {

}

// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
