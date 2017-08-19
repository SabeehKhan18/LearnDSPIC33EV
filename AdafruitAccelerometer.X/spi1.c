/*
 * File:   spi1.c
 * Author: Sabeeh
 *
 * Created on August 1, 2017, 9:28 PM
 */


#include "xc.h"
#include "spi1.h"

void spi1_init(void)
{
    /* The following code sequence shows SPI register configuration for Master mode */
	IFS0bits.SPI1IF = 0; 	// Clear the Interrupt flag
	IEC0bits.SPI1IE = 0; 	// Disable the interrupt
							// SPI1CON1 Register Settings
	SPI1CON1bits.DISSCK = 0; // Internal serial clock is enabled
	SPI1CON1bits.DISSDO = 0; // SDOx pin is controlled by the module
	
	SPI1CON1bits.PPRE = 2;	// divide Fy by 4
	SPI1CON1bits.SPRE = 3;	// divide Fy/4 by 5. 40MHz -> 2MHz
	
	SPI1CON1bits.MODE16 = 1; // Communication is word-wide (16 bits)
	SPI1CON1bits.MSTEN = 1; // Master mode enabled
	SPI1CON1bits.SMP = 0; 	// Input data is sampled at the middle of data output time
	SPI1CON1bits.CKE = 1; 	// Serial output data changes on transition from
	// active clock state to idle clock state
	SPI1CON1bits.CKP = 0; 	// Idle state for clock is a low level;
							// active state is a high level
	SPI1STATbits.SPIEN = 1; // Enable SPI module
	
	// Interrupt Controller Settings
	IFS0bits.SPI1IF = 0; // Clear the Interrupt flag
	IEC0bits.SPI1IE = 1; // Enable the interrupt
}

