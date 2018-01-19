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
int_u8 hour_dec,min_dec,sec_dec,day_dec,date_dec,month_dec,year_dec;
int_u8 inc = 0,flag = 0;
int_u8 key_nav=0;
void main()
{
    
    
    TRISD=0X00;
    TRISE=0X00;
    TRISB=0XFF;
    TRISA=0X00;
    PORTD=0X00;
    RBIE=SET;
    OPTION_REG=0XB0;
    

   
   i2c_pkt.address=RTC_ADD;
   i2c_pkt.data=0x00;
   i2c_pkt.ack =0;
#ifdef MASTER_MODE
   lcd_init();
   i2c_master_init();
  // master_tx(&i2c_pkt);
   while(1)
   {
#if 1
       int i;
  //  PORTD=0xFF; testing code
            
           master_tx(&i2c_pkt);
           for(i=0,timer=(int_u8 *)&local_time;i<7;i++,timer++)
           master_rx(&i2c_pkt,timer);


           hex2char(local_time.HH,hour);
           hex2char(local_time.MM,min);
           hex2char(local_time.SS,sec);

           sprintf(lcd_msg,"Time: %d%d-%d%d-%d%d  ",hour[1],hour[0],min[1],min[0],sec[1],sec[0]);
           lcd_cmnt(0x80);
           uart_lcd_update(lcd_msg,sizeof(lcd_msg));
           hex2char(local_time.date,date);
           hex2char(local_time.month,month);
           hex2char(local_time.year,year);
           sprintf(lcd_msg1,"Date: %d%d-%d%d-%d%d  ",date[1],date[0],month[1],month[0],year[1],year[0]);
           lcd_cmnt(0xC0);
           uart_lcd_update(lcd_msg1,sizeof(lcd_msg1));
           delay(100);
#endif
             
       while(flag)
       {
      //     flag=0;
           
            //delay(100);
       #if 0
           sprintf(lcd_msg,"Time: %d%d-%d%d-%d%d<-",hour[1],hour[0],min[1],min[0],sec[1],sec[0]);
           lcd_cmnt(0x80);
       #endif

           uart_lcd_update(lcd_msg,sizeof(lcd_msg));
           sprintf(lcd_msg1,"Date: %d%d-%d%d-%d%d<-",date[1],date[0],month[1],month[0],year[1],year[0]);
           lcd_cmnt(0xC0);
           uart_lcd_update(lcd_msg1,sizeof(lcd_msg1));
           //lcd_cmnt(0xC0);



       switch(key_nav)
       {
           

           case DOWN:
               inc_year(year);
               key_nav=0;
               break;

           case UP:
               dec_year(year);
               key_nav=0;
               break;

           case SET_KEY:

               key_nav=0;
               break;
       }
       
       }
        PORTA=1;
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
    RBIE = CLEAR;
    SEN=SET;
    if(i2c_pkt->data!=0)
    {
        i2c_pkt->data = 0;
    }
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
     RBIE = SET;
   return 0;
}
int_u8 master_rx(i2c_pck *i2c_pkt,int_u8 * rx_time)
{
    RBIE = CLEAR;
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

    ACKDT=SET ;
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
    RBIE = SET;
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
    if(RBIF)
    {

    //   delay(10);
       PORTA=2;
        // Read PORTB to avoid LATCHING OF PORTB STATUS in isr
       key_nav = ((0XF0&~PORTB)>>4);

       
        if(RB4==CLEAR)
        {
            flag=!flag;
        }
       
        RBIF = 0;
       

    }

}
void hex2char(int_u8 in, int_u8 *out)
{
    *out= in & 0x0f;
    *(out+1)= in>>4;

}
void hex2integer(int_u8 in, int_u8 *out)
{
    *out= in & 0x0f + (( in & 0xf0 )>>4 * 10) ;
    

}
void int2char(int_u8 in, int_u8 *out)
{
    *out= in % 10 + (in/10)<<4 ;


}

void inc_year(int_u8 *data_ptr)
{
    if(data_ptr[0]==9)
    {
        data_ptr[0]=0;
        if(data_ptr[1]==9)
        {
             data_ptr[1]=0;
            
        }
        else
        {
        data_ptr[1]= data_ptr[1]+1;
        }
    }
    else
    {
        data_ptr[0]=data_ptr[0]+1;
    }

}
void dec_year(int_u8 *data_ptr)
{
    if(data_ptr[0]==0)
    {
        data_ptr[0]=9;
        if(data_ptr[1]==0)
        {
             data_ptr[1]=9;
        }
        else
        {
              data_ptr[1]= data_ptr[0]-1;
        }
    }
    else
    {
        data_ptr[0]=data_ptr[0]-1;
       
    }

}

void master_start(void)
{
    SEN=SET;
    while(!i2c_pkt.ack)
    {
        //WAIT till start condition asserted

    }
    i2c_pkt.ack=0;


}
void master_stop(void)
{
    PEN=SET;
    while(!i2c_pkt.ack)
    {
        //wait till stop bit sent
    }
    i2c_pkt.ack=0;
}
void master_repeat_start(void)
{
    RSEN=SET;
    while(!i2c_pkt.ack)
    {

    }
    i2c_pkt.ack=0;
}