/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TMP_101_H
#define	TMP_101_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define TMP101TEMP 0x00
#define TMP101CONFIG 0x01

void initTMP101(void);
unsigned int getRawTemp(void);

#endif

