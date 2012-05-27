/*
 * libmanyuc - Architecture independent IO functions
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
#include "timers.h"
#include <stdlib.h>

/* *********************************************************** */
PinBus_t PinBus_Get(int npins, ...) {
    va_list pins;
    va_start(pins, npins);
    PinBus_t bus = vPinBus_Get(npins, pins);
    va_end(pins);
    return bus;
}

/* *********************************************************** */

Bus_t Bus_Get(int npins, ...) {

    Bus_t bus;

    // Get the pinBus
    va_list pins;
    va_start(pins, npins);
    bus.pinBus = vPinBus_Get(npins, pins);
    bus.npins = npins;
    va_end(pins);

    // Get all the pins
    va_start(pins, npins);
    bus.pins = malloc(sizeof(Pin_t) * npins);
    int i;
    for (i = 0; i < npins; i++) {
        bus.pins[i] = Pin_Get(va_arg(pins, uint32_t));
    }
    va_end(pins);

    return bus;
}

void Bus_Output(Bus_t bus) {
    PinBus_Output(bus.pinBus);
}

void Bus_Input(Bus_t bus) {
    PinBus_Input(bus.pinBus);
}

void Bus_Mode(Bus_t bus, PinMode mode) {
    PinBus_Mode(bus.pinBus, mode);
}

void Bus_Write(Bus_t bus, uint32_t data) {
    int i;
    for (i = 0; i < bus.npins; i++) {
        if (data & (1 << i))
            Pin_On(bus.pins[i]);
        else
            Pin_Off(bus.pins[i]);
    }
}

uint32_t Bus_Read(Bus_t bus) {
    uint32_t data = 0;
    int i;
    for (i = 0; i < bus.npins; i++) {
        data |= (Pin_Read(bus.pins[i]) << i);
    }
    return data;
}

void Bus_Destroy(Bus_t bus) {
    free(bus.pins);
}

/* *********************************************************** */

void Show_Error() {
    PinBus_t leds = PinBus_Get_Notification();
    PinBus_Output(leds);
    uint8_t i, j, l;
    while (1) {
        // . . . - - - . . .
        for (j = 0; j < 3; j++) {
            l = (j % 2) ? 3 : 1;
            for (i = 0; i < 3; i++) {
                PinBus_On(leds);
                wait(0.15 * l);
                PinBus_Off(leds);
                wait(0.2);
            }
            wait(0.2);
        }
        wait(1);
    }
}

/* *********************************************************** */

void Pin_All_On(Pin_t *pins, int n) {
    int i;
    for (i = 0; i < n; i++) {
        Pin_On(pins[i]);
    }
}

void Pin_All_Off(Pin_t *pins, int n) {
    int i;
    for (i = 0; i < n; i++) {
        Pin_Off(pins[i]);
    }
}

void Pin_Show_Byte(Pin_t *pins, int n, uint8_t byte) {
    int i;
    for (i = 0; i < n; i++) {
        if (byte & (1 << i))
            Pin_On(pins[i]);
        else
            Pin_Off(pins[i]);
    }
}


// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
