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

    /** Returns the current value set in the pin. 
     *  @return 0 if the pin is off, 1 if it is on.
     */
    int read() {
        return Pin_Read(this->pin);
    }

    /** Writes a value for the pin. 
     *  @param value 0 turns the pin off, any other value turns it on.
     */
    void write(int value) {
        (value) ? Pin_On(this->pin): Pin_Off(this->pin);
    }

    /** Sets the operation mode for the pin. 
     *  @param mode The mode to set for the pin.
     *  Available modes depend on the architecture.
     */
    void mode(PinMode mode) {
        Pin_Mode(this->pin, mode);
    }

    /** Toggles the value of the pin. */
    void toggle() {
        Pin_Toggle(this->pin);
    }

    // Interrupt methods

    /** Binds a function to be called when an interrupt occurrs on the
     *  pin. 
     *  @param function A function to attach to the pin interrupt.
     *  @param mode The mode for the pin interrupt (architecture
     *  dependent).
     */
    void attach(Int_Func function, IOIntMode mode) {
        Pin_Int_Attach(this->pin, function, mode);
    }

    /** Disables a pin interrupt that had been previously
     *  attached/enabled.
     *  @param mode The mode for the pin interrupt that had been attached.
     */
    void disable(IOIntMode mode) {
        Pin_Int_Disable(this->pin, mode);
    }
     
    /** Enables a pin interrupt that had been previously disabled.
     *  @param mode The mode for the pin interrupt that had been attached.
     */
    void enable(IOIntMode mode) {
        Pin_Int_Enable(this->pin, mode);
    }

    // Operator overloading

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
