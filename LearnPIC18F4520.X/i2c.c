#include "xc.h"
#include "i2c.h"

void i2cInit() {
    // enable pins
    TRISCbits.TRISC3 = 0; // SCL
    TRISCbits.TRISC4 = 0; // SDA
    SSPCON1bits.SSPM = 8; // I2C Master mode, clock = Fosc/(4*(SSPADD + 1))
    SSPADD = 19;          // BRG = 100khz
    SSPCON1bits.SSPEN = 1; // Serial port enabled
    
}

void i2ctransmit(I2CTransaction *trans) {
    char addr = (trans->devAddr < 1) | trans->readWrite;
    SSPCON2bits.SEN = 1;
    while (SSPIF == 0);
    SSPBUF = addr;
    SSPIF = 0;
    while (SSPIF == 0); // wait for ACK
    SSPIF = 0;
    int i;
    if (trans->readWrite == WRITE) {
        for (i = 0; i < trans->sendLen; i++) {
            SSPBUF = trans->recvData[i];
            while (SSPIF == 0);         // wait for ACK
            SSPIF = 0;
        }
    }
    if (trans->readWrite == READ) {
        SSPCON2bits.RCEN = 1; // set into read mode
        for (i = 0; i < trans->recvLen; i++) {
            
        }
    }
    
}