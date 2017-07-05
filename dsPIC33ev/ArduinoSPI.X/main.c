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
    
    // Turn on Power LED
    PORTBbits.RB7 = 1;
    
    // Main Program Loop
    while(1) {
        
    }
    
}
