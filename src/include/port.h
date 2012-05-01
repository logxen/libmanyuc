/*
 * libmanyuc - port header file
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

#ifndef PORT_H
#define PORT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <portmacro.h>
#include <stdint.h>

void init();

typedef struct _pin_t Pin_t;
typedef struct _serial_t Serial_t;

Pin_t Pin_Get(PinName pin_name);
void Pin_On (Pin_t pin);
void Pin_Output (Pin_t pin);
void Pin_Off (Pin_t pin);
void Pin_Input (Pin_t pin);
void Pin_Input_Mode (Pin_t pin, PinMode mode);
int Pin_Read (Pin_t pin);

void Delay (uint32_t dlyTicks);

// Serial
typedef enum { BLOCKING, NONBLOCKING, BLOCK_WITH_TIMEOUT }
SerialTransferMode;


Serial_t Serial_Get(int number);
void Serial_Init(Serial_t port, int baudrate);
uint8_t Serial_Get_Byte(Serial_t port);
void Serial_Put_Byte(Serial_t port, uint8_t data);
uint32_t Serial_Put_Bytes(Serial_t port, uint8_t* data, uint32_t length,
SerialTransferMode mode);

#ifdef __cplusplus
}
#endif

#endif
