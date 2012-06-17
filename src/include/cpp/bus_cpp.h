/*
 * libmanyuc - bus cpp header file
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

#ifndef BUS_CPP_H
#define BUS_CPP_H

#include "io.h"
#include <stdint.h>

/** The pin class represents an extenal pin in the board,
 *  it can be used as input or output.
 *
 *  @author Margarita Manterola
 *  @date 2012
 */

class Bus {
private:
    Bus_t bus;
public:
    /** Bus Constructor.  A Bus is a group of pins that 
     *  can be quickly set all at the same time, or easily 
     *  set and read in binary.
     *  @param npins the amount of pins for the bus.
     *  @param ... a list of pins to be added to the bus.
     */
    Bus(int npins, ...);

    /** Bus destructor.
     *  Frees the memory allocated for the bus.
     */
    ~Bus() {
        Bus_Destroy(this->bus);
    }

    /** Sets the mode for the group of pins.
     *  The possible input/output modes or pin functions
     *  depend on the architecture.
     *  @param mode The mode to set for the pins.
     *  Available modes depend on the architecture.
     */
    void mode(PinMode mode) {
        PinBus_Mode(this->bus.pinBus, mode);
    }

    /** Writes a value to all pins. 
     *  @param value 0 turns the pins off, any other value turns them on.
     */
    void write_all(int value) {
        (value) ? PinBus_On(this->bus.pinBus): PinBus_Off(this->bus.pinBus);
    }

    /** Writes a value to the pins. 
     *  @param value A number to write in binary to the pins.
     */
    void write(unsigned int value) {
        Bus_Write(this->bus, value);
    }

    /** Reads the value of the pins.
     *  @return The value read from the pins, in binary form.
     */
    unsigned int read() {
        return Bus_Read(this->bus);
    }

    // Operator overloading

    /** Shorthand for write, sets the value to the pin. */
    Bus &operator= (int value) {
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
