/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*/

#include 	"i2c.h"

/* defined for I2C */

#define I2C_TRANSMIT_REG                       SSPBUF                 // Defines the transmit register used to send data.
#define I2C_RECEIVE_REG                        SSPBUF                 // Defines the receive register used to receive data.

// The following control bits are used in the I2C state machine to manage
// the I2C module and determine next states.
#define I2C_TRANSMIT_STATUS_BIT                SSPSTATbits.R_nW     // I2C Transmit is in progress status bit.
#define I2C_BUFFER_STATUS_BIT                  SSPSTATbits.BF       // I2C Buffer/Receive complete status bit.

#define I2C_WRITE_COLLISION_STATUS_BIT         SSPCONbits.WCOL      // Defines the write collision status bit.
#define I2C_MODE_SELECT_BITS                   SSPCONbits.SSPM0     // I2C Master Mode control bit.
#define I2C_MASTER_ENABLE_CONTROL_BITS         SSPCONbits.SSPEN     // I2C port enable control bit.

#define I2C_START_CONDITION_ENABLE_BIT         SSPCON2bits.SEN      // I2C START control bit.
#define I2C_REPEAT_START_CONDITION_ENABLE_BIT  SSPCON2bits.RSEN     // I2C Repeated START control bit.
#define I2C_RECEIVE_ENABLE_BIT                 SSPCON2bits.RCEN     // I2C Receive enable control bit.
#define I2C_STOP_CONDITION_ENABLE_BIT          SSPCON2bits.PEN      // I2C STOP control bit.
#define I2C_ACKNOWLEDGE_ENABLE_BIT             SSPCON2bits.ACKEN    // I2C ACK start control bit.
#define I2C_ACKNOWLEDGE_DATA_BIT               SSPCON2bits.ACKDT    // I2C ACK data control bit.
#define I2C_ACKNOWLEDGE_STATUS_BIT             SSPCON2bits.ACKSTAT  // I2C ACK status bit.


void I2C_Initialize(void)
{
    TRISC3=1;           // Set SCL and SDA pins as inputs, this
    TRISC4=1;		//	initially relaxes SCL and SDA, letting them
                        //	be pulled high by the external pullup resistors.
    // BF RCinprocess_TXcomplete; UA dontupdate; SMP Sample At Middle; P stopbit_notdetected; S startbit_notdetected; R_nW write_noTX; CKE Idle to Active; D_nA lastbyte_address; 
    SSPSTAT = 0x00;
    // SSPM0 FOSC/4_SSPxADD; SSPEN enabled; WCOL no_collision; SSPOV no_overflow; CKP Idle:Low, Active:High; 
    SSPCON = 0x28;      // We are choosing <SSPM3:SSPM0> = <1000> = I2C Master mode, clock = FOSC / (4 * (SSPADD+1))
    // BOEN disabled; AHEN disabled; SBCDE disabled; SDAHT 100ns; DHEN disabled; ACKTIM ackseq; PCIE disabled; SCIE disabled; 
    SSPCON2 = 0x00;
    // Baud Rate Generator Value: SSPADD 19;   
    SSPADD = 19;        // Choose 100 kHZ I2C clock rate assuming an Fosc = 8 Mhz PIC clock
    		
    // clear the master interrupt flag
    SSPIF = 0;
    // enable the master interrupt
//    SSPIE = 1;
    
}

/*
 * 	Return idle status of I2C in MSSP module
 * 	  0 - idle, 1 - active
 */
unsigned char I2C_Idle_Status(void)
{
    return (I2C_TRANSMIT_STATUS_BIT | I2C_START_CONDITION_ENABLE_BIT | 
            I2C_REPEAT_START_CONDITION_ENABLE_BIT | I2C_STOP_CONDITION_ENABLE_BIT | 
            I2C_RECEIVE_ENABLE_BIT | I2C_ACKNOWLEDGE_ENABLE_BIT);
}

/*
 * 	Send start condition
 * 	  - data high-low while clock high
 */
void I2C_Start(void)
{
    while(I2C_Idle_Status());
    // send the start condition
    I2C_START_CONDITION_ENABLE_BIT = 1;
    while(I2C_START_CONDITION_ENABLE_BIT);
}

/*
 * 	Send restart condition
 * 	  - ensure data is high then issue a start condition
 */
void I2C_Restart(void)
{
    while(I2C_Idle_Status());
    // ... trigger a REPEATED START
    I2C_REPEAT_START_CONDITION_ENABLE_BIT = 1;
    while(I2C_REPEAT_START_CONDITION_ENABLE_BIT);
}

/*
 * 	Send stop condition
 * 	  - data low-high while clock high
 */
void I2C_Stop(void)
{
    while(I2C_Idle_Status());
    I2C_STOP_CONDITION_ENABLE_BIT = 1;
    while(I2C_STOP_CONDITION_ENABLE_BIT);
    SSPIF = 0;
}

/*
 * 	Send a byte to the slave
 * 	  - returns ACK value
 */
unsigned char I2C_SendByte(unsigned char data)
{
    // Place data into transmit buffer
    I2C_TRANSMIT_REG = data;
    SSPIF = 0;
    while(I2C_TRANSMIT_STATUS_BIT);
    SSPIF = 0;
    return I2C_ACKNOWLEDGE_STATUS_BIT;
}

/*
 * 	send an address and data direction to the slave
 * 	  - 7-bit address (lsb ignored)
 * 	  - direction (0 = write )
 */
unsigned char I2C_SendAddress(unsigned char address, unsigned char rw)
{
    return I2C_SendByte(address | (rw?1:0));
}

/*
 * 	Read a byte from the slave
 * 	  - returns the byte, or I2C_ERROR if a bus error
 *        - sets ACK bit to value of ack if successful
 */
int I2C_ReadByte(unsigned char ack)
{
    int byte = I2C_ERROR;
    unsigned char response = I2C_NACK;
    I2C_RECEIVE_ENABLE_BIT = 1;
    SSPIF = 0;
    while(SSPIF == 0);
    if(I2C_BUFFER_STATUS_BIT) {
        byte = I2C_RECEIVE_REG;
        response = ack;
    }
    SSPIF = 0;
    I2C_ACKNOWLEDGE_DATA_BIT = response;
    // Initiate the acknowledge
    I2C_ACKNOWLEDGE_ENABLE_BIT = 1;
    while(I2C_ACKNOWLEDGE_ENABLE_BIT);
    return byte;
}

