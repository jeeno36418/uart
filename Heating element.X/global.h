/* 
 * File:   global.h
 * Author: Kanna
 *
 * Created on April 8, 2017, 11:33 PM
 */

#ifndef GLOBAL_H
#define	GLOBAL_H
#include "lcd_driver.h"
#include "configuration_bits.h"
typedef  int int_16;
typedef  char int_8;
typedef  long int int_32;

typedef  unsigned int int_u16;
typedef  unsigned char int_u8;
typedef  unsigned long int int_u32;
#define HIGH_BAUD_SELECTED 1
#define HIGH_BAUD_DISBALED 0

void delay_ms(int_u32 count);
void set_port(void);
void delay(int x);
void lcd_init(void);
void lcd_data(int_u8 data);
void lcd_cmnt(int_u8 cmnt);
void uart_lcd_update(int_u8 *,int_u8);

void timer_isr(void);
int_u8 rx_timer_opr();
#define _XTAL_FREQ 20000000
#define SUCCESS 0
#define FAILURE 1
#define SET 1
#define CLEAR 0
/********************************************
 * Function prototype declaration
 *******************************************/
int_u8 timer_init(int_u32 delay);
void led_test(void);

/********************************************
 * Global variables declaration
 *******************************************/

int_16 timer_flag=0;
int_u32 timer_value = 0;
int_u32 counter = 0;
int_u32 counter_mod_value = 0;
int_u8 led_serial_blink = 0;
int_u8 adc_update_flag = 1;
typedef struct
{
    
    int_u8 min;
    int_u8 max;
    
    
}time_mm;
typedef struct
{
    int_u8 SS;
    int_u8 MM;
    int_u8 HH;
    int_u8 day;
    int_u8 date;
    int_u8 month;
    int_u8 year;
}time_T;

typedef struct
{
    int_u8 rxmsg;
    int_u8 read_sts;
}uart_rx_t;

typedef struct
{
    int_u16 adc_arr[214];

}adc_ary_t;


#endif	/* GLOBAL_H */

