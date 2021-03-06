/* 
 * File:   global.h
 * Author: Kanna
 *
 * Created on April 8, 2017, 11:33 PM
 */

#ifndef GLOBAL_H
#define	GLOBAL_H
#include "lcd_driver.h"
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
void delay(int x);
void lcd_init(void);
void lcd_data(int_u8 data);
void lcd_cmnt(int_u8 cmnt);
void uart_lcd_update(int_u8 *,int_u8);
void timer_init(void);
void timer_isr(void);
int_u8 rx_timer_opr();
typedef struct timer_min_max
{
    
    int_u8 min;
    int_u8 max;
    
    
}time_mm;
typedef struct timer_t
{
    int_u8 SS;
    int_u8 MM;
    int_u8 HH;
    int_u8 day;
    int_u8 date;
    int_u8 month;
    int_u8 year;
}time_T;

#endif	/* GLOBAL_H */

