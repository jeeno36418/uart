/*
 * File:   uart_driver.c
 * Author: Kanna
 *
 * Created on December 28, 2019, 1:55 PM
 */


#include"uart.h"
#include"adc_driver.h"
#include "stdio.h" 

/********************************************************
 Function Description: This function is used to initialize
 * UART protocol with baud rate 9600. and enable high baud
 * mode  
 Variable Used:high_baud_select
 Return Value: None
 ********************************************************/
 
void uart_init(int_u8 high_baud_select)
{
    TRISC6=1; /*CONFIGURED TRISC<6> AS OUTPUT PIN*/
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
    SPBRG=129;/*Configured as 9600 for 20MHz clock*/
    GIE=1;/*Global Interrupt Enable bit*/
    PEIE=1;/*Peripheral Interrupt Enable bit*/
   // TXIE=1;/*USART Transmit Interrupt Enable bit*/
    RCIE=1;/*USART Receive Interrupt Enable bit*/
}

void uart_write(int_u8 write_msg)
{
       while(!TRMT)
       transmision_msg=write_msg;

       TXIE=1;


}
void uart_read(void)
{

      rx_msg_buf[rx_index].rxmsg=RCREG;
        
}
void uart_write_string(int_u8 *data)
{   

while(*data)
uart_write(*data++);
    

}
/********************************************************
 * Function Name: uart_bluetooth_receive
 * Function Description: This function is used to process
 * received bluetooth message and pass command to the 
 * uart_bluetooth_command_handler function
 * Variable Used:i
 * Return Value: None
 ********************************************************/
void uart_bluetooth_receive(void)
{
    int_u8 i,index;
    if(received == TRUE)
    {
        received = FALSE;
        if(rx_msg_buf[rx_index-1].rxmsg == '\n')
        {
            rx_index = 0;
            index = rx_msg_buf[0].rxmsg - '0';
            if(index > RX_BUF_SIZE)
            {
                index = RX_BUF_SIZE;
            }
            for(i = 0; i < index; i++)
            {
                 bt_msg[i] = rx_msg_buf[i].rxmsg;
            }
            bt_msg[i] = '\0';
            uart_bluetooth_command_handler(bt_msg[1]);
            uart_write('\r');
            uart_write_string(reply);
            uart_write('\n');            
        }

    }
}

/********************************************************
 * Function Name: uart_bluetooth_command_handler
 * Function Description: This function is used to process
 * command to the 
 * 
 * Return Value: None
 ********************************************************/
void uart_bluetooth_command_handler(int_u8 cmd)
{
    
    switch(cmd)
    {
        case '0':
            sprintf((char *)reply,"LED STATUS : OFF");   
            LATBbits.LB0 = 0;  
            break;
        case '1':
            sprintf((char *)reply,"LED STATUS : ON ");
            LATBbits.LB0 = 1;            
            break;
        case '2':
            sprintf((char *)reply,"Time: %10ld",counter);
            break;
        case '3':
            sprintf((char *)reply,"Step: %10ld",stepper_count); 
            motor_dir_status = FORWARD_DIR;
            break;
        case '4':
            sprintf((char *)reply,"Step: %10ld",stepper_count); 
            motor_dir_status = REVERSE_DIR;           
            break;
        case '5':
            sprintf((char *)reply,"Stop motor");
            motor_dir_status = MOTOR_STOP;
            run_preset_flag = FALSE;
            break;
        case '6':
            channel_index = 0;
            sprintf((char *)reply,"Temperature %d",adc_value[channel_index]);
            break;
        case '7':
            channel_index = 1;
            sprintf((char *)reply,"Temperature %d",adc_value[channel_index]);
            break;
        case '8':
            sprintf((char *)reply,"Preset 0: %d",stepper_count); 
            preset[0] = stepper_count;
            break;
        case '9':
            run_preset_flag = TRUE;
            motor_dir_status = MOTOR_STOP;
            desired_pos = preset[0];
            break;
        case 'A':
            sprintf((char *)reply,"Preset 1: %d",stepper_count); 
            preset[1] = stepper_count;
            break;
        case 'B':
            run_preset_flag = TRUE;
            motor_dir_status = MOTOR_STOP;
            desired_pos = preset[1];
            break;
        case 'C':
            sprintf((char *)reply,"Preset 2: %d",stepper_count); 
            preset[2] = stepper_count;
            break;
        case 'D':
            run_preset_flag = TRUE;
            motor_dir_status = MOTOR_STOP;
            desired_pos = preset[2];
            break;
        case 'E':
            sprintf((char *)reply,"Preset 3: %d",stepper_count); 
            preset[3] = stepper_count;
            break;
        case 'F':
            run_preset_flag = TRUE;
            motor_dir_status = MOTOR_STOP;
            desired_pos = preset[3];
            break;            
        default:
            break;
    }
}
/********************************************************
 * Function Name: uart_bluetooth_stepper_forward
 * Function Description: This function will rotate 
 * stepper motor
 * command to the 
 * 
 * Return Value: None
 ********************************************************/
void uart_bluetooth_stepper_forward(void)
{ 
    PORTB = 0x30;
    __delay_ms(STEP_DELAY);
    PORTB = 0x60;
    __delay_ms(STEP_DELAY);
    PORTB = 0xC0;
    __delay_ms(STEP_DELAY);
    PORTB = 0x90;
     __delay_ms(STEP_DELAY);
    stepper_count++;
    
    
}
/********************************************************
 * Function Name: uart_bluetooth_stepper_reverse
 * Function Description: This function will rotate 
 * stepper motor
 * command to the 
 * 
 * Return Value: None
 ********************************************************/
void uart_bluetooth_stepper_reverse(void)
{ 
    PORTB = 0x90;
    __delay_ms(STEP_DELAY);
    PORTB = 0xC0;
    __delay_ms(STEP_DELAY);
    PORTB = 0x60;
    __delay_ms(STEP_DELAY);
    PORTB = 0x30;
     __delay_ms(STEP_DELAY);
    stepper_count--;
    
    
}
/********************************************************
 * Function Name: uart_bt_preset_set_position
 * Function Description: This function will set the  
 * desired position of the stepper
 * command to the 
 * 
 * Return Value: None
 ********************************************************/
void uart_bt_preset_set_position(int_32 des_pos)
{
    if(stepper_count == des_pos)
    {
        run_preset_flag = FALSE;
    }
    else if(stepper_count > des_pos)
    {
        uart_bluetooth_stepper_reverse();
        PORTB = 0;
       
    }
    else if(stepper_count < des_pos)
    { 
       uart_bluetooth_stepper_forward();
       PORTB = 0;
    }
}