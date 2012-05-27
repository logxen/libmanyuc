/*
 * libmanyuc - LPC PWM File
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

// Power register
#define PWM_POWER_BITMASK  ((uint32_t) 1 << 1)

#define PWM_MCR_RESET_ON_MR0        ((uint32_t)(1<<1)) /* Reset when MR0 matches the counter */

#define PWM_TCR_COUNTER_ENABLE      ((uint32_t)(1<<0)) /* PWM Counter Enable */
#define PWM_TCR_COUNTER_RESET       ((uint32_t)(1<<1)) /* PWM Counter Reset */
#define PWM_TCR_PWM_ENABLE          ((uint32_t)(1<<3)) /* PWM Enable */



// Single vs Double edge configuration
#define PWM_PCR_PWMSEL(n)      ((uint32_t) (n==0) ? 0 : (1<<n))
// Enable vs Disable PWM output
#define PWM_PCR_PWMENA(n)      ((uint32_t) (1 << (n+8)))

const static uint8_t modes[] = { 0, Alt2, Alt1, Alt3 };

static uint8_t pwm_get_id(PinName pin) {

    if ((pin == ARM_P1_18) || (pin == ARM_P2_0)) {
        return 1;
    } else if ((pin == ARM_P1_20) || (pin == ARM_P2_1) || (pin == ARM_P3_25)) {
        return 2;
    } else if ((pin == ARM_P1_21) || (pin == ARM_P2_2) || (pin == ARM_P3_26)) {
        return 3;
    } else if ((pin == ARM_P1_23) || (pin == ARM_P2_3)) {
        return 4;
    } else if ((pin == ARM_P1_24) || (pin == ARM_P2_4)) {
        return 5;
    } else if ((pin == ARM_P1_26) || (pin == ARM_P2_5)) {
        return 6;
    }

    // If the pin received is not in the list, it's an error.
    Show_Error();
    return 0;
}

// external variable set on port.c
extern uint32_t PeripheralClock;

// internal function to set the period
inline void _pwm_set_period(uint32_t period) {
    LPC_PWM1->MR0 = period;
    LPC_PWM1->LER |= 1;
}

// static variable to know if the pwm was initialized or not
static uint8_t _pwm_initialized = 0;

// General initialization function, to be run only once.
inline void pwm_init() {

    // Clear all
    LPC_PWM1->IR = 0x39F;
    LPC_PWM1->TCR = 0;
    LPC_PWM1->CTCR = 0;
    LPC_PWM1->MCR = 0;
    LPC_PWM1->CCR = 0;
    LPC_PWM1->PCR = 0;
    LPC_PWM1->LER = 0;

    // Give power to the PWM
    LPC_SC->PCONP |= PWM_POWER_BITMASK;

    // Use as timer counter
    LPC_PWM1->CCR = 0;
    // Disable interrupts - Reset on match of MR0
    LPC_PWM1->MCR = PWM_MCR_RESET_ON_MR0;
    // Set prescale to 0
    LPC_PWM1->PR = 0;

    // Set default period: 0.02s
    _pwm_set_period(0.020 * PeripheralClock);

    // Enable PWM in the TCR
    LPC_PWM1->TCR = PWM_TCR_COUNTER_RESET;
    LPC_PWM1->TCR = PWM_TCR_COUNTER_ENABLE | PWM_TCR_PWM_ENABLE;

    _pwm_initialized = 1;
}


PWMPin_t PWMPin_Get(PinName pin_name) {

    PWMPin_t pwm_pin = { pwm_get_id(pin_name) };
    Pin_t pin = Pin_Get(pin_name);

    // Check if pwm has been initialized
    if (_pwm_initialized == 0) {
        pwm_init();
    }

    // Configure the pin for PWM
    Pin_Mode(pin, modes[pin.port]);

    // Set as single edge mode
    if (pwm_pin.id > 1) {
        LPC_PWM1->PCR &= ~(PWM_PCR_PWMSEL(pwm_pin.id));
    }

    // Enable the pwm output for this pin
    LPC_PWM1->PCR |= PWM_PCR_PWMENA(pwm_pin.id);

    // Default duty cycle
    PWMPin_Set_Duty_Cycle(pwm_pin, 0.5);
    return pwm_pin;
}

// Set period functions
void PWMPin_Set_Period_s(PWMPin_t pin, float s) {
    _pwm_set_period(s * PeripheralClock);
}
void PWMPin_Set_Period_ms(PWMPin_t pin, float ms) {
    _pwm_set_period(ms * PeripheralClock / 1000);
}
void PWMPin_Set_Period_us(PWMPin_t pin, float us) {
    _pwm_set_period(us * PeripheralClock / 1000000);
}

// Set duty cycle functions
void PWMPin_Set_Duty_Cycle(PWMPin_t pin, float duty) {
    PWMPin_Set_Cycle_Count(pin, LPC_PWM1->MR0 * duty);
}

void inline PWMPin_Set_Cycle_Count(PWMPin_t pin, uint32_t count) {
    if (pin.id < 4) {
        LPC_PWM1->MRL[pin.id - 1] = count;
    } else {
        LPC_PWM1->MRH[pin.id - 4] = count;
    }
    LPC_PWM1->LER |= (1 << pin.id);
}

float PWMPin_Get_Duty_Cycle(PWMPin_t pin) {
    if (pin.id < 4) {
        return LPC_PWM1->MRL[pin.id - 1] / LPC_PWM1->MR0;
    } else {
        return LPC_PWM1->MRH[pin.id - 4] / LPC_PWM1->MR0;
    }
}
