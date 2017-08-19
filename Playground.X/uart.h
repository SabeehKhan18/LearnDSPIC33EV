/* 
 * File:   uart.h
 * Author: George Main IV
 *
 * Created on August 3, 2017, 10:27 PM
 */

#ifndef UART_H
#define	UART_H

#define FP 40000000
#define BAUDRATE 9600
#define BRGVAL ((FP/BAUDRATE)/16)-1
#define DELAY_105uS asm volatile ("REPEAT, #4201"); Nop(); // 105uS delay

void uart_init(void);

#endif	/* UART_H */

