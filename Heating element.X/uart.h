/* 
 * File:   uart.h
 * Author: Kanna
 *
 * Created on December 28, 2019, 1:56 PM
 */

#ifndef UART_H
#define	UART_H

#include"global.h"
/*The EUSART control will automatically
reconfigure the pin from input to output as
needed.*/
#define TX TRISC6 /*bit TRISC<6> must be set (= 1)*/
#define RX TRISC7 /*bit TRISC<7> must be set (= 1)*/
#define RX_BUF_SIZE 50
#define TRUE 1
#define FALSE 0
#define STEP_DELAY 5 /*DELAY CONFIGURED IN MS*/
#define FORWARD_DIR 1
#define REVERSE_DIR 2
#define MOTOR_STOP 0
/********************************************************
 Function Global variables
 ********************************************************/
int_u8 transmision_msg,time_flag=0,received=0,count,toggle=0,rx_index= 0,motor_dir_status = MOTOR_STOP;
uart_rx_t rx_msg_buf[RX_BUF_SIZE]={0};   
int_u8 bt_msg[RX_BUF_SIZE]={0};
int_u8 reply[16]={0};
int_32 stepper_count = 0;
int_32 preset[4]={0};
int_32 desired_pos = 0;
int_u8 run_preset_flag = FALSE;
/********************************************************
 Function Prototype declaration
 ********************************************************/
void uart_init(int_u8 high_baud_select);    
void uart_write(int_u8 write_msg);
void uart_read(void);
void uart_write_string(int_u8 *data);
void uart_bluetooth_receive(void);
void uart_bluetooth_command_handler(int_u8 cmd);
void uart_bluetooth_stepper_forward(void);
void uart_bluetooth_stepper_reverse(void);
void uart_bt_preset_set_position(int_32 des_pos);

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

