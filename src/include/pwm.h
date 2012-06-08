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

    typedef struct _pwm_pin_t PWMPin_t;
    PWMPin_t PWMPin_Get(PinName pin_name);
    void PWMPin_Set_Period_s(PWMPin_t pin, float s);
    void PWMPin_Set_Period_ms(PWMPin_t pin, float ms);
    void PWMPin_Set_Period_us(PWMPin_t pin, float us);
    void PWMPin_Set_Duty_Cycle(PWMPin_t pin, float duty);
    void PWMPin_Set_Cycle_Count(PWMPin_t pin, uint32_t count);
    float PWMPin_Get_Duty_Cycle(PWMPin_t pin);

//@}

#ifdef __cplusplus
}
#endif

#endif
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
