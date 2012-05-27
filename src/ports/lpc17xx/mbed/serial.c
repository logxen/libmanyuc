/*
 * libmanyuc - LPC serial communication file
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
#include "board.h"


// Port tables

const static int modes[] = { S0_Mode, S1_Mode, S2_Mode, S3_Mode };
const static int power_bits[] = { PCUART0, PCUART1, PCUART2, PCUART3 };
const static uint32_t txs[] = { TX_0, TX_1, TX_2, TX_3 };
const static uint32_t rxs[] = { RX_0, RX_1, RX_2, RX_3 };
const static int uarts[] = { UART_0, UART_1, UART_2, UART_3 };

// Internal defines used for bit operations
#define UART_BYTE_MASK          ((uint8_t) 0xFF)      // Mask bit for byte data
#define UART_LSB(val)           ((val) & 0xFF)        // LSB of val
#define UART_MSB(val)           (((val) >> 8) & 0xFF) // MSB of val

#define UART_FCR_FIFO_EN        ((uint8_t)(1<<0))     // UART FIFO enable 
#define UART_FCR_RX_RS          ((uint8_t)(1<<1))     // UART FIFO RX reset 
#define UART_FCR_TX_RS          ((uint8_t)(1<<2))     // UART FIFO TX reset 

// Line status register
#define UART_LSR_RDR            ((uint8_t)(1<<0))     // LSR Receive data ready
#define UART_LSR_THRE           ((uint8_t)(1<<5))     // LSR Transmit holding register empty

// Transmit enable register
#define UART_TER_TXEN           ((uint8_t)(1<<7))     // Transmit enable bit

// Line control register
#define UART_LCR_WLEN5          ((uint8_t) 0)         // 5 bit character length 
#define UART_LCR_WLEN6          ((uint8_t) 1)         // 6 bit character length 
#define UART_LCR_WLEN7          ((uint8_t) 2)         // 7 bit character length 
#define UART_LCR_WLEN8          ((uint8_t) 3)         // 8 bit character length 
#define UART_LCR_STOPBIT_SEL    ((uint8_t)(1<<2))     // UART Two Stop Bits Select 
#define UART_LCR_PARITY_EN      ((uint8_t)(1<<3))     // UART Parity Enable/
#define UART_LCR_PARITY_ODD     ((uint8_t)(0))        // UART Odd Parity Select 
#define UART_LCR_PARITY_EVEN    ((uint8_t)(1<<4))     // UART Even Parity Select 
#define UART_LCR_PARITY_F_1     ((uint8_t)(2<<4))     // UART force 1 stick parity 
#define UART_LCR_PARITY_F_0     ((uint8_t)(3<<4))     // UART force 0 stick parity 
#define UART_LCR_BREAK_EN       ((uint8_t)(1<<6))     // UART Transmission Break enable 
#define UART_LCR_DLAB_EN        ((uint8_t)(1<<7))     // UART Divisor Latches Access bit enable

#define UART_BLOCK_TIMEOUT      0xFFFFFFFF            // Timeout for blocking 



#define UART_IER_RBRINT_EN      ((uint32_t)(1<<0))  // RBR Interrupt enable
#define UART_IER_THREINT_EN     ((uint32_t)(1<<1))  // THR Interrupt enable
#define UART_IER_RLSINT_EN      ((uint32_t)(1<<2))  // RX line status interrupt enable
#define UART1_IER_MSINT_EN      ((uint32_t)(1<<3))  // Modem status interrupt enable 
#define UART1_IER_CTSINT_EN     ((uint32_t)(1<<7))  // CTS1 signal transition interrupt enable 
#define UART_IER_ABEOINT_EN     ((uint32_t)(1<<8))  // Enables the end of auto-baud interrupt 
#define UART_IER_ABTOINT_EN     ((uint32_t)(1<<9))  // Enables the auto-baud time-out interrupt 
#define UART_IER_BITMASK        ((uint32_t)(0x307)) // UART interrupt enable register bit mask 
#define UART1_IER_BITMASK       ((uint32_t)(0x38F)) // UART1 interrupt enable register bit mask 
#define UART_IIR_INTSTAT_PEND   ((uint32_t)(1<<0))  //Interrupt Status - Active low 
#define UART_IIR_INTID_RLS      ((uint32_t)(3<<1))  //Interrupt identification: Receive line status
#define UART_IIR_INTID_RDA      ((uint32_t)(2<<1))  //Interrupt identification: Receive data available
#define UART_IIR_INTID_CTI      ((uint32_t)(6<<1))  //Interrupt identification: Character time-out indicator
#define UART_IIR_INTID_THRE     ((uint32_t)(1<<1))  //Interrupt identification: THRE interrupt
#define UART1_IIR_INTID_MODEM   ((uint32_t)(0<<1))  //Interrupt identification: Modem interrupt
#define UART_IIR_INTID_MASK     ((uint32_t)(7<<1))  //Interrupt identification: Interrupt ID mask 
#define UART_IIR_FIFO_EN        ((uint32_t)(3<<6))  //These bits are equivalent to UnFCR[0] 
#define UART_IIR_ABEO_INT       ((uint32_t)(1<<8))  // End of auto-baud interrupt 
#define UART_IIR_ABTO_INT       ((uint32_t)(1<<9))  // Auto-baud time-out interrupt 
#define UART_IIR_BITMASK        ((uint32_t)(0x3CF)) // UART interrupt identification register bit mask 

#define UART_FCR_DMAMODE_SEL    ((uint8_t)(1<<3))   // UART DMA mode selection 
#define UART_FCR_TRG_LEV0       ((uint8_t)(0))      // UART FIFO trigger level 0: 1 character 
#define UART_FCR_TRG_LEV1       ((uint8_t)(1<<6))   // UART FIFO trigger level 1: 4 character 
#define UART_FCR_TRG_LEV2       ((uint8_t)(2<<6))   // UART FIFO trigger level 2: 8 character 
#define UART_FCR_TRG_LEV3       ((uint8_t)(3<<6))   // UART FIFO trigger level 3: 14 character 
#define UART_FCR_BITMASK        ((uint8_t)(0xCF))   // UART FIFO control bit mask 
#define UART_TX_FIFO_SIZE       (16)

#define UART1_MCR_DTR_CTRL      ((uint8_t)(1<<0))       /*!< Source for modem output pin DTR */
#define UART1_MCR_RTS_CTRL      ((uint8_t)(1<<1))       /*!< Source for modem output pin RTS */
#define UART1_MCR_LOOPB_EN      ((uint8_t)(1<<4))       /*!< Loop back mode select */
#define UART1_MCR_AUTO_RTS_EN   ((uint8_t)(1<<6))       /*!< Enable Auto RTS flow-control */
#define UART1_MCR_AUTO_CTS_EN   ((uint8_t)(1<<7))       /*!< Enable Auto CTS flow-control */
#define UART1_MCR_BITMASK       ((uint8_t)(0x0F3))      /*!< UART1 bit mask value */

#define UART_LSR_OE         ((uint8_t)(1<<1))   /*!<Line status register: Overrun error*/
#define UART_LSR_PE         ((uint8_t)(1<<2))   /*!<Line status register: Parity error*/
#define UART_LSR_FE         ((uint8_t)(1<<3))   /*!<Line status register: Framing error*/
#define UART_LSR_BI         ((uint8_t)(1<<4))   /*!<Line status register: Break interrupt*/
#define UART_LSR_TEMT       ((uint8_t)(1<<6))   /*!<Line status register: Transmitter empty*/
#define UART_LSR_RXFE       ((uint8_t)(1<<7))   /*!<Error in RX FIFO*/
#define UART_LSR_BITMASK    ((uint8_t)(0xFF))   /*!<UART Line status bit mask */

#define UART1_MSR_DELTA_CTS     ((uint8_t)(1<<0))   /*!< Set upon state change of input CTS */
#define UART1_MSR_DELTA_DSR     ((uint8_t)(1<<1))   /*!< Set upon state change of input DSR */
#define UART1_MSR_LO2HI_RI      ((uint8_t)(1<<2))   /*!< Set upon low to high transition of input RI */
#define UART1_MSR_DELTA_DCD     ((uint8_t)(1<<3))   /*!< Set upon state change of input DCD */
#define UART1_MSR_CTS           ((uint8_t)(1<<4))   /*!< Clear To Send State */
#define UART1_MSR_DSR           ((uint8_t)(1<<5))   /*!< Data Set Ready State */
#define UART1_MSR_RI            ((uint8_t)(1<<6))   /*!< Ring Indicator State */
#define UART1_MSR_DCD           ((uint8_t)(1<<7))   /*!< Data Carrier Detect State */
#define UART1_MSR_BITMASK       ((uint8_t)(0xFF))   /*!< MSR register bit-mask value */
#define UART_SCR_BIMASK     ((uint8_t)(0xFF))   /*!< UART Scratch Pad bit mask */
#define UART_ACR_START              ((uint32_t)(1<<0))  /**< UART Auto-baud start */
#define UART_ACR_MODE               ((uint32_t)(1<<1))  /**< UART Auto baudrate Mode 1 */
#define UART_ACR_AUTO_RESTART       ((uint32_t)(1<<2))  /**< UART Auto baudrate restart */
#define UART_ACR_ABEOINT_CLR        ((uint32_t)(1<<8))  /**< UART End of auto-baud interrupt clear */
#define UART_ACR_ABTOINT_CLR        ((uint32_t)(1<<9))  /**< UART Auto-baud time-out interrupt clear */
#define UART_ACR_BITMASK            ((uint32_t)(0x307)) /**< UART Auto Baudrate register bit mask */
#define UART_ICR_IRDAEN         ((uint32_t)(1<<0))          /**< IrDA mode enable */
#define UART_ICR_IRDAINV        ((uint32_t)(1<<1))          /**< IrDA serial input inverted */
#define UART_ICR_FIXPULSE_EN    ((uint32_t)(1<<2))          /**< IrDA fixed pulse width mode */
#define UART_ICR_PULSEDIV(n)    ((uint32_t)((n&0x07)<<3))   /**< PulseDiv - Configures the pulse when FixPulseEn = 1 */
#define UART_ICR_BITMASK        ((uint32_t)(0x3F))          /*!< UART IRDA bit mask */
#define UART_FDR_DIVADDVAL(n)   ((uint32_t)(n&0x0F))        /**< Baud-rate generation pre-scaler divisor */
#define UART_FDR_MULVAL(n)      ((uint32_t)((n<<4)&0xF0))   /**< Baud-rate pre-scaler multiplier value */
#define UART_FDR_BITMASK        ((uint32_t)(0xFF))          /**< UART Fractional Divider register bit mask */
#define UART_TER_BITMASK        ((uint8_t)(0x80))       /**< UART Transmit Enable Register bit mask */

#define UART1_RS485CTRL_NMM_EN      ((uint32_t)(1<<0))  /*!< RS-485/EIA-485 Normal Multi-drop Mode (NMM)
is disabled */
#define UART1_RS485CTRL_RX_DIS      ((uint32_t)(1<<1))  /*!< The receiver is disabled */
#define UART1_RS485CTRL_AADEN       ((uint32_t)(1<<2))  /*!< Auto Address Detect (AAD) is enabled */
#define UART1_RS485CTRL_SEL_DTR     ((uint32_t)(1<<3))  /*!< If direction control is enabled
(bit DCTRL = 1), pin DTR is used for direction control */
#define UART1_RS485CTRL_DCTRL_EN    ((uint32_t)(1<<4))  /*!< Enable Auto Direction Control */
#define UART1_RS485CTRL_OINV_1      ((uint32_t)(1<<5))  /*!< This bit reverses the polarity of the direction
control signal on the RTS (or DTR) pin. The direction control pin
    will be driven to logic "1" when the transmitter has data to be sent */

#define UART1_RS485CTRL_BITMASK     ((uint32_t)(0x3F))  /**< RS485 control bit-mask value */

#define UART1_RS485ADRMATCH_BITMASK ((uint8_t)(0xFF))   /**< Bit mask value */

#define UART1_RS485DLY_BITMASK      ((uint8_t)(0xFF))   /** Bit mask value */

#define UART_FIFOLVL_RXFIFOLVL(n)   ((uint32_t)(n&0x0F))        /**< Reflects the current level of the UART receiver FIFO */
#define UART_FIFOLVL_TXFIFOLVL(n)   ((uint32_t)((n>>8)&0x0F))   /**< Reflects the current level of the UART transmitter FIFO */
#define UART_FIFOLVL_BITMASK        ((uint32_t)(0x0F0F))        /**< UART FIFO Level Register bit mask */

static uint8_t serial_initialized[] = { 0, 0, 0, 0 };

/* Convert the serial port number to a serial port struct. */
Serial_t Serial_Get(int number) {
    if (number < 0 || number > 4) number = 0;
    Serial_t port = {
        Pin_Get(txs[number]),
        Pin_Get(rxs[number]),
        (LPC_UART_TypeDef *) uarts[number],
        number
    };
    return port;
}

Serial_t Serial_Init(int number, int baudrate) {

    Serial_t port = Serial_Get(number);
    if (serial_initialized[number]) {
        return port;
    }
    serial_initialized[number] = 1;

    // 1 - Power up the serial port
    uint32_t power_bit_mask = 1 << power_bits[port.number];
    LPC_SC->PCONP |= power_bit_mask;

    // 3 - Set the baudrate
    uint32_t SystemCoreClock = 100000000;
    uint16_t rate = SystemCoreClock / (16 * 4 * baudrate);

    // Enable divisor latches and set the rate
    port.uart->LCR |= UART_LCR_DLAB_EN;
    port.uart->DLL = UART_LSB(rate);
    port.uart->DLM = UART_MSB(rate);

    // 4 - Empty FIFOs and Disable FIFO
    port.uart->FCR = UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TX_RS;
    port.uart->FCR = 0;
    /*
        // Read what was already on the buffers
        uint8_t aux;
        while (port.uart->LSR & UART_LSR_RDR) {
            aux = port.uart->RBR;
        }

        // Enable transmission
        port.uart->TER = UART_TER_TXEN;
        // Transmit what was already on the buffer
        while (!(port.uart->LSR & UART_LSR_THRE));
        // Disable transmission
        port.uart->TER = 0;

        // Enable FIFO
        port.uart->FCR = UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TX_RS;*/

    // 5 - Set the pin function
    Pin_Mode(port.tx, modes[port.number]);
    Pin_Mode(port.rx, modes[port.number]);

    // 6 - Disable Interrupts
    port.uart->IER = 0;

    // Reset LCR / ACR
    port.uart->LCR = 0;
    /*  port.uart->ACR = 0;

        // Read anything still on the buffers
        aux = port.uart->LSR;*/

    // Set configuration for transmission (8N1)
    /*port.uart->LCR = UART_LCR_WLEN8 | UART_LCR_BREAK_EN;*/
    port.uart->LCR = UART_LCR_WLEN8;

    port.uart->FCR = UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TX_RS;

    // Enable transmission
    port.uart->TER = UART_TER_TXEN;

}

// Returns if there is info available to be read
__INLINE int Serial_Readable(Serial_t port) {
    return (port.uart->LSR & UART_LSR_RDR);
}

// Returns a byte read from the serial port. If there is no byte yet, it
// blocks until there is.
__INLINE uint8_t Serial_Get_Byte(Serial_t port) {
    return port.uart->RBR & UART_BYTE_MASK;
}

// Reads the amount of bytes from the serial port into the buffer.
// Memory for the buffer must have been allocated first.
uint32_t Serial_Get_Bytes(Serial_t port, uint8_t *data,
                          uint32_t length, SerialTransferMode mode) {

    uint32_t i = 0, wait;

    while (i < length) {

        // If non blocking, check if there's something to read
        // and if not, bail out.
        if (!(Serial_Readable(port)) && (mode == NONBLOCKING)) {
            break;
        }
        wait = UART_BLOCK_TIMEOUT;
        while (!(Serial_Readable(port)) && (mode == BLOCKING || (wait > 0))) {
            wait--;
        }
        if (!wait) break;

        data[i] = Serial_Get_Byte(port);
        i++;

    }
    return i;
}

// Returns if there is space to send a byte
__INLINE int Serial_Sendable(Serial_t port) {
    return (port.uart->LSR & UART_LSR_THRE);
}

// Sends a byte through the serial port. If there is no space, it blocks
// until there is.
__INLINE void Serial_Put_Byte(Serial_t port, uint8_t data) {
    port.uart->THR = data & UART_BYTE_MASK;
}


uint32_t Serial_Put_Bytes(Serial_t port, uint8_t *data,
                          uint32_t length, SerialTransferMode mode) {

    uint32_t i = 0, c, wait;

    while (i < length) {

        // If non blocking, check for space and leave when none.
        if (!(Serial_Sendable(port)) && (mode == NONBLOCKING)) {
            break;
        }

        // Otherwise check for space according to the timeout, or not.
        wait = UART_BLOCK_TIMEOUT;
        while (!(Serial_Sendable(port)) && (mode == BLOCKING || (wait > 0))) {
            wait--;
        }
        if (!wait) break;

        // Fill the fifo queue with bytes
        c = UART_TX_FIFO_SIZE;
        while ((i < length) && (c > 0)) {
            Serial_Put_Byte(port, data[i]);
            i++;
            c--;
        }
    }
    // Return the amount of bytes that were sent
    return i;
}

void UART0_IRQ_Handler() {
}

void UART1_IRQ_Handler() {
}

void UART2_IRQ_Handler() {
}

void UART3_IRQ_Handler() {
}

void Serial_Attach(Serial_t port, void (*function)(void), SerialIRQType type) {
    port.uart->IER |= type;
}

// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
