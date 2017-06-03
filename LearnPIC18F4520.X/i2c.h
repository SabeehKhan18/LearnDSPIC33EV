#ifndef	_I2C_H_
#define _I2C_H_

/*
 *	SDA (data) and SCL (clock) bits
 *	
 *	Special note!!!
 *	
 *	If the clock and data lines are in the same port, you will need
 *	to beware of the Read/Modify/Write issue in the PIC - since
 *	a bit set or clear on any one bit in a port will read and write
 *	back all other bits. 
 */

#ifndef _XTAL_FREQ
 #define _XTAL_FREQ 8000000
#endif

#include <xc.h>


#define I2C_READ	0x01		/* read bit used with address */
#define I2C_WRITE	0x00		/* write bit used with address */

#define I2C_ERROR	(-1)
#define I2C_NACK	1		/* SendNack: failed to receive */
#define I2C_MORE	0		/* SendAck: send more bytes */
#define I2C_LAST	1		/* SendNack: receive complete */

#define i2c_WriteTo(address)	I2C_SendAddress((address), I2C_WRITE)
#define i2c_ReadFrom(address)	I2C_SendAddress((address), I2C_READ)

extern unsigned char    I2C_SendAddress(unsigned char, unsigned char);
extern unsigned char    I2C_SendByte(unsigned char);
extern int		I2C_ReadByte(unsigned char);
extern void 		I2C_Start(void);
extern void		I2C_Restart(void);
extern void		I2C_Stop(void);
extern void 		I2C_Initialize(void);
#endif			/* _I2C_H_ */
