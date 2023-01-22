/*---------------------------------------------------------
Purpose: modulet har til formål at initialisere et knap
interrupt og styre interrupt serviceroutinen som sætter et
flag
Input: Interrupt fra knap
Output: Sætter flag
Uses: "includes.h", "BTN.h"
Author: buster nielsen (s211548)
Company: DTU
Version: 1
Date and year: 20/1 2023
-----------------------------------------------------*/

/* 
Global parameters used:
“Modulet bruger en globale variabler: BTN_flag"
*/

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "includes.h"
#include "BTN.h"

// Initialiserer PB7 som knap interrupt.
void init_BTN_19(){
  PORTD |= (1<<PD2);
  EICRA|=(1<<ISC21)|(1<<ISC20);
  EIMSK|=(1<<INT2);
}

//Service routinen for knap interrupt.
ISR(INT2_vect){
  BTN_flag++;
}