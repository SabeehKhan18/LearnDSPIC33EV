/*
 * File:   newmainXC16.c
 * Author: George Main IV
 *
 * This project will turn on and off an LED using a timer
 * 
 * Created on June 3, 2017, 4:14 PM
 */

// DSPIC33EV256GM102 Configuration Bit Settings
// FSEC
#pragma config BWRP = OFF        // Boot Segment Write-Protect Bit (Boot Segment may be written)
#pragma config BSS = DISABLED    // Boot Segment Code-Protect Level bits (No Protection (other than BWRP))
#pragma config BSS2 = OFF        // Boot Segment Control Bit (No Boot Segment)
#pragma config GWRP = OFF        // General Segment Write-Protect Bit (General Segment may be written)
#pragma config GSS = DISABLED    // General Segment Code-Protect Level bits (No Protection (other than GWRP))
#pragma config CWRP = OFF        // Configuration Segment Write-Protect Bit (Configuration Segment may be written)
#pragma config CSS = DISABLED    // Configuration Segment Code-Protect Level bits (No Protection (other than CWRP))
#pragma config AIVTDIS = DISABLE // Alternate Interrupt Vector Table Disable Bit  (Disable Alternate Vector Table)
// FBSLIM
#pragma config BSLIM = 0x1FFF // Boot Segment Code Flash Page Address Limit Bits (Boot Segment Flash Page Address Limit (0-0x1FFF))
// FOSCSEL
#pragma config FNOSC = FRCPLL // Initial oscillator Source Selection Bits (Internal Fast RC (FRC) Oscillator with postscaler)
#pragma config IESO = ON       // Two Speed Oscillator Start-Up Bit (Start up device with FRC,then automatically switch to user selected oscillator source)
// FOSC
#pragma config POSCMD = NONE  // Primary Oscillator Mode Select Bits (Primary Oscillator disabled)
#pragma config OSCIOFNC = ON  // OSC2 Pin I/O Function Enable Bit (OSC2 is general purpose digital I/O pin)
#pragma config IOL1WAY = ON   // Peripheral Pin Select Configuration Bit (Allow Only One reconfiguration)
#pragma config FCKSM = CSECMD // Clock Switching Mode Bits (Clock switch enabled and Fail-safe Clock Monitor disabled)
#pragma config PLLKEN = OFF    // PLL Lock Enable Bit (Clock switch to PLL source will wait until the PLL lock signal is valid)
// FWDT
#pragma config WDTPOST = PS512 // Watchdog Timer Postscaler Bits (1:32,768)
#pragma config WDTPRE = PR32    // Watchdog Timer Prescaler Bit (1:128)
#pragma config FWDTEN = OFF      // Watchdog Timer Enable Bits (WDT and SWDTEN Disabled)
#pragma config WINDIS = OFF      // Watchdog Timer Window Enable Bit (Watchdog timer in Non-Window Mode)
#pragma config WDTWIN = WIN25    // Watchdog Window Select Bits (WDT Window is 25% of WDT period)
// FPOR
#pragma config BOREN0 = ON // Brown Out Reset Detection Bit (BOR is Enabled)
// FICD
#pragma config ICS = PGD3 // ICD Communication Channel Select Bits (Communicate on PGEC3 and PGED3)
// FDMTINTVL
#pragma config DMTIVTL = 0xFFFF // Lower 16 Bits of 32 Bit DMT Window Interval (Lower 16 bits of 32 bit DMT window interval (0-0xFFFF))
// FDMTINTVH
#pragma config DMTIVTH = 0xFFFF // Upper 16 Bits of 32 Bit DMT Window Interval (Upper 16 bits of 32 bit DMT window interval (0-0xFFFF))
// FDMTCNTL
#pragma config DMTCNTL = 0xFFFF // Lower 16 Bits of 32 Bit DMT Instruction Count Time-Out Value (Lower 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF))
// FDMTCNTH
#pragma config DMTCNTH = 0xFFFF // Upper 16 Bits of 32 Bit DMT Instruction Count Time-Out Value (Upper 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF))
// FDMT
#pragma config DMTEN = DISABLE // Dead Man Timer Enable Bit (Dead Man Timer is Disabled and can be enabled by software)
// FDEVOPT
#pragma config PWMLOCK = OFF // PWM Lock Enable Bit (Certain PWM registers may only be written after key sequence)
#pragma config ALTI2C1 = OFF // Alternate I2C1 Pins Selection Bit (I2C1 mapped to SDA1/SCL1 pins)
// FALTREG
#pragma config CTXT1 = NONE // Interrupt Priority Level (IPL) Selection Bits For Alternate Working Register Set 1 (Not Assigned)
#pragma config CTXT2 = NONE // Interrupt Priority Level (IPL) Selection Bits For Alternate Working Register Set 2 (Not Assigned)

#include <xc.h>
#include <libpic30.h>
#include <p33ev256gm102.h>

int main(void) {
    
    device_initialize();
    device_enableInterrupts();
    
    // Set TRIS, PORT, and ANSEL A and B to zeros
    ANSELA = 0x00;
    ANSELB = 0x00;
    TRISA = 0x00;
    TRISB = 0x00;
    PORTA = 0x00;
    PORTB = 0x00;
    
    // Set RB1 as an analog input
    ANSELBbits.ANSB0 = 1;
    TRISBbits.TRISB0 = 1;
    
    // Set RA0 as an analog input
    ANSELAbits.ANSA0 = 1;
    TRISAbits.TRISA0 = 1;
    
    // Reset AD1CON1
    AD1CON1 = 0x00;
    
    // Set the ADC Operational Mode to 12 bit, Single Channel ADC
    AD1CON1bits.AD12B = 1;
    
    // Set voltage reference
    AD1CON2bits.VCFG = 0x000;
    
    // ADC Clock Selection
    AD1CON3 = 0x000F;
    
    AD1CHS0 = 0x0005;
    AD1CHS123 = 0x0000;
    AD1CSSH = 0x0000;
    AD1CSSL = 0x0000;
    
    // Set AN2 as input
    AD1CHS0bits.CH0SA = 2;
    AD1CHS0bits.CH0NA = 0;
        
    // Turn on the ADC
    AD1CON1bits.ADON = 1;
    
    // Delay so ADC can stabilize
    Delay_us(20);
    
    // Reset timer 1
    T1CON = 0x00;
    
    // Set the pre-scaler to 16
    T1CONbits.TCKPS = 0b11;
    
    // Clear timer 1
    TMR1 = 0x00;
    
    // Set the period value for timer 1
    PR1 = 156;
    
    // Set timer 1 interrupt priority
    IPC0bits.T1IP = 1;
    
    // Reset timer 1 interrupt
    IFS0bits.T1IF = 0;
    
    // Enable timer 1 interrupt
    IEC0bits.T1IE = 1;
    
    // Start timer 1
    T1CONbits.TON = 1;
    
    while (1);
    return 0;
    
}

// Counter
int i = 0;

// Delay time
int value = 1000;

void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{
    // Increment counter
    i++;
    
    // If 100 cycles have occurred
    if (i > value) { 
        // Reset counter
        i = 0;
        
        // Switch LED state
        PORTBbits.RB7 = ~PORTBbits.RB7;
        
        // Example 16-1: http://ww1.microchip.com/downloads/en/DeviceDoc/70621c.pdf
        
        // Start Sampling
        AD1CON1bits.SAMP = 1;
        
        // Wait 10 us for sampling
        Delay_us(10);
        
        // Start conversion
        AD1CON1bits.SAMP = 0;  
        
        // Wait for conversion to complete
        while (!AD1CON1bits.DONE);  
        
        // Read the AN2 conversion result
        value = ADC1BUF0 / 5;      
        
    }
    
    // Reset timer 1 interrupt
    IFS0bits.T1IF = 0;
    
}

void Delay_us(unsigned int delay) {
    for (i = 0; i < delay; i++)
    {
    __asm__ volatile ("repeat #39");
    __asm__ volatile ("nop");
    }
}