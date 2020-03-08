/* 
 * File:   i2c_driver.h
 * Author: Kanna
 *
 * Created on May 1, 2017, 1:11 AM
 */

#ifndef I2C_DRIVER_H
#define	I2C_DRIVER_H
#include <pic18f4520.h>
#include "global.h"


#define MASTER_MODE
#define READ 1
#define WRITE 0
#define RTC_ADD 0x68

typedef struct packet
{
    int_u8 address;
    int_u8 data;
    int_u8 ack;
}i2c_pck;

typedef enum key_nav
{
    SELECT=1,
    UP,
    DOWN=4,
    SET_KEY=8,

}key_nav_t;

typedef enum nvm
{
    SECONDS=0,
    MINUTES,
    HOURS,
    DAY,
    DATE,
    MONTH,
    YEAR,
    CONTROL,

}nvm_address_index;

/*Heating element definition**/
#define PASS 1
#define FAIL 0
#define HEAT_ELEMNT_CNT 2
#define TEST_TIME 200 /* 1 tick = 10ms, 200 tick = 2second */

int_u8 heat_elmnt_result[HEAT_ELEMNT_CNT]={0};
int_u8 heat_elmnt_short[HEAT_ELEMNT_CNT]={0};
int_u32 heat_elmnt_result_time[HEAT_ELEMNT_CNT]={0};
int_u8 heat_elmnt_flag[HEAT_ELEMNT_CNT]= {0};
void heat_element_testing(void);
void heat_element_device_select(int_u8 relay_number);
void heat_element_device_deselect(int_u8 relay_number);
void heat_elmnt_result_update(void);
/**Heating element definitions end*/
int_u8 master_tx(i2c_pck *);
int_u8 master_rx(i2c_pck *,int_u8 *);
int_u8 master_tx_write(i2c_pck *);
int_u8 slave_rx(i2c_pck);
int_u8 slave_tx(i2c_pck);
int_u8 slave_ack(i2c_pck);
int_u8 master_ack(i2c_pck);
void i2c_master_init(void);
void i2c_slave_init(void);

void hex2char(int_u8 in, int_u8 *out,int_u8 mask);
int_u8 hex2integer(int_u8 *in);
void int2hex(int_u8 in, int_u8 *out);
int_u8 char2int(int_u8 *in);
void inc_year(int_u8 *,int_u8 );
void dec_year(int_u8 *,int_u8 );
void space_stuff(int_u8 *, int_u8 );
void master_wait(void);
void master_start(void);
void master_stop(void);
void master_repeat_start(void);
void keypad_update(void);
void i2c_driver_motor_control_update(void);
void i2c_adc_update(void);
#endif	/* I2C_DRIVER_H */

