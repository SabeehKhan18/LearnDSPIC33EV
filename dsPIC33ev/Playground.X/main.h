/* 
 * File:   main.h
 * Author: George Main IV
 * 
 * Created on August 1, 2017, 7:55 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#define POWER       LATBbits.LATB5

#define FP 40000000
#define BAUDRATE 9600
#define BRGVAL ((FP/BAUDRATE)/16)-1
unsigned int i;
#define DELAY_105uS asm volatile ("REPEAT, #4201"); Nop(); // 105uS delay

#endif	/* MAIN_H */

