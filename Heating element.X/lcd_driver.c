#include "global.h"
#include <pic18f4520.h>
/*lcd initialization*/

#define port PORTD
#define rs PORTBbits.RB1
#define en PORTBbits.RB2
#define rw PORTBbits.RB3
#define latch en=1;__delay_ms(2);en=0;


void lcd_init()
{
    TRISD=0X00;
    PORTD=0X00;
    ADCON1=0X06;
    lcd_cmnt(0x38);
    __delay_ms(100);
    lcd_cmnt(0x0c);
    __delay_ms(100);
    lcd_cmnt(0x01);
    __delay_ms(100);
    lcd_cmnt(0x80);
    __delay_ms(100);
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
        lcd_data(data[i]);
    }

}

