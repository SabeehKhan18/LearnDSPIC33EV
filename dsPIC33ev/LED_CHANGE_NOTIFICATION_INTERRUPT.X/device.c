/*
 * File:   device.c
 * Author: David Mehl
 *
 * Created on August 2, 2016, 9:09 PM
 */


#include  "xc.h"

#include "device.h"


void device_initialize(void) {
    device_oscInit();
}

void device_oscInit(void) {
    //Set up constants to get 80 MHz FOsc

    //Shut off interrupts to complete unlock and switch
    device_disableInterrupts();

    //Set up clock constants
    CLKDIVbits.PLLPRE = CLOCK_PREDIV;
    CLKDIVbits.PLLPOST = CLOCK_POSTDIV;
    PLLFBDbits.PLLDIV = CLOCK_MULTIPLIER;

    //Need to use assembly because must be completed in 3 Instr. Cyc.
    device_setOscillator(CLOCK_TYPE);

}

void device_setOscillator(oscillator_t osc) {
    __builtin_write_OSCCONH(osc);
    __builtin_write_OSCCONL(OSCCONL | 1);

    while (OSCCONbits.OSWEN);
}

void device_disableInterrupts(void){
    INTCON2bits.GIE = 0;
}

void device_enableInterrupts(void){
    INTCON2bits.GIE = 1;
}

