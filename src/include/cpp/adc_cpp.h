/*
 * libmanyuc - analogin cpp header file
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

#ifndef ANALOGIN_CPP_H
#define ANALOGIN_CPP_H

#include "adc.h"
#include <stdint.h>

/** The analogin class represents an extenal analogin in the board,
 *  it can be used as input or output.
 *
 *  @author Margarita Manterola
 *  @date 2012
 */

class AnalogIn {
private:
    AnalogIn_t pin;
public:
    /** AnalogIn Constructor.
     *  @param pin_name the board name for the pin.
     *  The pin must be an ADC enabled pin, or an error is shown. 
     *  Tne pin is initialized so that it can be used as an ADC input.
     */
    AnalogIn(PinName pin_name) {
        this->pin = AnalogIn_Init(pin_name);
    }

    /** Returns the current value read on the pin.
     *  @param mode The mode used to read. Basic modes are: ADC_NORMAL
     *              and ADC_INTERRUPT. Other modes are architecture 
     *              dependent.
     *  @return the value read from the ADC.
     */
    unsigned int read(AnalogInMode mode) {
        return AnalogIn_Read(this->pin);
    }

    // Interrupt methods

    /** Attaches a function to be called when the conversion done
     *  on pin is finished. It does not start the converstion. 
     *  To start the conversion, read should be called, with
     *  ADC_INTERRUPT mode.
     */
    void attach(ADC_Int_Func function) {
        AnalogIn_Attach(this->pin, function);
    }

    /** Detaches the interrupt that had been previously
     *  attached.
     */
    void detach() {
        AnalogIn_Detach(this->pin);
    }
     

    // Operator overloading

    /** Shorthand for read, returns the value of the pin in normal mode. */
    operator int() {
        return this->read(ADC_NORMAL);
    }

    // Static methods

    /** Starts reading all the attached pins, calling the associated
     *  functions for each of them
     *  @param speed A value to set the speed for the ADC conversion.
     *               Architecture dependent.
     */
    static void read_all(unsigned int speed) {
        AnalogIn_Read_All(speed);
    }

    /** Stop reading from many pins at the same time.
     */
    static void stop_reading() {
        AnalogIn_Stop_Reading();
    }

};

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
