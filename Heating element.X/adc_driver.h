/* 
 * File:   adc_driver.h
 * Author: Kanna
 *
 * Created on January 4, 2020, 6:02 PM
 */

#ifndef ADC_DRIVER_H
#define	ADC_DRIVER_H
/*********************************
 * Global Variables definition
 *********************************/
int_u16 adc_value[13] = {0};
int_u8 channel_index = 0;

/*********************************
 Function prototype declaration
 *********************************/
void adc_init(void);
void adc_update(int_u8 adc_channel);
int_u16 adc_read(int_u8 adc_channel);
#endif	/* ADC_DRIVER_H */

