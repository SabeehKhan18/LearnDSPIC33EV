/**
 * device.h
 * David Mehl
 * 
 *  
 * 
 */

#ifndef _DEVICE_H_
#define _DEVICE_H


typedef enum {
    FRC = 0b000,
    FRCPLL,
    EC_XT_HS,
    EC_XT_HS_PLL,
    BFRC,
    LPRC,
    FRCDIV16,
    FRCDIVN
} oscillator_t;

/*
 * Here are the guidelines to using the oscillator
 * The default numbers achieve a frequency of 80 MHz -> System Freq. 40 MHz
 * 
 * FOSC = ((Fin / (N1 + 2)) * (M + 2)) / (N2 + 2)
 * If using the internal oscillator, Fin = 7.37 MHz (nominal)
 * 
 * NOTE: If using PLL,
 * Fin / (N1 + 2) must be greater than .8 MHz and less than 8 MHz
 * 120 MHz <= Fin / (N1 + 2) * (M + 2) <= 340 MHz
 * 15 MHz <= Fin / (N1 + 2) * (M + 2) / (N2 + 2) <= 120 MHz
 * 
*/
////////////////////////////////////////////////////////////////////////////////
//                      MODIFY BELOW TO SET CLOCK                             //
////////////////////////////////////////////////////////////////////////////////
// Define PLL constants
#define CLOCK_MULTIPLIER    41  // M,  Default 41
#define CLOCK_PREDIV        0x0 // N1, Default 0
#define CLOCK_POSTDIV       0x0 // N2, Default 0

//Define the clock type here, for NOSC in OSCCON during setup
//Look in the oscillator_t enumeration for options
#define CLOCK_TYPE          FRCPLL //Internal oscillator with PLL, FRCPLL

////////////////////////////////////////////////////////////////////////////////
//                      END MODIFICATION AREA                                 //
////////////////////////////////////////////////////////////////////////////////



//Sets up the device from a RESET or POWER_UP condition
void device_initialize(void);

//Initializes the oscillator based on defines above
void device_oscInit(void);


/**
 * Sets the oscillator parameters
 * 
 * @param osc Oscillator mode desired
 */
void device_setOscillator(oscillator_t osc);

//Disables global interrupts
void device_disableInterrupts(void);

//Enables global interrupts
void device_enableInterrupts(void);

#endif
