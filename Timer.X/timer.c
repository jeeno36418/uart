/* 
 * File:   timer.c
 * Author: Kanna
 *
 * Created on April 22, 2017, 9:41 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pic16f877a.h>
#include "timer.h"
/*
 * 
 */

void main()
{
    TRISD0=0; /*PORTD0 CONFIGURED AS OUTPUT PIN*/
    RD0=0;/*PORTD 0TH PIN TURNED OFF*/
    timer_init();
    while(1)
    {
        if(timer_flag)
        {
            timer_flag=0;
            RD0=~RD0;


        }
    }


}

void timer_init(void)
{
    T1CON=0x31;/*TURN ON TIMER AND SET PRESCALAR AS 1:8*/
    TMR1H=0x0B;/*CONFIGURED WITH 500ms*/
    TMR1L=0xDC;
    INTCON=0xC0;/*Enable global and peripheral interrupt*/
    PIE1=0x01;/*Enable timer 1 interrupt*/
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