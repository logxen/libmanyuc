/**************************************************************************//**
 * @defgroup IO Input and Output
 * @{ 
 * @brief    libmanyuc Input and Output definitions.
 * @date     May 2012
 * @author   Copyright (C) 2012 - Margarita Manterola Rivero
 *
 * @par
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * @par
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * @par
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, 
 * MA 02110-1301 USA
 *
 ******************************************************************************/

#ifndef IO_H
#define IO_H

#ifdef __cplusplus
extern "C" {
#endif

/** Opaque structure to hold pin information. 
 *  The data contained in the structure depends on the
 *  architecture. It should be created through Pin_Get. 
 */
typedef struct _pin_t Pin_t;

/** Creates the pin structure from the pin name. 
 *  @param pin_name One of the available pin names, 
 *  depending on the architecture.
 *  @return A structure that represents the pin.
 */
Pin_t Pin_Get(PinName pin_name);

/** Marks the pin as an output pin. 
 *  Pins have to be set as output to turn them on or off.
 *  @param pin A pin created through Pin_Get.
 */
void Pin_Output (Pin_t pin);

/** Marks the pin as an input pin. 
 *  Pins have to be set as input to read data from them.
 *  @param pin A pin created through Pin_Get.
 */
void Pin_Input (Pin_t pin);

/** Sets the mode for the pin.
 *  The possible input modes or pin functions 
 *  depend on the architecture.
 *  @param pin A pin created through Pin_Get.
 *  @param mode The mode to set for the pin.  
 *  Available modes depend on the architecture.
 */
void Pin_Mode (Pin_t pin, PinMode mode);

/** Turns the pin on. 
 *  @param pin A pin created through Pin_Get.
 */
void Pin_On (Pin_t pin);

/** Turns the pin off.
 *  @param pin A pin created through Pin_Get.
 */
void Pin_Off (Pin_t pin);

/** Reads the state of the pin.
 *  @param pin A pin created through Pin_Get.
 *  @return The state of the pin (0 or 1).
 */
int Pin_Read (Pin_t pin);

/** Opaque structure to hold a bus of pins information. 
 *  The data contained in the structure depends on the
 *  architecture. It should be created through PinBus_Get. 
 */
typedef struct _pinBus_t PinBus_t;

/** Creates a structure for the group of pins according 
 *  to the pin names. 
 *  @param pin_names An array of pin_names
 *  @param npins The number of pins in the array
 *  @return A structure that represents the group of pins.
 */
PinBus_t PinBus_Get(PinName* pin_names, int npins);

/** Marks all the pins in the bus as output pins. 
 *  @param bus A group of pins created through PinBus_Get.
 */
void PinBus_Output (PinBus_t bus);

/** Marks all the pins in the bus as input pins. 
 *  @param bus A group of pins created through PinBus_Get.
 */
void PinBus_Input (PinBus_t bus);

/** Sets the mode for the group of pins.
 *  The possible input modes or pin functions 
 *  depend on the architecture.
 *  @param bus A group of pins created through PinBus_Get.
 *  @param mode The mode to set for the pins.
 *  Available modes depend on the architecture.
 */
void PinBus_Mode (PinBus_t bus, PinMode mode);

/** Turns all the pins in the bus on. 
 *  @param bus A group of pins created through PinBus_Get.
 */
void PinBus_On (PinBus_t bus);

/** Turns all the pins in the bus off. 
 *  @param bus A group of pins created through PinBus_Get.
 */
void PinBus_Off (PinBus_t bus);








/** Wait an amount of seconds.
  * TODO: this shouldn't be here.
  */
void Delay (uint32_t dlyTicks);




//@}

#ifdef __cplusplus
}
#endif

#endif
