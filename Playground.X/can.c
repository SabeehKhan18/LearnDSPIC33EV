/* 
 * File:   can.h
 * Author: George Main IV
 *
 * Created on August 5, 2017, 9:20 AM
 */

#include "can.h"
#include "xc.h"

void can_init() {
    
    TRISAbits.TRISA3 = 1;
    TRISAbits.TRISA4 = 0;
    
    RPOR4bits.RP43R = 0b001110; // C1TX on RP43 (Pin 22)
    RPINR26bits.C1RXR = 0b0101010; // C1RX on pin RP42 (Pin 21)
            
    
}