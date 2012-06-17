/**************************************************************************//**
 * @defgroup PWM Pulse Width Modulation
 * @{
 * @brief    libmanyuc Pulse Width Modulation definitions
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

#ifndef PWM_H
#define PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "board.h"


    /** Opaque structure to hold pwm pin information.
     *  The data contained in the structure depends on the
     *  architecture. It should be created through PWMPin_Get or 
     *  PWMPin_Init.
     */
    typedef struct _pwm_pin_t PWMPin_t;

    /** Initializes the PWMPin_t structure and starts creating
     *  the default PWM pulse (50% duty cicle).
     *  @param pin_name The pin on which the PWM cycle should be generated.
     *                  It must be a PWM enabled pin, or an error is shown.
     */
    PWMPin_t PWMPin_Init(PinName pin_name);

    /** Creates the PWMPin_t structure for the pin. No initialization is
     *  done for the pin itself.
     *  @param pin_name The pin on which the PWM cycle should be generated.
     *                  It must be a PWM enabled pin, or an error is shown.
     */ 
    PWMPin_t PWMPin_Get(PinName pin_name);

    /** Sets the period of the PWM signal.
     *  @param pin The pin affected. Should be created by Pin_Init or Pin_Get
     *  @param s The period of the signal, in seconds.
     */
    void PWMPin_Set_Period_s(PWMPin_t pin, float s);

    /** Sets the period of the PWM signal.
     *  @param pin The pin affected. Should be created by Pin_Init or Pin_Get
     *  @param s The period of the signal, in seconds.
     */
    void PWMPin_Set_Period_ms(PWMPin_t pin, float ms);

    /** Sets the period of the PWM signal.
     *  @param pin The pin affected. Should be created by Pin_Init or Pin_Get
     *  @param ms The period of the signal, in milliseconds.
     */
    void PWMPin_Set_Period_ms(PWMPin_t pin, float ms);

    /** Sets the period of the PWM signal.
     *  @param pin The pin affected. Should be created by Pin_Init or Pin_Get
     *  @param us The period of the signal, in microseconds.
     */
    void PWMPin_Set_Period_us(PWMPin_t pin, float us);

    /** Sets the duty cycle of the PWM signal.
     *  @param pin The pin affected. Should be created by Pin_Init or Pin_Get
     *  @param duty The duty cycle to set. Values should be between 0 and 1. 
     *  0 means always off, 1 means always on. 
     */
    void PWMPin_Set_Duty_Cycle(PWMPin_t pin, float duty);

    /** Sets the exact cycle count, the meaning of this value is
     *  architecture dependant. 
     *  @param pin The pin affected. Should be created by Pin_Init or Pin_Get
     *  @param count The amount of cycles that the signal should be on.
     */
    void PWMPin_Set_Cycle_Count(PWMPin_t pin, uint32_t count);

    /** Returns the currently set duty cycle.
     *  @param pin The pin affected. Should be created by Pin_Init or Pin_Get
     *  @return The currently set duty cycle for the pin.
     */
    float PWMPin_Get_Duty_Cycle(PWMPin_t pin);

//@}

#ifdef __cplusplus
}
#endif

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
