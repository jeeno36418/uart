/* 
 * File:   i2c_driver.c
 * Author: Kanna
 *
 * Created on May 1, 2017, 1:11 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "i2c_driver.h"
#include "global.h"
#pragma config CONFIG=0x00

i2c_pck i2c_pkt;
time_T local_time={0};
int_u8 * timer;
int_u8 lcd_msg[16]={0};
int_u8 lcd_msg1[16]={0};
int_u8 hour[2],min[2],sec[2],day,date[2],month[2],year[2];
int_u8 inc = 0,flag = 0;
void main()
{
    
    
    TRISD=0X00;
    TRISE=0X00;
    TRISB=0X01;
    PORTD=0X00;
    

   
   i2c_pkt.address=RTC_ADD;
   i2c_pkt.data=0x00;
   i2c_pkt.ack =0;
#ifdef MASTER_MODE
   lcd_init();
   i2c_master_init();
  // master_tx(&i2c_pkt);
   while(1)
   {
       int i;
  //  PORTD=0xFF; testing code
       if(flag)
       {
           master_tx(&i2c_pkt);
           for(i=0,timer=(int_u8 *)&local_time;i<7;i++,timer++)
           master_rx(&i2c_pkt,timer);


           int2char(local_time.HH,hour);
           int2char(local_time.MM,min);
           int2char(local_time.SS,sec);

           sprintf(lcd_msg,"Time: %d%d-%d%d-%d%d",hour[1],hour[0],min[1],min[0],sec[1],sec[0]);
           lcd_cmnt(0x80);
           uart_lcd_update(lcd_msg,sizeof(lcd_msg));
           int2char(local_time.date,date);
           int2char(local_time.month,month);
           int2char(local_time.year,year);
           sprintf(lcd_msg1,"Date: %d%d-%d%d-%d%d",date[1],date[0],month[1],month[0],year[1],year[0]);
           lcd_cmnt(0xC0);
           uart_lcd_update(lcd_msg1,sizeof(lcd_msg1));
           flag=0;
           
       }
       if(RB0==SET)
       {
          if(inc%2==1)
          flag =1;
       }
       else
       {
          inc++;
       }
 /*     if(RD0==1)
          RD1=1;
      else
          RD1=0;*/
   }
#else

#endif
}

void i2c_master_init(void)
{

        TRISC3 = 1;      /* SDA and SCL as input pin */
	TRISC4 = 1;      /* these pins can be configured either i/p or o/p */
	SSPADD = 0x28;    /* 100Khz @ 4Mhz Fosc */
        SSPSTAT |= 0x80; /* Slew rate disabled */
	SSPCON = 0x28;   /* SSPEN = 1, I2C Master mode, clock = FOSC/(4 * (SSPADD + 1)) */
	GIE = SET;
        PEIE = SET;
        SSPIE = SET;
#if 0
        

   TRISC3=SET;//SCL CONFIGURED AS O/P PIN FOR MASTER MODE
   TRISC4=SET;//SDA CONFIGURED AS O/P PIN FOR MASTER MODE
   SSPEN=SET;
   SSPSTAT=0x80;
   SSPCON1|=0x08;
   SSPCON2=0;
   SSPADD=0x09;
   INTCON=0xC0;
   SSPIE=SET;
   BCLIE=SET;
   SSPIP=SET;
   GIE=SET;
   
   
   //RCEN=SET;
#endif

}

int_u8 master_tx(i2c_pck *i2c_pkt)
{
    SEN=SET;
    while(!i2c_pkt->ack)
    {    
        //WAIT FOR SSPIF TO CLEAR ;

    }
    i2c_pkt->ack=0;
   // PORTD=0X01;
    SSPBUF=(i2c_pkt->address<<1|WRITE);
    while(!i2c_pkt->ack);
        i2c_pkt->ack=0;
    SSPBUF=i2c_pkt->data;
 //   PORTD=0X02;
    while(!i2c_pkt->ack);
        i2c_pkt->ack=0;
    
    
    PEN=SET;
    while(!i2c_pkt->ack);
        i2c_pkt->ack=0;
#if 0
    RSEN=SET;
    while(!i2c_pkt->ack);
        i2c_pkt->ack=0;
    SSPBUF=i2c_pkt->data;
#endif
   return 0;
}
int_u8 master_rx(i2c_pck *i2c_pkt,int_u8 * rx_time)
{
  SEN=SET;
    while(!i2c_pkt->ack)
    {
        //WAIT FOR SSPIF TO CLEAR ;

    }
    i2c_pkt->ack=0;
  //  PORTD=0X01;
    SSPBUF=(i2c_pkt->address<<1|READ);
    while(!i2c_pkt->ack);
        i2c_pkt->ack=0;
 /*   SSPBUF=i2c_pkt->data;
    PORTD=0X02;
    while(!i2c_pkt->ack);
        i2c_pkt->ack=0;*/
    RCEN=SET;
    while(!i2c_pkt->ack);
        i2c_pkt->ack=0;
    *rx_time=SSPBUF;

    ACKDT=1 ;
    ACKEN=SET;
    while(!i2c_pkt->ack);
        i2c_pkt->ack=0;

 /*
    while(!i2c_pkt->ack);
        i2c_pkt->ack=0;
    PORTD=0X08;
    SSPBUF=0x00;
    while(!i2c_pkt->ack);
        i2c_pkt->ack=0;*/
   // PORTD=0X10;
    PEN=SET;
    while(!i2c_pkt->ack);
        i2c_pkt->ack=0;
#if 0
    RSEN=SET;
    while(!i2c_pkt->ack);
        i2c_pkt->ack=0;
    SSPBUF=i2c_pkt->data;
#endif
   return 0;

}
void i2c_slave_init()
{
   TRISC3 = SET;//SCL CONFIGURED AS O/P PIN FOR MASTER MODE
   TRISC4 = SET;//SDA CONFIGURED AS O/P PIN FOR MASTER MODE
   SSPEN = SET;
   SSPCON |= 0x08;
   SSPADD = 0x09;
   INTCON = 0xC0;
   SSPIE = SET;
   BCLIE = SET;
   
   GIE = SET;
   PEIE = SET;
   SSPIE = SET;
   //RCEN=SET;


}
void wait()
{
    
}

void interrupt interrupt_isr(void)
{
    
    if(SSPIF)
    {
       i2c_pkt.ack=1;
      

        SSPIF = 0;
      

    }

}
void int2char(int_u8 in, int_u8 *out)
{
    *out= in & 0x0f;
    *(out+1)= in>>4;

}
