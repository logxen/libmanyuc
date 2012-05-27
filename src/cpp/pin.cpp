/*
 * libmanyuc - pin cpp file
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

#include "libmanyuc.h"

Pin::Pin(PinName pin_name, PinMode mode) {
    this->pin = Pin_Get(pin_name);
    this->mode(mode);
}

// TODO: ver tema de inlines

int Pin::read() {
    return Pin_Read(this->pin);
}

void Pin::write(int value) {
    if (value) {
        Pin_On(this->pin);
    } else {
        Pin_Off(this->pin);
    }
}

void Pin::mode(PinMode mode) {
    switch (mode) {
    case Output:
        Pin_Output(this->pin);
        break;
    default:
        Pin_Input(this->pin);
        Pin_Mode(this->pin, mode);
    }
}

Pin &Pin::operator= (int value) {
    this->write(value);
    return *this;
}

Pin::operator int() {
    return this->read();
}

