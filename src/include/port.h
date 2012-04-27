#ifndef PORT_H
#define PORT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <portmacro.h>
#include <stdint.h>

typedef struct _pin_t Pin_t;

void led();

Pin_t Pin_Get(PinName pin_name);
void Pin_On (Pin_t pin);
void Pin_Output (Pin_t pin);
void Pin_Off (Pin_t pin);
void Pin_Input (Pin_t pin);
int Pin_Read (Pin_t pin);

void Delay (uint32_t dlyTicks);

#ifdef __cplusplus
}
#endif

#endif
