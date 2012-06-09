/**************************************************************************//**
 * @defgroup ADC Analog Digital Converter
 * @{
 * @brief    libmanyuc Analog Digital Converter definitions
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

#ifndef ADC_H
#define ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include "board.h"

    /** Opaque structure to hold ADC information.
     *  The data contained in the structure depends on the
     *  architecture. It should be created through 
     *  AnalogIn_Init or AnalogIn_Get.
     */
    typedef struct _analog_in_t AnalogIn_t;


    /** Type for functions passed to AnalogIn_Attach.
     *  It receives the value converted through the ADC.
     */
    typedef void (*ADC_Int_Func)(uint32_t);

    /** Returns a structure with the information necessary to read
     *  from this pin. The pin must be an ADC enabled pin, or an 
     *  error is shown. Tne pin is initialized so that it can be used
     *  as an ADC input.
     */
    AnalogIn_t AnalogIn_Init(PinName pin_name);

    /** Returns a structure with the information necessary to read
     *  from this pin. The pin must be an ADC enabled pin, or an 
     *  error is shown. No initialization is performed.
     */
    AnalogIn_t AnalogIn_Get(PinName pin_name);

    /** Returns a value read from the ADC pin specified.
     * @param pin The pin from which to read. Should be constructed 
     *            through AnalogIn_Init or AnalogIn_Get.
     * @param mode The mode used to read. Architecture dependent.
     * @return the value read from the ADC.
     */
    uint32_t AnalogIn_Read(AnalogIn_t pin, AnalogInMode mode);

    /** Attaches a function to be called when the conversion done
     *  on pin is finished. It does not start the converstion. 
     *  To start the converstion AnalogIn_Read should be called, with
     *  ADC_INTERRUPT mode.
     *  @param pin The pin from which to read. Should be constructed 
     *             through AnalogIn_Init or AnalogIn_Get.
     */
    void AnalogIn_Attach(AnalogIn_t pin, ADC_Int_Func func);

    /** Detaches the function associated to this pin.
     * @param pin The pin to which the desired function is attached.
     */
    void AnalogIn_Detach(AnalogIn_t pin);

    /** Starts reading all the attached pins, calling the associated
     *  functions for each of them
     *  @param speed A value to set the speed for the ADC conversion.
     *               Architecture dependent.
     */
    void AnalogIn_Read_All(uint32_t speed);
//@}

#ifdef __cplusplus
}
#endif

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
