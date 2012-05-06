

#include "LPC17xx.h"
#include "portmacro.h"

#define CLOCK_SETUP           1
#define SCS_Val               0x00000020
#define CLKSRCSEL_Val         0x00000001
#define PLL0_SETUP            1
#define PLL0CFG_Val           0x00050063
#define PLL1_SETUP            1
#define PLL1CFG_Val           0x00000023
#define CCLKCFG_Val           0x00000003
#define USBCLKCFG_Val         0x00000000
#define PCLKSEL0_Val          0x00000000
#define PCLKSEL1_Val          0x00000000
#define PCONP_Val             0x042887DE
#define CLKOUTCFG_Val         0x00000000

#define XTAL        (12000000UL)        /* Oscillator frequency               */
#define OSC_CLK     (      XTAL)        /* Main oscillator frequency          */
#define RTC_CLK     (   32768UL)        /* RTC oscillator frequency           */
#define IRC_OSC     ( 4000000UL)        /* Internal RC oscillator frequency   */

/* F_cco0 = (2 * M * F_in) / N  */
#define __M               (((PLL0CFG_Val      ) & 0x7FFF) + 1)
#define __N               (((PLL0CFG_Val >> 16) & 0x00FF) + 1)
#define __FCCO(__F_IN)    ((2 * __M * __F_IN) / __N)
#define __CCLK_DIV        (((CCLKCFG_Val      ) & 0x00FF) + 1)

/* Determine core clock frequency according to settings */
 #if (PLL0_SETUP)
    #if   ((CLKSRCSEL_Val & 0x03) == 1)
        #define __CORE_CLK (__FCCO(OSC_CLK) / __CCLK_DIV)
    #elif ((CLKSRCSEL_Val & 0x03) == 2)
        #define __CORE_CLK (__FCCO(RTC_CLK) / __CCLK_DIV)
    #else
        #define __CORE_CLK (__FCCO(IRC_OSC) / __CCLK_DIV)
    #endif
 #else
    #if   ((CLKSRCSEL_Val & 0x03) == 1)
        #define __CORE_CLK (OSC_CLK         / __CCLK_DIV)
    #elif ((CLKSRCSEL_Val & 0x03) == 2)
        #define __CORE_CLK (RTC_CLK         / __CCLK_DIV)
    #else
        #define __CORE_CLK (IRC_OSC         / __CCLK_DIV)
    #endif
 #endif


/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/

uint32_t SystemCoreClock;/*!< System Clock Frequency (Core Clock)*/
void SystemCoreClockUpdate (void)            /* Get Core Clock Frequency      */
{
  SystemCoreClock = __CORE_CLK;
  /* Determine clock frequency according to clock register values             */
  if (((LPC_SC->PLL0STAT >> 24) & 3) == 3) { /* If PLL0 enabled and connected */
    switch (LPC_SC->CLKSRCSEL & 0x03) {
      case 0:                                /* Int. RC oscillator => PLL0    */
      case 3:                                /* Reserved, default to Int. RC  */
        SystemCoreClock = (IRC_OSC *
                          ((2 * ((LPC_SC->PLL0STAT & 0x7FFF) + 1)))  /
                          (((LPC_SC->PLL0STAT >> 16) & 0xFF) + 1)    /
                          ((LPC_SC->CCLKCFG & 0xFF)+ 1));
        break;
      case 1:                                /* Main oscillator => PLL0       */
        SystemCoreClock = (OSC_CLK *
                          ((2 * ((LPC_SC->PLL0STAT & 0x7FFF) + 1)))  /
                          (((LPC_SC->PLL0STAT >> 16) & 0xFF) + 1)    /
                          ((LPC_SC->CCLKCFG & 0xFF)+ 1));
        break;
      case 2:                                /* RTC oscillator => PLL0        */
        SystemCoreClock = (RTC_CLK *
                          ((2 * ((LPC_SC->PLL0STAT & 0x7FFF) + 1)))  /
                          (((LPC_SC->PLL0STAT >> 16) & 0xFF) + 1)    /
                          ((LPC_SC->CCLKCFG & 0xFF)+ 1));
        break;
    }
  } else {
    switch (LPC_SC->CLKSRCSEL & 0x03) {
      case 0:                                /* Int. RC oscillator => PLL0    */
      case 3:                                /* Reserved, default to Int. RC  */
        SystemCoreClock = IRC_OSC / ((LPC_SC->CCLKCFG & 0xFF)+ 1);
        break;
      case 1:                                /* Main oscillator => PLL0       */
        SystemCoreClock = OSC_CLK / ((LPC_SC->CCLKCFG & 0xFF)+ 1);
        break;
      case 2:                                /* RTC oscillator => PLL0        */
        SystemCoreClock = RTC_CLK / ((LPC_SC->CCLKCFG & 0xFF)+ 1);
        break;
    }
  }

}


// Used for initializing global variables
extern unsigned int _start_data;
extern unsigned int _end_data;
extern unsigned int _start_datai;
extern unsigned int _end_datai;

void init(void) {
	/* Based on CMSIS SystemInit() for LPC17xx */
	/* Also see chapters 3 and 4 of LPC17xx User Manual, UM10360 */

	/* SCS: OSCRANGE=1 (12MHz on mbed), OSCEN=1 */
	LPC_SC->SCS = 0x20;
	/* Wait for the main oscillator to ready */
	while (!(LPC_SC->SCS & (1<<6)))
		;
	
	/* CLKSRCSEL: CLKSRC=01 for main oscillator as PLL0 source */
	LPC_SC->CLKSRCSEL = 0x01;

	/* CCLKCFG: CCLKSEL = 3, PLL0 is divided by 4 to provide CPU clock */
	LPC_SC->CCLKCFG = 0x03;
	
	/* PCKSEL0 and PCKSEL1 = 00, all peripherals get CCLK/4 */ 
	LPC_SC->PCLKSEL0 = 0x0;
	LPC_SC->PCLKSEL1 = 0x0;

	/* PLL0 Configuration, taken from CMSIS LPC17xx example */
	LPC_SC->PLL0CFG = 0x00050063;
	/* PLL Feed */
	LPC_SC->PLL0FEED = 0xAA;
	LPC_SC->PLL0FEED = 0x55;
	/* Enable PLL0 */
	LPC_SC->PLL0CON = 0x01;
	/* PLL Feed */
	LPC_SC->PLL0FEED = 0xAA;
	LPC_SC->PLL0FEED = 0x55;
	/* Wait for PLL0 lock */
	while (!(LPC_SC->PLL0STAT & (1<<26)))
		;
	/* Enable and connect PLL0 */
	LPC_SC->PLL0CON = 0x03;
	/* PLL Feed */
	LPC_SC->PLL0FEED = 0xAA;
	LPC_SC->PLL0FEED = 0x55;
	/* Wait for PLL1 enable and connect */
	while (!(LPC_SC->PLL0STAT & ((1<<25) | (1<<24))))
		;

	/* PLL1 Configuration, taken from CMSIS LPC17xx example */
	LPC_SC->PLL1CFG = 0x00000023;
	/* PLL Feed */
	LPC_SC->PLL1FEED = 0xAA;
	LPC_SC->PLL1FEED = 0x55;
	/* Enable PLL1 */
	LPC_SC->PLL1CON = 0x01;
	/* PLL Feed */
	LPC_SC->PLL1FEED = 0xAA;
	LPC_SC->PLL1FEED = 0x55;
	/* Wait for PLL1 lock */
	while (!(LPC_SC->PLL1STAT & (1<<10)))
		;
	/* Enable and connect PLL1 */
	LPC_SC->PLL1CON = 0x03;
	/* PLL Feed */
	LPC_SC->PLL1FEED = 0xAA;
	LPC_SC->PLL1FEED = 0x55;
	/* Wait for PLL1 enable and connect */
	while (!(LPC_SC->PLL1STAT & ((1<<9) | (1<<8))))
		;

	/* Additional settings */
	//LPC_SC->USBCLKCFG = ...;
	//LPC_SC->PCONP = ...;
	//LPC_SC->CLKOUTCFG = ...;
	//LPC_SC->FLASHCFG = ...;

	// Initialize Global Variables
    uint32_t* data_begin  = (uint32_t*) &_start_data;
    uint32_t* data_end    = (uint32_t*) &_end_data;
    uint32_t* datai_begin = (uint32_t*) &_start_datai;
    uint32_t* datai_end   = (uint32_t*) &_end_datai;
    while(data_begin < data_end)
    {
        *data_begin = *datai_begin;
        data_begin++;
        datai_begin++;
    }

    SystemCoreClockUpdate();

    if (SysTick_Config(SystemCoreClock / 1000)) {   /* Setup SysTick Timer for 1 msec interrupts  */
        while (1);              /* Capture error */
    }

}

/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
volatile uint32_t msTicks;      /* counts 1ms timeTicks */
void SysTick_Handler(void) {
    msTicks++;          /* increment counter necessary in Delay() */
}

/*------------------------------------------------------------------------------
  delays number of tick Systicks (happens every 1 ms)
 *------------------------------------------------------------------------------*/
__INLINE void Delay (uint32_t dlyTicks) {
    uint32_t curTicks;
    curTicks = msTicks;
    while ((msTicks - curTicks) < dlyTicks);
}

