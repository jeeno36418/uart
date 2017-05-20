/* 
 * File:   timer.c
 * Author: Kanna
 *
 * Created on April 22, 2017, 9:41 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic18f4520.h>
#include "timer.h"
#pragma config CONFIG1H=0x08
#pragma config CONFIG2H=0x00
#pragma config CONFIG4L=0x00
#pragma config CONFIG2L=0x00
/*
 * 
 */

void main()
{
    TRISC=0; /*PORTD0 CONFIGURED AS OUTPUT PIN*/
   PORTC=0XFF;/*PORTD 0TH PIN TURNED OFF*/
   timer_init();
    while(1)
    {
        if(timer_flag)
        {
            timer_flag=0;
            PORTC=~PORTC;


        }
    }


}

void timer_init(void)
{
    T1CON=0xB1;/*TURN ON TIMER AND SET PRESCALAR AS 1:8*/
    TMR1H=0x0B;/*CONFIGURED WITH 500ms*/
    TMR1L=0xDC;
    INTCON=0xC0;/*Enable global and peripheral interrupt*/
    PIE1=0x01;/*Enable timer 1 interrupt*/
    IPR1=0x01;
}

void interrupt timer_isr(void)
{
    if(TMR1IF)
    {
        TMR1IF=0;
        TMR1H=0x0B;/*CONFIGURED WITH 500ms*/
        TMR1L=0xDC;
        timer_flag=1;


    }
}