/*
 * File:   tmp101.c
 * Author: khansa
 *
 * Created on May 25, 2017, 2:12 AM
 */


#include <xc.h>
#include "tmp101.h"
#include "i2c.h"

#define ADDR1 0x48
#define ADDR2 0x49
#define ADDR3 0x4A

void initTMP101() {
    I2C_Start();
    I2C_SendByte(ADDR1 << 1); //address of sensor A
    I2C_SendByte(0x01); // Sets the pointer to the Configuration Register
    I2C_SendByte(0x60); // Set to 12 bit mode
    I2C_Stop();
}

unsigned int getRawTemp() {   
    I2C_Start(); // Generate start condition
    while (i2c_WriteTo(ADDR1 << 1)); // Send ?Write to Address? byte to all slaves on I2C bus
    // This routine returns a nonzero value if the addressed
    // TMP101 fails to acknowledge after the master sends out
    // the ?Write to address? byte, so the program will hang up in
    // this loop if there is no response from the TMP101,
    // repeating this step until an acknowledge is received.
    I2C_SendByte(0x00); // Sets pointer register to 00 (Temperature register) for
    //the addressed TMP101.  (See Table 2 TMP101 Datasheet)
    I2C_Restart(); // Generate restart condition between write and read operations
    i2c_ReadFrom(ADDR1 << 1); // Sends ?Read from Address? byte to TMP101
    // Next two frames from TMP101 contain temperature as
    // signed 12-bit value
    unsigned int temp = 0, temp_rem = 0;
    temp = (I2C_ReadByte(I2C_MORE)); //get upper 8 bits of temperature (integer portion)
    temp_rem = I2C_ReadByte(I2C_LAST); //get lower 4 bits temperature (fractional portion)
    I2C_Stop(); // Generate stop condition
}