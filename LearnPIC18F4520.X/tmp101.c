/*
 * File:   tmp101.c
 * Author: khansa
 *
 * Created on May 25, 2017, 2:12 AM
 */


#include <xc.h>
#include "tmp101.h"
#include "i2c.h"

#define ADDR1 0x40
#define ADDR2 0x41
#define ADDR3 0x42

void initTMP101() {
    I2CTransaction tmp101;
    tmp101.devAddr = ADDR1;
    tmp101.readWrite = WRITE;
    char data[] = { 1, 0x60};
    tmp101.sendData = data;
    tmp101.sendLen = 2; 
    i2ctransmit(tmp101);
}

int getRawTemp() {
    char data[2];
    char temp[2];
    I2CTransaction trans;
    trans.devAddr = ADDR1;
    trans.readWrite = WRITE; // write to set pointer to 0
    data[0] = 0;
    trans.sendLen = 1;
    trans.sendData = data;
    trans.recvData = temp;
    trans.recvLen = 2;
    i2ctransmit(trans);
    trans.readWrite = READ;
    i2ctransmit(trans);
    int retVal = (int) temp[1] >> 4;
    retVal |= ((int) temp[0]) << 8;
    return retVal;
}