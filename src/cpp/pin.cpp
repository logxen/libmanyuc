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

#include "pin_cpp.h"
#include <stdarg.h>

// Only the constructor is here, the rest are all inline functions.

Pin::Pin(PinName pin_name, uint32_t nmodes, ... ) {
    this->pin = Pin_Get(pin_name);

    if (nmodes == 0) {
        this->mode(Output);
    } else {
        va_list modes;
        va_start(modes, nmodes);
        for (uint32_t i = 0; i < nmodes; i++) {
            this->mode((PinMode) va_arg(modes, int));
        }
        va_end(modes);
    }
}


// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
