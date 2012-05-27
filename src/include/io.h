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

#include <stdarg.h>

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
    void Pin_Output(Pin_t pin);

    /** Marks the pin as an input pin.
     *  Pins have to be set as input to read data from them.
     *  @param pin A pin created through Pin_Get.
     */
    void Pin_Input(Pin_t pin);

    /** Sets the mode for the pin.
     *  The possible input modes or pin functions
     *  depend on the architecture.
     *  @param pin A pin created through Pin_Get.
     *  @param mode The mode to set for the pin.
     *  Available modes depend on the architecture.
     */
    void Pin_Mode(Pin_t pin, PinMode mode);

    /** Turns the pin on.
     *  @param pin A pin created through Pin_Get.
     */
    void Pin_On(Pin_t pin);

    /** Turns the pin off.
     *  @param pin A pin created through Pin_Get.
     */
    void Pin_Off(Pin_t pin);

    /** Toggles the pin state.
     *  @param pin A pin created through Pin_Get.
     */
    void Pin_Toggle(Pin_t pin);


    /** Reads the state of the pin.
     *  @param pin A pin created through Pin_Get.
     *  @return The state of the pin (0 or 1).
     */
    int Pin_Read(Pin_t pin);

    /* *********************************************************** */

    /** Attach a function to a pin interrupt. If necessary, this function
     * enables IO interrupts and enables this particular pin as an
     * interrupt source. The attached function will be called when the
     * interrupt is activated.  The available modes for the interrupt
     * depend on the architecture.
     *
     * @param pin Any pin that can generate interrupts.
     * @param function A function to attach to the pin interrupt.
     * @param mode The mode for the pin interrupt (architecture
     * dependent).
     */
    void Pin_Int_Attach(Pin_t pin, void(*function)(void), IOIntMode mode);

    /** Disables a pin interrupt that had been previously
     * attached/enabled.
     * @param pin A pin that had an interrupt function attached.
     * @param mode The mode for the pin interrupt that had been attached.
     */
    void Pin_Int_Disable(Pin_t pin, IOIntMode mode);

    /** Enables the interrupt on a certain pin and mode.  It only makes
     * sense to call this function when the interrupt had been previously
     * disabled.
     * @param pin A pin that had an interrupt function attached that was
     * disabled.
     * @param mode The mode for the pin interrupt that had been attached.
     */
    void Pin_Int_Enable(Pin_t pin, IOIntMode mode);

    /* *********************************************************** */

    /** Opaque structure to hold a group of pins information.
     *  The PinBus structure is only useful when performing the
     *  same operation on all of the pins. To read/write
     *  different data to a group of pins, use the Bus structure.
     *
     *  The data contained in the structure depends on the
     *  architecture. It should be created through PinBus_Get.
     */
    typedef struct _pinBus_t PinBus_t;

    /** Creates a structure for the group of pins according
     *  to the pin names.
     *  @param npins The number of pins to be grouped.
     *  @param ... A variable list of pins, must be exactly npins.
     *  @return A structure that represents the group of pins.
     */
    PinBus_t PinBus_Get(int npins, ...);

    /** Variadic version of PinBus_Get. */
    PinBus_t vPinBus_Get(int npins, va_list pins);

    /** Marks all the pins in the bus as output pins.
     *  @param bus A group of pins created through PinBus_Get.
     */
    void PinBus_Output(PinBus_t bus);

    /** Marks all the pins in the bus as input pins.
     *  @param bus A group of pins created through PinBus_Get.
     */
    void PinBus_Input(PinBus_t bus);

    /** Sets the mode for the group of pins.
     *  The possible input modes or pin functions
     *  depend on the architecture.
     *  @param bus A group of pins created through PinBus_Get.
     *  @param mode The mode to set for the pins.
     *  Available modes depend on the architecture.
     */
    void PinBus_Mode(PinBus_t bus, PinMode mode);

    /** Turns all the pins in the bus on.
     *  @param bus A group of pins created through PinBus_Get.
     */
    void PinBus_On(PinBus_t bus);

    /** Turns all the pins in the bus off.
     *  @param bus A group of pins created through PinBus_Get.
     */
    void PinBus_Off(PinBus_t bus);

    /** Returns a PinBus with the leds that exist in this arch.
     *  @return A PinBus that has the leds for this arch.
     */
    PinBus_t PinBus_Get_Notification();

    /* *********************************************************** */

    /** Structure to hold the bus information.
     *  The Bus structure allows a user to read and write to
     *  up to 32 bytes at the same time.
     *
     *  The structure is architecture independent and
     *  should be created through Bus_Get.
     */
    typedef struct _bus_t {
        PinBus_t pinBus;
        uint32_t npins;
        Pin_t *pins;
    } Bus_t;

    /** Creates a structure for the bus, according to the pin
     *  names.  The order of the pins is the one that will be
     *  used when reading or writing to the bus. The first pin
     *  will always be the least significant bit. No more than
     *  32 pins will be taken into account.
     *
     *  @param npins The number of pins to be grouped.
     *  @param ... A variable list of pins, must be exactly npins.
     *  @return A structure that represents the group of pins.
     */
    Bus_t Bus_Get(int npins, ...);
//void Bus_Get(int npins, ...);

    /** Sets the bus as output.
     *  @param bus A bus created through Bus_Get.
     */
    void Bus_Output(Bus_t bus);

    /** Sets the bus as input.
     *  @param bus A bus created through Bus_Get.
     */
    void Bus_Input(Bus_t bus);

    /** Sets the mode for the bus.
     *  The possible input modes or pin functions
     *  depend on the architecture.
     *  @param bus A bus created through Bus_Get.
     *  @param mode The mode to set for the pins.
     *  Available modes depend on the architecture.
     */
    void Bus_Mode(Bus_t bus, PinMode mode);

    /** Writes data to the bus. Each set bit in data will
     *  result in a on pin, each unset bit will result in an
     *  off pin. The order of the pins is set when
     *  constructing the bus.
     *
     *  @param bus A bus created through Bus_Get.
     *  @param data The data to be set to the bits.
     */
    void Bus_Write(Bus_t bus, uint32_t data);

    /** Reads data from the bus. Each pin read as on will result
     * in a set bit in data, each pin read as off will result in
     * an unset bit. The order of the pins is set when
     * constructing the bus.
     *
     * @param bus A bus created through Bus_Get.
     * @return the bits read from the bus.
     */
    uint32_t Bus_Read(Bus_t bus);

    /** Frees the dynamic memory used by the Bus_t structure. */
    void Bus_Destroy(Bus_t bus);

    /* *********************************************************** */


    uint32_t AnalogIn_Get(PinName pin_name);
    uint16_t AnalogIn_Read(uint32_t channel);


    /* *********************************************************** */

    typedef struct _pwm_pin_t PWMPin_t;
    PWMPin_t PWMPin_Get(PinName pin_name);
    void PWMPin_Set_Period_s(PWMPin_t pin, float s);
    void PWMPin_Set_Period_ms(PWMPin_t pin, float ms);
    void PWMPin_Set_Period_us(PWMPin_t pin, float us);
    void PWMPin_Set_Duty_Cycle(PWMPin_t pin, float duty);
    void PWMPin_Set_Cycle_Count(PWMPin_t pin, uint32_t count);
    float PWMPin_Get_Duty_Cycle(PWMPin_t pin);

    /* *********************************************************** */

    /** Display an error with the arch leds.  Show's SOS in morse. */
    void Show_Error();

    /** Wait an amount of seconds.
      * TODO: this shouldn't be here.
      */
    void Delay(uint32_t dlyTicks);




//@}

#ifdef __cplusplus
}
#endif

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
