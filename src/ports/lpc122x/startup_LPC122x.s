/* LPC1227 Startup Script */

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
.long 0
.long 0
.long 0
.long 0
.long 0
.long 0
.long 0
.long SVC_Handler
.long 0
.long 0
.long PendSV_Handler
.long SysTick_Handler
/* External interrupts */
.long WAKEUP_IRQHandler         /* 16+ 0: Wakeup PIO0.0 */
.long WAKEUP_IRQHandler         /* 16+ 1: Wakeup PIO0.1 */
.long WAKEUP_IRQHandler         /* 16+ 2: Wakeup PIO0.2 */
.long WAKEUP_IRQHandler         /* 16+ 3: Wakeup PIO0.3 */
.long WAKEUP_IRQHandler         /* 16+ 4: Wakeup PIO0.4 */
.long WAKEUP_IRQHandler         /* 16+ 5: Wakeup PIO0.5 */
.long WAKEUP_IRQHandler         /* 16+ 6: Wakeup PIO0.6 */
.long WAKEUP_IRQHandler         /* 16+ 7: Wakeup PIO0.7 */
.long WAKEUP_IRQHandler         /* 16+ 8: Wakeup PIO0.8 */
.long WAKEUP_IRQHandler         /* 16+ 9: Wakeup PIO0.9 */
.long WAKEUP_IRQHandler         /* 16+10: Wakeup PIO0.10 */
.long WAKEUP_IRQHandler         /* 16+11: Wakeup PIO0.11 */
.long I2C_IRQHandler
.long TIMER16_0_IRQHandler
.long TIMER16_1_IRQHandler
.long TIMER32_0_IRQHandler
.long TIMER32_1_IRQHandler
.long SSP_IRQHandler
.long UART0_IRQHandler
.long UART1_IRQHandler
.long COMP_IRQHandler
.long ADC_IRQHandler
.long WDT_IRQHandler
.long BOD_IRQHandler
.long 0
.long PIOINT0_IRQHandler
.long PIOINT1_IRQHandler
.long PIOINT2_IRQHandler
.long 0
.long DMA_IRQHandler
.long RTC_IRQHandler

/* Addresses for all of the interrupts handlers above, can be pointed to a
 * real IRQ handler instead of falling through to the startup code. */
    .weak   HardFault_Handler
    .type   HardFault_Handler, %function
HardFault_Handler:

    .weak   SVC_Handler
    .type   SVC_Handler, %function
SVC_Handler:

    .weak   PendSV_Handler
    .type   PendSV_Handler, %function
PendSV_Handler:

    .weak   SysTick_Handler
    .type   SysTick_Handler, %function
SysTick_Handler:

    .weak   NMI_Handler
    .type   NMI_Handler, %function
NMI_Handler:

    .weak   WAKEUP_IRQHandler
    .type   WAKEUP_IRQHandler, %function
WAKEUP_IRQHandler:

    .weak   I2C_IRQHandler
    .type   I2C_IRQHandler, %function
I2C_IRQHandler: 

    .weak   TIMER16_0_IRQHandler
    .type   TIMER16_0_IRQHandler, %function
TIMER16_0_IRQHandler: 

    .weak   TIMER16_1_IRQHandler
    .type   TIMER16_1_IRQHandler, %function
TIMER16_1_IRQHandler: 

    .weak   TIMER32_0_IRQHandler
    .type   TIMER32_0_IRQHandler, %function
TIMER32_0_IRQHandler:

    .weak   TIMER32_1_IRQHandler
    .type   TIMER32_1_IRQHandler, %function
TIMER32_1_IRQHandler:

    .weak   SSP_IRQHandler
    .type   SSP_IRQHandler, %function
SSP_IRQHandler:

    .weak   UART0_IRQHandler
    .type   UART0_IRQHandler, %function
UART0_IRQHandler:

    .weak   UART1_IRQHandler
    .type   UART1_IRQHandler, %function
UART1_IRQHandler:

    .weak   COMP_IRQHandler
    .type   COMP_IRQHandler, %function
COMP_IRQHandler:

    .weak   ADC_IRQHandler
    .type   ADC_IRQHandler, %function
ADC_IRQHandler:

    .weak   WDT_IRQHandler
    .type   WDT_IRQHandler, %function
WDT_IRQHandler:

    .weak   BOD_IRQHandler
    .type   BOD_IRQHandler, %function
BOD_IRQHandler:

    .weak   PIOINT0_IRQHandler
    .type   PIOINT0_IRQHandler, %function
PIOINT0_IRQHandler:

    .weak   PIOINT1_IRQHandler
    .type   PIOINT1_IRQHandler, %function
PIOINT1_IRQHandler:

    .weak   PIOINT2_IRQHandler
    .type   PIOINT2_IRQHandler, %function
PIOINT2_IRQHandler:

    .weak   DMA_IRQHandler
    .type   DMA_IRQHandler, %function
DMA_IRQHandler:

    .weak   RTC_IRQHandler
    .type   RTC_IRQHandler, %function
RTC_IRQHandler:
    B       .

.section ".startup","x",%progbits
.thumb_func
.global _startup
.global Reset_Handler

Reset_Handler:
_startup:
	/* Clear the BSS section */ 
	movs r0, #0
	ldr r1, = _start_bss
	ldr r2, = _end_bss
	subs r2, #1
_loop:
	cmp r1, r2
	str r0, [r1, #0]
	adds r1, #4
	blo _loop

	/* Jump to init() */
	ldr r0, =init
	blx r0

	/* Jump to main() */
	ldr r0, =main
	bx r0
	
.end
