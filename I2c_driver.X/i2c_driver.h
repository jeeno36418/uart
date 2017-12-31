/* 
 * File:   i2c_driver.h
 * Author: Kanna
 *
 * Created on May 1, 2017, 1:11 AM
 */

#ifndef I2C_DRIVER_H
#define	I2C_DRIVER_H
#include <pic16f877a.h>
typedef  short int int_16;
typedef  char int_8;
typedef  int int_32;
#define SET 1
#define CLEAR 0
#define MASTER_MODE
#define READ 1
#define WRITE 0
#define RTC_ADD 0x68
typedef  unsigned short int int_u16;
typedef  unsigned char int_u8;
typedef  unsigned int int_u32;
typedef struct packet
{
    int_u8 address;
    int_u8 data;
    int_u8 ack;
}i2c_pck;

int_u8 master_tx(i2c_pck *);
int_u8 master_rx(i2c_pck *,int_u8 *);
int_u8 slave_rx(i2c_pck);
int_u8 slave_tx(i2c_pck);
int_u8 slave_ack(i2c_pck);
int_u8 master_ack(i2c_pck);
void I2C_Master_Write(unsigned d);
void I2C_Master_Wait()
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}
void I2C_Master_Start()
{
  I2C_Master_Wait();
  SEN = 1;
}

void I2C_Master_RepeatedStart()
{
  I2C_Master_Wait();
  RSEN = 1;
}

void I2C_Master_Stop()
{
  I2C_Master_Wait();
  PEN = 1;
}

void I2C_Master_Write(unsigned d)
{
  I2C_Master_Wait();
  SSPBUF = d;
}
void i2c_master_init(void);
void i2c_slave_init(void);
void int2char(int_u8 , int_u8 *);
void wait(void);
#endif	/* I2C_DRIVER_H */

