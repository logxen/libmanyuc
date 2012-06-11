/*
 * libmanyuc - pin cpp header file
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

#ifndef PIN_CPP_H
#define PIN_CPP_H

#include "io.h"
#include <stdint.h>

/** The pin class represents an extenal pin in the board,
 *  it can be used as input or output.
 *
 *  @author Margarita Manterola
 *  @date 2012
 */

class Pin {
private:
    Pin_t pin;
public:
    /** Pin Constructor.
     *  @param pin_name the board name for the pin.
     *  @param nmodes the amount of modes to set for this pin.
     *  @param ... a list of modes that have to be set.
     *         Output is the default mode.
     *         Other modes depend on the microcontroller.
     */
    Pin(PinName pin_name, uint32_t nmodes = 0, ...);

    /** Returns the current value set in the pin. */
    int read() {
        return Pin_Read(this->pin);
    }

    /** Writes a value for the pin. */
    void write(int value) {
        (value) ? Pin_On(this->pin): Pin_Off(this->pin);
    }

    /** Sets the operation mode for the pin. */
    void mode(PinMode mode) {
        Pin_Mode(this->pin, mode);
    }

    /** Shorthand for write, sets the value to the pin. */
    Pin &operator= (int value) {
        this->write(value);
        return *this;
    }

    /** Shorthand for read, returns the value of the pin. */
    operator int() {
        return this->read();
    }
};

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
