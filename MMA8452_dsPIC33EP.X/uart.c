/* 
 * File:   uart.h
 * Author: George Main IV
 *
 * Created on August 3, 2017, 10:26 PM
 */

#include "uart.h"
#include "xc.h"

void uart_init(int TX, int RX) {
    
    TX = U1TX; // U1TX on pin 12
    U1RX = RX; // U1RX on pin 10

    U1MODEbits.STSEL = 0; // 1-Stop bit
    U1MODEbits.PDSEL = 0; // No Parity, 8-Data bits
    U1MODEbits.ABAUD = 0; // Auto-Baud disabled
    U1MODEbits.BRGH = 0; // Standard-Speed mode
    U1BRG = BRGVAL; // Baud Rate setting for 9600
    U1STAbits.UTXISEL0 = 0; // Interrupt after one TX character is transmitted
    U1STAbits.UTXISEL1 = 0;
    IEC0bits.U1TXIE = 1; // Enable UART TX interrupt
    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable UART TX
    /* Wait at least 105 microseconds (1/9600) before sending first char */
    DELAY_105uS
            
}

void __attribute__((__interrupt__)) _U1TXInterrupt(void) {
    IFS0bits.U1TXIF = 0; // Clear TX Interrupt flag
}
