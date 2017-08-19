/*
 * File:   main.c
 * Author: George Main IV
 *
 * Created on August 1, 2017, 7:56 PM
 */

#include "configurationBits.h"
#include "main.h"
#include "device.h"
#include "uart.h"
#include <xc.h>
#include <stdio.h>
#include <libpic30.h>   
#include <p33ev256gm102.h>

int main(void) {
    
    // Initialize oscillator
    device_initialize();
    
    // Set all TRIS, ANSEL, and PORT to 0
    TRISA = ANSELA = PORTA = 0x00;
    TRISB = ANSELB = PORTB = 0x00;
    
    // Turn on power LED
    POWER = 1;
    
    // Initialize UART
    uart_init();
    printf("UART Initialized\n");
    
    // Enable interrupts
    device_enableInterrupts();
    printf("Interrupts Enabled\n");
    
    printf("ID: %i\n", ID);
    
    printf("Starting Loop\n");
    while(1) {
        
        // Check UART
        if (U1STAbits.FERR == 1) {
            continue;
        }
        /* Must clear the overrun error to keep UART receiving */
        if (U1STAbits.OERR == 1) {
            U1STAbits.OERR = 0;
            continue;
        }
  
    }
    
    return 0;
    
}
