/*---------------------------------------------------------
Purpose: modulet har til formål at initialisere en timer og
og styre timer interrupt serviceroutinen
Input: Interrupt fra timer
Output: Sætter flag, starter ADC sampling
Uses: "includes.h", "timer.h"
Author: buster nielsen (s211548)
Company: DTU
Version: 1
Date and year: 20/1 2023
-----------------------------------------------------*/

/* 
Global parameters used:
“Modulet bruger 4 globale variabler: LCD_count, display_flag, PWM_count, run_flag”
*/

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "includes.h"
#include "timer.h"

// Initialiserer timer 3
void init_timer3(int compareval){
  TCCR3B|=(1<<WGM32)|(0<<CS32)|(1<<CS31)|(0<<CS30); // CTC mode / /Prescale 8
  OCR3A = compareval;  // Det giver en frekvens på 8 kHz
  TIMSK3|=(1<<OCIE3A); // Timer interrpt aktiveres
}

// Serviceroutine for compare match - timer 3
ISR(TIMER3_COMPA_vect){

  if(disp_count++ == 8000)
    disp_flag = 1;

  if(PWM_count++){
    PORTB ^= (1<<PB7);
    PWM_count = 0;
  }
  
  if(run_flag)
    ADCSRA |= (1<<ADSC);
  
}