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
int_u8 reception_msg[500];
int_u8 transmision_msg;
void main()
{
    uart_init(9600,HIGH_BAUD_DISBALED);
while(1)
{
#ifdef TRANSMISSION
    uart_write(0xC0);
#else
    uart_read();
#endif
}

}

void uart_init(int_u32 baud_rate, int_u8 high_baud_select)
{
    TX=0; /*CONFIGURED TRISC<6> AS OUTPUT PIN*/
    RX=0; /*CONFIGURED TRISC<7> AS INPUT PIN*/
    TXSTAbits.BRGH=high_baud_select;/*High Baud Rate Select bit */
    TXEN=1;/*Transmit Enable bit*/
    TX9=0; /*9-bit Transmit Enable bit: 1 = Synchronous mode,0 = Asynchronous mode*/
    SYNC=0;/*USART Mode Select bit */
    SPEN=1;/*Serial Port Enable bit*/
    RX9=0;/*9-bit Receive Enable bit*/
    CREN=0;/*Continuous Receive Enable bit:1 = Enables continuous receive,0 = Disables continuous receive*/
    ADDEN=0;/*Address Detect Enable bit
             1 = Enables address detection, enables interrupt and load of the receive buffer when RSR<8>is set
             0 = Disables address detection, all bytes are received and ninth bit can be used as parity bit*/
    SPBRG=(FOSC/(64*baud_rate))-1;
    GIE=1;/*Global Interrupt Enable bit*/
    PEIE=1;/*Peripheral Interrupt Enable bit*/
    TXIE=1;/*USART Transmit Interrupt Enable bit*/
    RCIE=1;/*USART Receive Interrupt Enable bit*/
    TRMT=0;
}
void uart_write(int_u8 write_msg)
{
    if(TRMT)
    {
        transmision_msg=write_msg;

    }
}
void uart_read()
{

}
void interrupt isr(void)
{
    if(RCIF)
    {
        RCIF=0;
    }
    if(TXIF)
    {
        TXIF=0;
    }
}