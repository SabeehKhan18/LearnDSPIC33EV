/*
 * File:   newmainXC16.c
 * Author: George Main IV
 * 
 * This project will write text to an LCD
 *
 * Created on June 16, 1:55 PM
 */

// DSPIC33EP256GP502 Configuration Bit Settings

// 'C' source line config statements

// FICD
#pragma config ICS = PGD1               // ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)

// FPOR
#pragma config ALTI2C1 = OFF            // Alternate I2C1 pins (I2C1 mapped to SDA1/SCL1 pins)
#pragma config ALTI2C2 = OFF            // Alternate I2C2 pins (I2C2 mapped to SDA2/SCL2 pins)
#pragma config WDTWIN = WIN25           // Watchdog Window Select bits (WDT Window is 25% of WDT period)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler bits (1:32,768)
#pragma config WDTPRE = PR128           // Watchdog Timer Prescaler bit (1:128)
#pragma config PLLKEN = ON              // PLL Lock Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = ON              // Watchdog Timer Enable bit (Watchdog timer always enabled)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function bit (OSC2 is clock output)
#pragma config IOL1WAY = ON             // Peripheral pin select configuration (Allow only one reconfiguration)
#pragma config FCKSM = CSDCMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)

// FOSCSEL
#pragma config FNOSC = FRCDIVN          // Oscillator Source Selection (Internal Fast RC (FRC) Oscillator with postscaler)
#pragma config IESO = ON                // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FGS
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GCP = OFF                // General Segment Code-Protect bit (General Segment Code protect is Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <libpic30.h>
#include <p33ep256gp502.h>

int main(void) {

    device_initialize();
    device_enableInterrupts();
    
    // Set TRIS A/B, ANSEL A/B, and PORT A/B to 0
    TRISA = TRISB = 0x00;
    ANSELA = ANSELB = 0x00;
    PORTA = PORTB = 0x00;
    
    /* The following code sequence shows SPI register configuration for Master mode */
    // Example 3-1 - http://ww1.microchip.com/downloads/en/DeviceDoc/70005185a.pdf
    
    IFS0bits.SPI1IF = 0;            // Clear the Interrupt flag
    IEC0bits.SPI1IE = 0;            // Disable the interrupt
    
    SPI1STAT = 0x00;                // Reset SPI1 Status and Control Register
    SPI1STATbits.SPIEN = 1;         // Enable SCK1, SDO1, SDI1, and SS1 as serial port pins
    
    SPI1CON1 = 0x00;                // Reset SPI1 Control Register 1
    SPI1CON1bits.DISSCK = 0;        // Internal serial clock is enabled
    SPI1CON1bits.DISSDO = 0;        // SDOx pin is controlled by the module
    SPI1CON1bits.MODE16 = 0;        // Communication is 8 bits
    SPI1CON1bits.MSTEN = 1;         // Enable Master Mode
    SPI1CON1bits.SMP = 0;           // Input data is sampled at the middle of data output time
    SPI1CON1bits.CKE = 0;           // Serial output data changes on transition from
    
    SPI1CON1bits.CKP = 0;           // Idle state for clock is a low level; 
    
    SPI1STATbits.SPIEN = 1;         // Enable SPI module
    
    IFS0bits.SPI1IF = 0;            // Clear the Interrupt flag
    IEC0bits.SPI1IE = 1;            // Enable the interrupt

    while(1) {
      while( SPI1STATbits.SPITBF )
    {

    }
    
    SPI1BUF = 0xA5;
     while ( SPI1STATbits.SRXMPT);
    }

}
