/*
 * File:   newmainXC16.c
 * Author: George Main IV
 * 
 * This project will write text to an LCD
 *
 * Created on June 16, 1:55 PM
 */


#define BLACK 1
#define WHITE 0

#define LCDWIDTH 128
#define LCDHEIGHT 64

#define CMD_DISPLAY_OFF   0xAE
#define CMD_DISPLAY_ON    0xAF

#define CMD_SET_DISP_START_LINE  0x40
#define CMD_SET_PAGE  0xB0

#define CMD_SET_COLUMN_UPPER  0x10
#define CMD_SET_COLUMN_LOWER  0x00

#define CMD_SET_ADC_NORMAL  0xA0
#define CMD_SET_ADC_REVERSE 0xA1

#define CMD_SET_DISP_NORMAL 0xA6
#define CMD_SET_DISP_REVERSE 0xA7

#define CMD_SET_ALLPTS_NORMAL 0xA4
#define CMD_SET_ALLPTS_ON  0xA5
#define CMD_SET_BIAS_9 0xA2 
#define CMD_SET_BIAS_7 0xA3

#define CMD_RMW  0xE0
#define CMD_RMW_CLEAR 0xEE
#define CMD_INTERNAL_RESET  0xE2
#define CMD_SET_COM_NORMAL  0xC0
#define CMD_SET_COM_REVERSE  0xC8
#define CMD_SET_POWER_CONTROL  0x28
#define CMD_SET_RESISTOR_RATIO  0x20
#define CMD_SET_VOLUME_FIRST  0x81
#define  CMD_SET_VOLUME_SECOND  0
#define CMD_SET_STATIC_OFF  0xAC
#define  CMD_SET_STATIC_ON  0xAD
#define CMD_SET_STATIC_REG  0x0
#define CMD_SET_BOOSTER_FIRST  0xF8
#define CMD_SET_BOOSTER_234  0
#define  CMD_SET_BOOSTER_5  1
#define  CMD_SET_BOOSTER_6  3
#define CMD_NOP  0xE3
#define CMD_TEST  0xF0

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
#include <stdint.h>

int main(void) {

    device_initialize();
    device_enableInterrupts();
    
    // Set TRIS A/B, ANSEL A/B, and PORT A/B to 0
    TRISA = TRISB = 0x00;
    ANSELA = ANSELB = 0x00;
    PORTA = PORTB = 0x00;   
  
      // Set A0 Low
    PORTBbits.RB10 = 0;
            
    // Set /RESET High
    PORTBbits.RB11 = 1;
    
     /* The following code sequence shows SPI register configuration for Master mode */
    // Example 3-1 - http://ww1.microchip.com/downloads/en/DeviceDoc/70005185a.pdf
    
    /* The following code sequence shows SPI register configuration for Master mode */
    IFS0bits.SPI1IF = 0; // Clear the Interrupt flag
    IEC0bits.SPI1IE = 0; // Disable the interrupt
    // SPI1CON1 Register Settings
    SPI1CON1bits.DISSCK = 0; // Internal serial clock is enabled
    SPI1CON1bits.DISSDO = 0; // SDOx pin is controlled by the module
    SPI1CON1bits.MODE16 = 0; // Communication is 8 bits
    SPI1CON1bits.SMP = 0; // Input data is sampled at the middle of data output time
    SPI1CON1bits.CKE = 0; // Serial output data changes on transition from
    // Idle clock state to active clock state
    SPI1CON1bits.CKP = 1; // Idle state for clock is a low-level;
    // active state is a high-level
    SPI1CON1bits.MSTEN = 1; // Master mode enabled
    SPI1STATbits.SPIEN = 1; // Enable SPI module
    SPI1BUF = 0x0000; // Write data to be transmitted
    // Interrupt Controller Settings
    IFS0bits.SPI1IF = 0; // Clear the Interrupt flag
    IEC0bits.SPI1IE = 1; // Enable the interrupt
    // Init LCD
    
    // Set A0 Low
    PORTBbits.RB10 = 0;
    
    // Reset LCD
    PORTBbits.RB11 = 0;
    //Delay_us(500000);
    PORTBbits.RB11 = 1;
    
    
     // LCD bias select
    st7565_command(CMD_SET_BIAS_7);
    // ADC select
    st7565_command(CMD_SET_ADC_NORMAL);
    // SHL select
    st7565_command(CMD_SET_COM_NORMAL);
    // Initial display line
    st7565_command(CMD_SET_DISP_START_LINE);

    // turn on voltage converter (VC=1, VR=0, VF=0)
    st7565_command(CMD_SET_POWER_CONTROL | 0x4);
    // wait for 50% rising
    //Delay_us(50000);

    // turn on voltage regulator (VC=1, VR=1, VF=0)
    st7565_command(CMD_SET_POWER_CONTROL | 0x6);
    // wait >=50ms
    //Delay_us(50000);

    // turn on voltage follower (VC=1, VR=1, VF=1)
    st7565_command(CMD_SET_POWER_CONTROL | 0x7);
    // wait
    //Delay_us(100);
    // set lcd operating voltage (regulator resistor, ref voltage resistor)
    st7565_command(CMD_SET_RESISTOR_RATIO | 0x6);
    st7565_command(CMD_DISPLAY_ON);
    st7565_command(CMD_SET_ALLPTS_ON);
    st7565_command(CMD_SET_VOLUME_FIRST);
    st7565_command(CMD_SET_VOLUME_SECOND | (125 & 0x3f));
    
    
    PORTBbits.RB5 = 1;
 

}

void st7565_command( uint8_t data)  {
   SPI1BUF = data;
  while (SPI2STATbits.SPITBF) { 

  }
}

int i = 0;

void Delay_us(unsigned int delay) {
    for (i = 0; i < delay; i++)
    {
    __asm__ volatile ("repeat #39");
    __asm__ volatile ("nop");
    }
}