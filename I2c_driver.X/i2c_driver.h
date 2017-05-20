/* 
 * File:   i2c_driver.h
 * Author: Kanna
 *
 * Created on May 1, 2017, 1:11 AM
 */

#ifndef I2C_DRIVER_H
#define	I2C_DRIVER_H
#include <pic18f4520.h>
typedef  short int int_16;
typedef  char int_8;
typedef  int int_32;

typedef  unsigned short int int_u16;
typedef  unsigned char int_u8;
typedef  unsigned int int_u32;
typedef struct packet
{
    int_u8 address;
    int_u8 data;
    int_u8 ack;
}i2c_pck;

int_u8 master_tx(i2c_pck);
int_u8 master_rx(i2c_pck);
int_u8 slave_rx(i2c_pck);
int_u8 slave_tx(i2c_pck);
int_u8 slave_ack(i2c_pck);
int_u8 master_ack(i2c_pck);

#endif	/* I2C_DRIVER_H */

