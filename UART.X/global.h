/* 
 * File:   global.h
 * Author: Kanna
 *
 * Created on April 8, 2017, 11:33 PM
 */

#ifndef GLOBAL_H
#define	GLOBAL_H

typedef  short int int_16;
typedef  char int_8;
typedef  int int_32;

typedef  unsigned short int int_u16;
typedef  unsigned char int_u8;
typedef  unsigned int int_u32;
#define HIGH_BAUD_SELECTED 1
#define HIGH_BAUD_DISBALED 0
void uart_init(int_u32 baud_rate, int_u8 high_baud_rate);
void uart_write(int_u8 write_msg);
void uart_read(void);
void delay_ms(int_u32 count);
void set_port(void);
#endif	/* GLOBAL_H */

