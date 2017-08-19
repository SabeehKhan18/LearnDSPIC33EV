/*
 * File:   main.c
 * Author: Sabeeh
 *
 * Created on August 9, 2017, 9:00 PM
 */


#include "xc.h"
#include "canbus.h"

int main(void) {
    ANSELA = ANSELB = 0;
    
    can_init();
    return 0;
}
