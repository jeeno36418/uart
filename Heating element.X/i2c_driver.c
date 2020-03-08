/* 
 * File:   i2c_driver.c
 * Author: Kanna
 *
 * Created on May 1, 2017, 1:11 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "i2c_driver.h"
#include "adc_driver.h"
#include "global.h"
#include "string.h" 
#include "uart.h"
#define DEBUG 1  
#define INCOMPLETE 0
#define COMPLETE 1
i2c_pck i2c_pkt = {0};
time_T local_time={0};
time_mm timer_min_max[6]={0,23,0,59,0,59,1,31,1,12,0,99};

int_u8 lcd_msg[16]={0},*timer;
int_u8 lcd_msg1[16]={0};
int_u8 hour[2],min[2],sec[2]={0},day,date[2],month[2],year[2];
int_u8 *timer_ptr[7]={sec,min,hour,&day,date,month,year };
int_u8 *lcd_ptr[6]={hour,min,sec,date,month,year };
int_u8 inc = 0,flag = 0;
int_u8 key_nav=0,update_count=0;
int_u32 i2c_mas_time = 0,start_time,end_time;
int_u32 loop_count=0;
int_u8 test_status = INCOMPLETE;
//adc_ary_t heating_elemnt_adc_value[2]={0};
int_u16 heating_elemnt_adc_value[214]={0};
void main()
{
    int_u8 lcd_test[16]="Initializing... ",i;
    int_u32 current_time = 0;
    TRISC = 0x00;
    TRISD=0X00;
    TRISE=0X00;
    TRISB=0X08;
    TRISA=0X03;
    PORTD=0X00;
    PORTB= 0x00;
    PORTC = 0X03;
   i2c_pkt.address=RTC_ADD;
   i2c_pkt.data=0x00;
   i2c_pkt.ack =0;

   lcd_init();
//   i2c_master_init();
   timer_init(10);
   adc_init();
   /*Initialize UART WITH High baud mode for bluetooth application*/
   lcd_cmnt(0x80);
   uart_lcd_update(lcd_test,sizeof(lcd_test));
   TRISE= 0;
   while(1)
   {    
       current_time = counter + 200;
       while(current_time > counter && test_status == INCOMPLETE)
       {
           adc_update(0);
       }

      // heat_element_testing();
       if(test_status == INCOMPLETE)
       {
        heat_element_testing();
        heat_elmnt_result_update();
       }
       else
       {
            for(i = 0; i < 214; i++)
           {
               lcd_cmnt(0x80);
               sprintf((char *)lcd_test,"I%5u A%8u",i,loop_count);
               uart_lcd_update(lcd_test,sizeof(lcd_test));
               adc_update(0);
                lcd_cmnt(0xc0);
                sprintf((char *)lcd_test,"Adc:%12x",adc_value[0]);
                uart_lcd_update(lcd_test,sizeof(lcd_test));               
               __delay_ms(1000);
           }      
       }
      
   }
}

  void heat_element_testing(void)
{
    int i,current_time;
    int_u8 lcd_test[16]={0};
    int_u32 testing_elapse_time[HEAT_ELEMNT_CNT] = {0};
    memset(heat_elmnt_flag,0,sizeof(heat_elmnt_flag));
    memset(heat_elmnt_short,0,sizeof(heat_elmnt_short));
    for(i = 0 ; i < HEAT_ELEMNT_CNT; i++)
    {
        heat_element_device_select(i);
        testing_elapse_time[i] = counter+TEST_TIME;
        loop_count = 0;
        while(testing_elapse_time[i] > counter)
        {
           
           
//            lcd_cmnt(0x80);
//            sprintf((char *)lcd_test,"%d:%6lu %7lu",i,testing_elapse_time[i],counter);
//            uart_lcd_update(lcd_test,sizeof(lcd_test)); 
//            lcd_cmnt(0xc0);
//            sprintf((char *)lcd_test,"address:%4x%2x",&adc_value,sizeof(adc_value));
//            uart_lcd_update(lcd_test,sizeof(lcd_test));             
            adc_update(0);
            if(loop_count <215)
            heating_elemnt_adc_value[loop_count]= adc_value[0];
            if((adc_value[0] > 368.64) && (adc_value[0] < 409.6) && (heat_elmnt_flag[i] == CLEAR))
            {
                heat_elmnt_result[i]= PASS;
                heat_elmnt_short[i]= PASS;
                heat_elmnt_result_time[i] = counter;
                heat_elmnt_flag[i] = SET;
 
            }
            else if(adc_value[0] >= 736.56)
            {
                heat_elmnt_result[i] = PASS;
                heat_elmnt_short[i]= FAIL;
                heat_elmnt_result_time[i] = counter;
              //  break;
            }                
           loop_count++;;      
        }
        heat_element_device_deselect(i);
    }  
    test_status = COMPLETE;
}
/********************************************************
 * Function Name: heat_element_device_select
 * Function Called: None
 * Function Description: This function ENABLE the 
 * relay channel GIO based on the given relay channel number
 * Variables used: relay_number 
 * Return Value: None
 ********************************************************/
void heat_element_device_select(int_u8 relay_number)
{
    switch(relay_number)
    {
        case 0:
            PORTCbits.RC0 = CLEAR;
            break;
        case 1:
            PORTCbits.RC1 = CLEAR;
            break;
        default:
            break;
    }
   
}
/********************************************************
 * Function Name: heat_element_device_deselect
 * Function Called: None
 * Function Description: This function DISABLE the 
 * relay channel GIO based on the given relay channel number
 * Variables used: relay_number  
 * Return Value: None
 ********************************************************/
void heat_element_device_deselect(int_u8 relay_number)
{
    switch(relay_number)
    {
        case 0:
            PORTCbits.RC0 = SET;
            break;
        case 1:
            PORTCbits.RC1 = SET;
            break;
        default:
            break;
    }
}
/********************************************************
 * Function Name: heat_elmnt_result_update
 * Function Called: None
 * Function Description: This function DISABLE the 
 * relay channel GIO based on the given relay channel number
 * Variables used: relay_number  
 * Return Value: None
 ********************************************************/
void heat_elmnt_result_update(void)
{
    int i;
    for(i = 0; i < HEAT_ELEMNT_CNT; i++)
    {
        if(heat_elmnt_result[i] == FAIL)
        {
            switch(i)
            {
                case 0:
                    PORTBbits.RB7 = SET;
                    break;
                case 1:
                    PORTBbits.RB6 = SET;
                    break;
                default:
                    break;
            }
        }
        if(heat_elmnt_short[i] == FAIL)
        {
            switch(i)
            {
                case 0:
                    PORTBbits.RB5 = SET;
                    break;
                case 1:
                    PORTBbits.RB4 = SET;
                    break;
                default:
                    break;
            }            

        }
               
    }
    
}
void i2c_master_init(void)
{

    TRISC3 = 1;      /* SDA and SCL as input pin */
	TRISC4 = 1;      /* these pins can be configured either i/p or o/p */
	SSPADD = 0X28;    /* 100Khz @ 4Mhz Fosc */
    SSPSTAT |= 0x80; /* Slew rate disabled */
	SSPCON1 = 0x28;   /* SSPEN = 1, I2C Master mode, clock = FOSC/(4 * (SSPADD + 1)) */
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
   INTCON=0xC8;
   SSPIE=SET;
   BCLIE=SET;
   SSPIP=SET;
   GIE=SET;
   
   
   //RCEN=SET;
#endif

}
#if DEBUG
int_u8 master_tx(i2c_pck *i2c_pkt)
{

    int_u8 lcd_test[16],status;
    RBIE = CLEAR;
    SEN = SET;
   
    while(!i2c_pkt->ack)
    {    
//        status = SSPSTAT;
//        sprintf((char *)lcd_test,"I2C STATUS %5x",status);
//         lcd_cmnt(0x80);
//         uart_lcd_update(lcd_test,sizeof(lcd_test)); //WAIT FOR SSPIF TO CLEAR ;
//         sprintf((char *)lcd_test,"I2C pin %3x%3x  ",PORTCbits.RC4,PORTCbits.RC3);
//         lcd_cmnt(0xc0);
//         uart_lcd_update(lcd_test,sizeof(lcd_test)); //WAIT FOR SSPIF TO CLEAR ;
    }
    
    i2c_pkt->ack=0;
    SSPBUF=(i2c_pkt->address<<1|WRITE);
    while(!i2c_pkt->ack)NOP();
        i2c_pkt->ack=0;
    SSPBUF=i2c_pkt->data;
    while(!i2c_pkt->ack)NOP();
        i2c_pkt->ack=0;
    PEN=SET;
    while(!i2c_pkt->ack)NOP();
        i2c_pkt->ack=0;
     RBIE = SET;
   return 0;
}

int_u8 master_rx(i2c_pck *i2c_pkt,int_u8 * rx_time)
{
    int_u8 lcd_test[16];
    RBIE = CLEAR;
    SEN = SET;
    while(!i2c_pkt->ack)
    {
       NOP(); //WAIT FOR SSPIF TO CLEAR ;

    }
    i2c_pkt->ack=0;
    SSPBUF=(i2c_pkt->address<<1|READ);
    while(!i2c_pkt->ack)NOP();
        i2c_pkt->ack=0;
    RCEN=SET;
    while(!i2c_pkt->ack)NOP();
        i2c_pkt->ack=0;
    *rx_time=SSPBUF;
    ACKDT=SET ;
    ACKEN=SET;
    while(!i2c_pkt->ack)NOP();
        i2c_pkt->ack=0;
    PEN=SET;
    while(!i2c_pkt->ack)NOP();
        i2c_pkt->ack=0;
    RBIE = SET;
   return 0;

}
#endif
#if 0
void i2c_slave_init()
{
   TRISC3 = SET;//SCL CONFIGURED AS O/P PIN FOR MASTER MODE
   TRISC4 = SET;//SDA CONFIGURED AS O/P PIN FOR MASTER MODE
   SSPEN = SET;
   SSPCON1 |= 0x08;
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
#endif
void space_stuff(int_u8 *in, int_u8 index)
{
    in[0]=0x20;
    in[1]=0x20;
}
#if DEBUG
int_u8 master_tx_write(i2c_pck *i2c_pkt)
{   int i;
    RBIE = CLEAR;
    SEN=SET;

    while(!i2c_pkt->ack)
    {
        NOP();//WAIT FOR SSPIF TO CLEAR ;

    }
    i2c_pkt->ack=0;
    SSPBUF=(i2c_pkt->address<<1|WRITE);
    while(!i2c_pkt->ack)NOP();
        i2c_pkt->ack=0;
    SSPBUF=0;
    while(!i2c_pkt->ack)NOP();
        i2c_pkt->ack=0;
    for(i=0;i<7;i++)
    {
        if(i==3)
            SSPBUF=*(timer_ptr[i]);
        else
            SSPBUF=char2int(timer_ptr[i]);
		while(!i2c_pkt->ack)NOP();
        i2c_pkt->ack=0;
    }
    PEN=SET;
    while(!i2c_pkt->ack)NOP();
        i2c_pkt->ack=0;
    RBIE = SET;
    return 0;

}
#endif
int_u8 timer_init(int_u32 delay)
{
    
    if(delay >100)
    {
      
      counter_mod_value = delay/100;
      delay = 100; 
    }
    else
    {
      counter_mod_value = 1;        
    }
    T1CON=0xB1;/*TURN ON TIMER AND SET PRESCALAR AS 1:8*/
    timer_value = (65536 -(((delay) * _XTAL_FREQ))/((8) * 4000 ));

    if(timer_value > 0xffff)
    TMR1H = (timer_value & 0xff00)>>8;
    TMR1L = timer_value & 0x00ff;
    INTCON=0xC0;/*Enable global and peripheral interrupt*/
    PIE1=0x01;/*Enable timer 1 interrupt*/
    IPR1=0x01;
    return SUCCESS;
}
#if 0
void led_test(void)
{
            
            //PORTCbits.RC1=~PORTCbits.RC1;
            PORTC = 1 << (led_serial_blink % 8);
            led_serial_blink ++;    
}
#endif
void __interrupt() interrupt_isr(void)
{
    
    if(SSPIF)
    {
       SSPIF = 0;
       i2c_pkt.ack=1;
    }
    if(RCIF)
    {
       RCIF = 0;/*Clear RCIF flag Once received data*/ 
       rx_msg_buf[rx_index].rxmsg=RCREG;
       received = TRUE;
       rx_index++;
   }
    if(TXIF&TXIE)
    {
        TXIF=0;
        TXIE=0;
        TXREG=transmision_msg;
    }    
    if(RBIF)
    {
       flag = 1;
       if((0XF0&~PORTB)>>4)
       key_nav = ((0xF0&~PORTB)>>4);        
       RBIF = 0;
   }
    if(TMR1IF)
    {   
        TMR1IF=0;
        counter++;
        TMR1H = (timer_value & 0xff00)>>8;
        TMR1L = timer_value & 0x00ff;
    }
    if(ADIF)
    {
        ADIF = CLEAR;
        adc_value[channel_index] = (ADRESH )<<8 | ADRESL;
    }

}
#if DEBUG
void hex2char(int_u8 in, int_u8 *out,int_u8 mask)
{
    out[0]= in & 0x0f;
    out[1]= (in & mask)>>4;

}
#endif
int_u8 hex2integer(int_u8 *in)
{
    return ( in[0] %10 +  in[1] * 10) ;
       

}
void int2hex(int_u8 in, int_u8 *out)
{
    out[0] = in %10 ;
    out[1] = (in/10) ;
}
int_u8 char2int(int_u8 *in)
{
    return (*(in) | *(in+1)<<4) ;


}

void inc_year(int_u8 *data_ptr,int_u8 index)
{
    int_8 temp = (int_8)hex2integer(data_ptr);
    if(temp >= timer_min_max[index].max)
    {

        temp = timer_min_max[index].min;

    }
    else
    {
        temp++;

    }
    int2hex(temp,data_ptr);

}
void dec_year(int_u8 *data_ptr,int_u8 index)
{
    int_8 temp =(int_8)hex2integer(data_ptr);
    if(temp <= timer_min_max[index].min)
    {
        
        temp = timer_min_max[index].max;
        
    }
    else
    {
        temp--;
       
    }
    int2hex(temp,data_ptr);

}
void keypad_update(void)
{
    int_u8 status;
       while(flag)
       {
#if DEBUG
			
			counter++;
           __delay_ms(350);            
            switch(key_nav)
            {
                case SELECT:
                   key_nav = 0;
                   inc++;
                   if(inc == 7)
                   {
                        inc = 0;
                        flag = 0;

                   }	
                break;	
                case DOWN:
                   dec_year(lcd_ptr[6-inc],6-inc);
                   key_nav=0;
                   break;

                case UP:
                   inc_year(lcd_ptr[6-inc],6-inc);
                   key_nav=0;
                   break;

                case SET_KEY:
                   #if DEBUG
                   status = master_tx_write(&i2c_pkt);
                   #endif
                   flag = 0;
                   key_nav=0;
                   inc=0;
                   break;
            }
            if(inc == 0)
            {
                flag = 0;
                break;
            }
          
#else
           lcd_cmnt(0x80);
           sprintf((char *)lcd_msg1,"inc=%d key =%d",inc);
           uart_lcd_update(lcd_msg1,sizeof(lcd_msg1));          
#endif     
         if(inc < 4)
           {
                space_stuff(lcd_msg1+(11-((inc-1)*3)),inc);
                lcd_cmnt(0xC0);
                uart_lcd_update(lcd_msg1,sizeof(lcd_msg1));           
           }
           else
           {
                space_stuff(lcd_msg+(11-((inc-4)*3)),inc);    
                lcd_cmnt(0x80);
                uart_lcd_update(lcd_msg,sizeof(lcd_msg)); 
                lcd_cmnt(0xC0);
                uart_lcd_update(lcd_msg1,sizeof(lcd_msg1));                
           }
           __delay_ms(100);
           lcd_cmnt(0x80);
           sprintf((char *)lcd_msg,"Time:%d%d-%d%d-%d%d %2x",hour[1],hour[0],min[1],min[0],sec[1],sec[0],PORTD);
           uart_lcd_update(lcd_msg,sizeof(lcd_msg));            
           sprintf((char *)lcd_msg1,"Date:%d%d-%d%d-%d%d%3d",date[1],date[0],month[1],month[0],year[1],year[0],inc);
           lcd_cmnt(0xC0);
           uart_lcd_update(lcd_msg1,sizeof(lcd_msg1));
    }    
}
#if 0 
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
#endif
/********************************************************
 * Function Name: i2c_driver_motor_control_update
 * Function Called:uart_bluetooth_stepper_reverse,
 uart_bluetooth_stepper_forward
 * Function Description: This function motor read 
 motor_dir_status and call the respective function.
 * Variables used: motor_dir_status 
 * Return Value: None
 ********************************************************/
void i2c_driver_motor_control_update(void)
{ 
    if(motor_dir_status == FORWARD_DIR)
    {
        uart_bluetooth_stepper_forward();
        PORTB = 0;
        sprintf((char *)reply,"Step: %10ld",stepper_count); 
         
    }
    else if(motor_dir_status == REVERSE_DIR)
    {
        uart_bluetooth_stepper_reverse();
        PORTB = 0;
        sprintf((char *)reply,"Step: %10ld",stepper_count); 
       
    }
    else
    {
       /*Do nothing stop motor*/ 
    }
 
    
}
/********************************************************
 * Function Name: i2c_adc_update
 * Function Called:adc_update,
 adc_read
 * Function Description: This function update the requested
 * adc channel adc conversation and read the converted value
 * Variables used: motor_dir_status 
 * Return Value: None
 ********************************************************/
void i2c_adc_update(void)
{
    if(adc_update_flag)
    {
        adc_update(channel_index);
       
    }
    else
    {
        /*Do nothing*/
    }
}