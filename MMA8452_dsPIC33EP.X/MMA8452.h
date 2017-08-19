/* 
 * File:   MMA8452.h
 * Author: george
 *
 * Created on August 10, 2017, 9:18 AM
 */

#ifndef MMA8452_H
#define	MMA8452_H

/**
 * Initializes the I2C connection to the accelerometer
 * 
 * @return success
 */
int mma8452_init();

/**
 *  Gets the X acceleration
 *
 * @return x acceleration
 */

int mma8452_getX();

/**
 * Gets the y acceleration
 * 
 * @return y acceleration
 */
int mma8452_getY();

/**
 * Gets the z acceleration
 * 
 * @return z acceleration 
 */
int maa8452_getZ();

#endif	/* MMA8452_H */

