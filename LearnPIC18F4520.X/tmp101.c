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
    I2CTransaction tmp101;
    char ID[] = { WRITE(ADDR1), 1, 0x00};
    tmp101.sendData = ID;
    tmp101.sendLen = 3; 
    tmp101.recvLen = 0;
    i2ctransmit(&tmp101);
}

unsigned int getRawTemp() {   
    I2CTransaction trans;
    char data[2];
    char temp[2];
    trans.sendLen = 2;
    trans.sendData = data;
    trans.recvData = temp;
    trans.recvLen = 2;
    data[0] = WRITE(ADDR1);
    data[1] = TMP101TEMP;
    i2ctransmit(&trans);
    
    unsigned int retVal = (int) temp[1] >> 4;
    retVal |= ((int) temp[0]) << 4;
    return retVal;
}