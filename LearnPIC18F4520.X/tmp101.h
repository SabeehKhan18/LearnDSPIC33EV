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

void initTMP101(void);
int getRawTemp(void);

#endif

