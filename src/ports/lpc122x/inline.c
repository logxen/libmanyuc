/*
 * libmanyuc - Template inline functions
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

// This function probably deserve to be inline. In case they don't, they
// should be moved to the apropriate file


// Switch Pin On
static inline void Pin_On(struct _pin_t pin) {
}

// Switch Pin Off
static inline void Pin_Off(struct _pin_t pin) {
}

// Toggle Pin State
static inline void Pin_Toggle(struct _pin_t pin) {
}

// Read pin state
static inline int Pin_Read(struct _pin_t pin) {
    return 0;
}

// Set pin as output
static inline void Pin_Output(struct _pin_t pin) {
}

// Set pin as input
static inline void Pin_Input(struct _pin_t pin) {
}

// Switch PinBus On
static inline void PinBus_On(struct _pinBus_t bus) {
}

// Switch PinBus Off
static inline void PinBus_Off(struct _pinBus_t bus) {
}

// Set PinBus as Output
static inline void PinBus_Output(struct _pinBus_t bus) {
}

// Set PinBus as Input
static inline void PinBus_Input(struct _pinBus_t bus) {
}


// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
