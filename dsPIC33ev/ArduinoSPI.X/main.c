/*
 * File:   main.c
 * Author: George Main IV
 * 
 * This project sends and receives data to and from an Arduino using SPI
 *
 * Created on July 5, 2017, 4:38 PM
 */

#include "configurationBits.h"
#include <xc.h>
#include <libpic30.h>   
#include <p33ev256gm102.h>

int main(void) {

    device_initialize();
    device_enableInterrupts();
    
    // Set TRIS A/B, ANSEL A/B, and PORT A/B to 0
    TRISA = TRISB = 0x00;
    ANSELA = ANSELB = 0x00;
    PORTA = PORTB = 0x00;  
    
    // Turn on Power LED (RB 7, pin 16)
    PORTBbits.RB7 = 1;
    
    // SPI Configuration (Example 3-1 in SPI datasheet)
    
    IFS0bits.SPI1IF = 0;        // Clear the Interrupt flag
    IEC0bits.SPI1IE = 0;        // Disable the interrupt
    
    // SPI1CON1 Register Settings
    SPI1CON1bits.DISSCK = 0;    // Internal serial clock is enabled
    SPI1CON1bits.DISSDO = 0;    // SDOx pin is controlled by the module
    SPI1CON1bits.MODE16 = 0;    // Communication is 8 bits
    SPI1CON1bits.MSTEN = 1;     // Master mode enabled
    SPI1CON1bits.SMP = 0;       // Input data is sampled at the middle of data output time
    SPI1CON1bits.CKE = 0;       // Serial output data changes on transition from idle clock state to active clock state
    SPI1CON1bits.CKP = 0;       // Idle state for clock is a low level; active state is a high level
    SPI1STATbits.SPIEN = 1;     // Enable SPI module
    
    // Interrupt Controller Settings
    IFS0bits.SPI1IF = 0;        // Clear the Interrupt flag
    IEC0bits.SPI1IE = 1;        // Enable the interrupt

    // Main Program Loop
    while(1) {
        
    }
    
}
