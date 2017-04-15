/* 
 * File:   uart.c
 * Author: Kanna
 *
 * Created on April 8, 2017, 11:00 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include"uart.h"
#include"global.h"
int_u8 reception_msg[32]={'0'};
int_u8 transmision_msg,count=30,recieved=0;
#define port PORTD
#define rs RE0
#define en RE1
#define latch en=1;delay(10);en=0;

void main()
{
    TRISB=0x00;
    TRISD=0X00;
    TRISE=0X00;
    PORTB=0X00;
    PORTE=0X00;
//    mmset((void *)reception_msg,'0',(register)sizeof(reception_msg));
    uart_init(9600,HIGH_BAUD_DISBALED);
    lcd_init();
while(1)
{
#ifdef TRANSMISSION
    
    uart_write(count++);
     delay_ms(100);
    PORTD=0XFF;
    delay_ms(100);
    delay_ms(100);
    delay_ms(100);
#else
    if(recieved)
    {
        lcd_data(count++);
      //  uart_lcd_update();
        recieved=0;
    }
#endif
}

}

void uart_init(int_u32 baud_rate, int_u8 high_baud_select)
{
    TRISC6=0; /*CONFIGURED TRISC<6> AS OUTPUT PIN*/
    TRISC7=1; /*CONFIGURED TRISC<7> AS INPUT PIN*/
    TXSTAbits.BRGH=high_baud_select;/*High Baud Rate Select bit */
    TXEN=1;/*Transmit Enable bit*/
    TX9=0; /*9-bit Transmit Enable bit: 1 = Synchronous mode,0 = Asynchronous mode*/
    SYNC=0;/*USART Mode Select bit */
    SPEN=1;/*Serial Port Enable bit*/
    RX9=0;/*9-bit Receive Enable bit*/
    CREN=1;/*Continuous Receive Enable bit:1 = Enables continuous receive,0 = Disables continuous receive*/
    ADDEN=0;/*Address Detect Enable bit
             1 = Enables address detection, enables interrupt and load of the receive buffer when RSR<8>is set
             0 = Disables address detection, all bytes are received and ninth bit can be used as parity bit*/
    SPBRG=(((FOSC/64)/baud_rate)-1);
    GIE=1;/*Global Interrupt Enable bit*/
    PEIE=1;/*Peripheral Interrupt Enable bit*/
   // TXIE=1;/*USART Transmit Interrupt Enable bit*/
    RCIE=1;/*USART Receive Interrupt Enable bit*/
 

}
void uart_write(int_u8 write_msg)
{

        transmision_msg=write_msg;

       TXIE=1;
       PORTD=0X00;


    
}
void uart_read()
{

      reception_msg[0]=RCREG;
        
}
void set_port()
{
    if(recieved)
    {
    PORTB=reception_msg[0];
    recieved=0;
    }

}

void uart_lcd_update()
{   int i;
    for(i=0;i<32;i++)
    {
        lcd_data(reception_msg[i]);
    }

}

void interrupt isr(void)
{
    if(RCIF)
    {
       uart_read();
       recieved=1;

       
    }
    if(TXIF)
    {
        TXREG=transmision_msg;
        TXIE=0;
    }
}
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
    lcd_cmnt(0x0E);
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


void delay(int x)
{
    int i,j;
    for(i=0;i<=x;i++)
    {
        for(j=0;j<=x;j++)
        {}
    }
}