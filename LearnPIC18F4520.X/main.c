
// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#include "i2c.h"
unsigned int heat;

const unsigned char list1[] = {50,25,13,6};
const unsigned char list2[] = {128,64,32,16};

char get_temperature(unsigned char TMP101_address, char *temp, char *temp_rem) {
    I2C_Start(); // Generate start condition
    while (i2c_WriteTo(TMP101_address)); // Send ?Write to Address? byte to all slaves on I2C bus
    // This routine returns a nonzero value if the addressed
    // TMP101 fails to acknowledge after the master sends out
    // the ?Write to address? byte, so the program will hang up in
    // this loop if there is no response from the TMP101,
    // repeating this step until an acknowledge is received.
    I2C_SendByte(0x00); // Sets pointer register to 00 (Temperature register) for
    //the addressed TMP101. (See Table 2 TMP101 Datasheet)
    I2C_Restart(); // Generate restart condition between write and read operations
    i2c_ReadFrom(TMP101_address); // Sends ?Read from Address? byte to TMP101
    // Next two frames from TMP101 contain temperature as
    // signed 12-bit value
    *temp = I2C_ReadByte(I2C_MORE); //get upper 8 bits of temperature (integer portion)
    *temp_rem = I2C_ReadByte(I2C_LAST); //get lower 4 bits temperature (fractional portion)
    I2C_Stop(); // Generate stop condition
}

void main(void) {
    ANSEL = ANSELH = 0;
    char temp, temp_rem, sign_char, dig0_char, dig1_char, dig2_char;
    I2C_Initialize();

    while (1) {
        get_temperature(0x90, &temp, &temp_rem);
//        heat = temp;
//        char k;
//        char heatLOW = 0;
//        for (k = 0; k < 4; k++){        // Convert lower four bits
//            if (temp_rem > list2[k]){
//                temp_rem = temp_rem - list2[k];
//                heatLOW += list1[k];
//            }
//        }
//        heat = (heat * 100) + heatLOW;
    }
}