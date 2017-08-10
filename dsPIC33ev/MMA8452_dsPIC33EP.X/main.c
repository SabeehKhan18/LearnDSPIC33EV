/* 
 * File:   main.c
 * Author: George Main IV
 *
 * Created on August 9, 2017, 9:09 PM
 * 
 * Initializes the MMA8452 library and prints values over UART for the dsPIC33EP256GP502
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "main.h"
#include "configurationBits.h"
#include "MMA8452.h"
#include "device.h"
#include "uart.h"

/*
 * Initializes MMA8452 and UART and then prints out values of the MMA8452 in the loop
 */
int main() {
    
    // Set up device clock
    device_initialize();
    
    // Set TRIS, PORT, and ANSEL for A and B to 0
    TRISA = TRISB = 0x00;
    PORTA = PORTB = 0x00;
    ANSELA = ANSELB = 0x00;
    
    // Turn on the POWER LED on RA4
    LATAbits.LATA4 = 1;
    
    // Initialize UART
    TRISBbits.TRISB6 = 1;                   // Set RB6 (U1RX_RP38) as an input pin
    uart_init(U1TX_RP37, U1RX_RP38);        // Initialize UART with TX - RP37 and RX - RP38  
    printf("UART Initialized");
    
    // Initialize MMA8452
    mma8452_init();
    printf("MMA8452 Initialized");
    
    // Re-Enable Interrupts
    device_enableInterrupts();

    printf("Starting Main Loop");
    
    while(1) {
        
    }
    
    return (0);
}

