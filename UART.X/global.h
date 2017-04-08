/* 
 * File:   global.h
 * Author: Kanna
 *
 * Created on April 8, 2017, 11:33 PM
 */

#ifndef GLOBAL_H
#define	GLOBAL_H

#define int_16 short int
#define int_8 char
#define int_32 int

#define int_u16 unsigned short int
#define int_u8 unsigned char
#define int_u32 unsigned int
#define HIGH_BAUD_SELECTED 1
#define HIGH_BAUD_DISBALED 0
void uart_init(int_u32 baud_rate, int_u8 high_baud_rate);
void uart_write(int_u8 write_msg);
void uart_read(int_u8 read_msg);

#endif	/* GLOBAL_H */

