/* LPC1768 Startup Script */

.syntax unified
.thumb

.section ".interrupt_vector_table"
.global __interrupt_vector_table
/* This interrupt vector table gets pulled in by the linker script
 * into flash right before the startup code */
__interrupt_vector_table:
.long _end_stack
.long Reset_Handler
.long NMI_Handler
.long HardFault_Handler
.long MemManage_Handler
.long BusFault_Handler
.long UsageFault_Handler
.long 0
.long 0
.long 0
.long 0
.long SVC_Handler
.long DebugMon_Handler
.long 0
.long PendSV_Handler
.long SysTick_Handler
/* External interrupts */
.long WDT_IRQHandler
.long TIMER0_IRQHandler
.long TIMER1_IRQHandler
.long TIMER2_IRQHandler
.long TIMER3_IRQHandler
.long UART0_IRQHandler
.long UART1_IRQHandler
.long UART2_IRQHandler
.long UART3_IRQHandler
.long PWM1_IRQHandler
.long I2C0_IRQHandler
.long I2C1_IRQHandler
.long I2C2_IRQHandler
.long SPI_IRQHandler
.long SSP0_IRQHandler
.long SSP1_IRQHandler
.long PLL0_IRQHandler
.long RTC_IRQHandler
.long EINT0_IRQHandler
.long EINT1_IRQHandler
.long EINT2_IRQHandler
.long EINT3_IRQHandler
.long ADC_IRQHandler
.long BOD_IRQHandler
.long USB_IRQHandler
.long CAN_IRQHandler
.long DMA_IRQHandler
.long I2S_IRQHandler
.long ENET_IRQHandler
.long RIT_IRQHandler
.long MCPWM_IRQHandler
.long QEI_IRQHandler
.long PLL1_IRQHandler

/* Addresses for all of the interrupts handlers above, can be pointed to a
 * real IRQ handler instead of falling through to the startup code. */
    .weak   NMI_Handler
    .type   NMI_Handler, %function
NMI_Handler:

    .weak   HardFault_Handler
    .type   HardFault_Handler, %function
HardFault_Handler: 

    .weak   MemManage_Handler
    .type   MemManage_Handler, %function
MemManage_Handler: 

    .weak   BusFault_Handler
    .type   BusFault_Handler, %function
BusFault_Handler: 

    .weak   UsageFault_Handler
    .type   UsageFault_Handler, %function
UsageFault_Handler:

    .weak   SVC_Handler
    .type   SVC_Handler, %function
SVC_Handler:

    .weak   DebugMon_Handler
    .type   DebugMon_Handler, %function
DebugMon_Handler:

    .weak   PendSV_Handler
    .type   PendSV_Handler, %function
PendSV_Handler:

    .weak   SysTick_Handler
    .type   SysTick_Handler, %function
SysTick_Handler:

    .weak   WDT_IRQHandler
    .type   WDT_IRQHandler, %function
WDT_IRQHandler:

    .weak   TIMER0_IRQHandler
    .type   TIMER0_IRQHandler, %function
TIMER0_IRQHandler:

    .weak   TIMER1_IRQHandler
    .type   TIMER1_IRQHandler, %function
TIMER1_IRQHandler:

    .weak   TIMER2_IRQHandler
    .type   TIMER2_IRQHandler, %function
TIMER2_IRQHandler:

    .weak   TIMER3_IRQHandler
    .type   TIMER3_IRQHandler, %function
TIMER3_IRQHandler:

    .weak   UART0_IRQHandler
    .type   UART0_IRQHandler, %function
UART0_IRQHandler:

    .weak   UART1_IRQHandler
    .type   UART1_IRQHandler, %function
UART1_IRQHandler:

    .weak   UART2_IRQHandler
    .type   UART2_IRQHandler, %function
UART2_IRQHandler:

    .weak   UART3_IRQHandler
    .type   UART3_IRQHandler, %function
UART3_IRQHandler:

    .weak   PWM1_IRQHandler
    .type   PWM1_IRQHandler, %function
PWM1_IRQHandler:

    .weak   I2C0_IRQHandler
    .type   I2C0_IRQHandler, %function
I2C0_IRQHandler:

    .weak   I2C1_IRQHandler
    .type   I2C1_IRQHandler, %function
I2C1_IRQHandler:

    .weak   I2C2_IRQHandler
    .type   I2C2_IRQHandler, %function
I2C2_IRQHandler:

    .weak   SPI_IRQHandler
    .type   SPI_IRQHandler, %function
SPI_IRQHandler:

    .weak   SSP0_IRQHandler
    .type   SSP0_IRQHandler, %function
SSP0_IRQHandler:

    .weak   SSP1_IRQHandler
    .type   SSP1_IRQHandler, %function
SSP1_IRQHandler:

    .weak   PLL0_IRQHandler
    .type   PLL0_IRQHandler, %function
PLL0_IRQHandler:

    .weak   RTC_IRQHandler
    .type   RTC_IRQHandler, %function
RTC_IRQHandler:

    .weak   EINT0_IRQHandler
    .type   EINT0_IRQHandler, %function
EINT0_IRQHandler:

    .weak   EINT1_IRQHandler
    .type   EINT1_IRQHandler, %function
EINT1_IRQHandler:

    .weak   EINT2_IRQHandler
    .type   EINT2_IRQHandler, %function
EINT2_IRQHandler:

    .weak   EINT3_IRQHandler
    .type   EINT3_IRQHandler, %function
EINT3_IRQHandler:

    .weak   ADC_IRQHandler
    .type   ADC_IRQHandler, %function
ADC_IRQHandler:

    .weak   BOD_IRQHandler
    .type   BOD_IRQHandler, %function
BOD_IRQHandler:

    .weak   USB_IRQHandler
    .type   USB_IRQHandler, %function
USB_IRQHandler:

    .weak   CAN_IRQHandler
    .type   CAN_IRQHandler, %function
CAN_IRQHandler:

    .weak   DMA_IRQHandler
    .type   DMA_IRQHandler, %function
DMA_IRQHandler:	 

    .weak   I2S_IRQHandler
    .type   I2S_IRQHandler, %function
I2S_IRQHandler:

    .weak   ENET_IRQHandler
    .type   ENET_IRQHandler, %function
ENET_IRQHandler:

    .weak   RIT_IRQHandler
    .type   RIT_IRQHandler, %function
RIT_IRQHandler:

    .weak   MCPWM_IRQHandler
    .type   MCPWM_IRQHandler, %function
MCPWM_IRQHandler:

    .weak   QEI_IRQHandler
    .type   QEI_IRQHandler, %function
QEI_IRQHandler:

    .weak   PLL1_IRQHandler
    .type   PLL1_IRQHandler, %function
PLL1_IRQHandler:
    B       .

.section ".startup","x",%progbits
.thumb_func
.global _startup
.global Reset_Handler

Reset_Handler:
_startup:
	/* Clear the BSS section */ 
	mov r0, #0
	ldr r1, = _start_bss
	ldr r2, = _end_bss
	sub r2, #1
_loop:	cmp r1, r2
	str r0, [r1, #0]
	add r1, #4
	blo _loop 

	/* Jump to init() */
	ldr r0, =init
	blx r0

	/* Jump to main() */
	ldr r0, =main
	bx r0
	
.end
