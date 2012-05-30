
#include "port.h"

volatile uint32_t msTicks;      /* counts 1ms timeTicks */
void SysTick_Handler(void) {
    msTicks++;          /* increment counter necessary in Delay() */
}

__INLINE void Delay(uint32_t dlyTicks) {
    uint32_t curTicks;
    curTicks = msTicks;
    while ((msTicks - curTicks) < dlyTicks);
}
