#include "global.h"
#include <pic16f877a.h>
/*lcd initialization*/

#define port PORTD
#define rs RE0
#define en RE1
#define latch en=1;delay(10);en=0;

void delay_ms(int_u32 ds)
{
    int i,j;
    for(i=0;i<ds;i++)
        for(j=0;j<ds;j++);
}

void lcd_init()
{
    TRISD=0X00;
    PORTD=0X00;
    ADCON1=0X06;

    lcd_cmnt(0x38);
    lcd_cmnt(0x0c);
    lcd_cmnt(0x01);
    lcd_cmnt(0x80);
}
void lcd_cmnt(unsigned char cmnt)
{
    port=cmnt;
    rs=0;
    latch ;

}
void lcd_data(unsigned char data)
{
    port=data;
    rs=1;
    latch;

}

void uart_lcd_update(int_u8 *data,int_u8 len)
{   int i;

    for(i=0;i<len;i++)
    {
        lcd_data(*(data+i));
    }

}

void delay(int x)
{
    int i,j;
    for(i=0;i<=x;i++)
    {
        for(j=0;j<=x;j++)
        {}
    }
}