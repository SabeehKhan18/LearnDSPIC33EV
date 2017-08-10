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
#include "main.h"
#include "configurationBits.h"
#include <xc.h>

/*
 * Initializes I2C, MMA8452, and UART and then prints out values of the MMA8452 in the loop
 */
int main() {
    
    // Set TRIS, PORT, and ANSEL for A and B to 0
    TRISA = TRISB = 0x00;
    PORTA = PORTB = 0x00;
    ANSELA = ANSELB = 0x00;
    
    // Turn on the POWER LED
    POWER = 1;

    while(1) {
        
    }
    
    return (0);
}

