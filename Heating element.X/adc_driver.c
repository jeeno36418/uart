/*
 * File:   adc_driver.c
 * Author: Kanna
 *
 * Created on January 4, 2020, 6:02 PM
 */
#include "global.h"
#include "adc_driver.h"

/********************************************************
 * Function Name:adc_init
 * Function Description: This function is used to initialize
 * analog to digital converstaion on selected analog pin
 * Variable Used: None
 * Return Value: None
 ********************************************************/
void adc_init(void)
{
   ADCON1bits.PCFG = 0x0D;
   ADCON2bits.ADFM = 1;/*A/D Format selected as Right justified*/
   ADIF = CLEAR; /*clear A/D interrupt flag*/
   ADIE = SET; /* Enable A/D Interrupt */
   ADCON0bits.ADON = SET;
   ADCON2bits.ACQT = 2;
   ADCON2bits.ADCS = 2;/*FRC*/
}
/********************************************************
 * Function Name:adc_update
 * Function Description: This function is used to update
 * analog to digital conversion on the analog channel
 * Variable Used: adc_channel
 * Return Value: None
 ********************************************************/
void adc_update(int_u8 adc_channel)
{
    channel_index = adc_channel;
    while(ADCON0bits.GO);
    ADCON0bits.CHS = adc_channel;
    ADCON0bits.GO = SET;    
}
/********************************************************
 * Function Name: adc_read
 * Function Description: This function is used to read
 * given adc channel and return adc value
 * Variable Used: adc_channel
 * Return Value: adc_value
 ********************************************************/
int_u16 adc_read(int_u8 adc_channel)
{
    return  adc_value[adc_channel];
}
