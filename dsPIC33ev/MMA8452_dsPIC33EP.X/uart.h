/* 
 * File:   uart.h
 * Author: George Main IV
 *
 * UART headerfile for DSPI
 * 
 * Created on August 3, 2017, 10:27 PM
 */

#ifndef UART_H
#define	UART_H

#define FP 40000000
#define BAUDRATE 9600
#define BRGVAL ((FP/BAUDRATE)/16)-1
#define DELAY_105uS asm volatile ("REPEAT, #4201"); Nop(); // 105uS delay


// U1TX Pin Possibilities
#define U1TX    0b000001

#define U1TX_RP35     RPOR0bits.RP35R     // RP35
#define U1TX_RP36     RPOR1bits.RP36R     // RP35
#define U1TX_RP20     RPOR0bits.RP20R     // RP20
#define U1TX_RP37     RPOR1bits.RP37R     // RP37
#define U1TX_RP43     RPOR4bits.RP43R     // RP43
#define U1TX_RP42     RPOR4bits.RP42R     // RP42
#define U1TX_RP41     RPOR3bits.RP41R     // RP41
#define U1TX_RP40     RPOR3bits.RP40R     // RP40
#define U1TX_RP39     RPOR2bits.RP39R     // RP39
#define U1TX_RP38     RPOR2bits.RP38R     // RP38

// U1RX Pin Possibilities
#define U1RX    RPINR18bits.U1RXR

#define U1RX_RPI32      0b0100000
#define U1RX_RPI33      0b0100001
#define U1RX_RPI34      0b0100010
#define U1RX_RP35       0b0100011
#define U1RX_RP36       0b0100100
#define U1RX_RP20       0b0010100
#define U1RX_RP37       0b0100101
#define U1RX_RP38       0b0100101
#define U1RX_RP39       0b0100111
#define U1RX_RP40       0b0101000
#define U1RX_RP41       0b0101001
#define U1RX_RP42       0b0101010
#define U1RX_RP43       0b0101011
#define U1RX_RPI44      0b0101100
#define U1RX_RPI45      0b0101101
#define U1RX_RPI46      0b0101110
#define U1RX_RPI47      0b0101111

void uart_init(int TX, int RX); 
#endif	/* UART_H */

