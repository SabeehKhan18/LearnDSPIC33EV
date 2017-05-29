#include "xc.h"
#include "i2c.h"

void i2cInit() {
    // enable pins
    TRISCbits.TRISC3 = 1; // SCL
    TRISCbits.TRISC4 = 1; // SDA
    SSPCON1bits.SSPM = 8; // I2C Master mode, clock = Fosc/(4*(SSPADD + 1))
    SSPADD = 19; // BRG = 100khz
    SSPCON1bits.SSPEN = 1; // Serial port enabled

}

void i2ctransmit(I2CTransaction *trans) {
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); //Transmit is in progress
    SSPCON2bits.SEN = 1;
    int i;
    
    // write data
    for (i = 0; i < trans->sendLen; i++) {
        while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); //Transmit is in progress
        SSPBUF = trans->sendData[i];
    }
    if (trans->recvLen > 0) {
        while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); //Transmit is in progress
        SSPCON2bits.RCEN = 1; // set into read mode
        
        for (i = 0; i < trans->recvLen; i++) {
            while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); //Transmit is in progress
            trans->recvData[i] = SSPBUF;
            while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); //Transmit is in progress
            if (i < (trans->recvLen - 1)) {
                SSPCON2bits.ACKDT = 0;
            } else {
                SSPCON2bits.ACKDT = 1;
            }
            SSPCON2bits.ACKEN = 1;
        }
    }
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); //Transmit is in progress
    SSPCON2bits.PEN = 1;
}