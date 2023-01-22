/*---------------------------------------------------------
Purpose: modulet har til formål at initialisere ADC'en og
og eksikvere interrupt serviceroutinen
Input: Valg af ADC kanal
Output: Sætter flag
Uses: "includes.h", "ADC.h"
Author: buster nielsen (s211548)
Company: DTU
Version: 1
Date and year: 20/1 2023
-----------------------------------------------------*/

/* 
Global parameters used:
“Modulet bruger 4 globale variabler: buffer[], ADC_count, done_flag, run_flag"
*/

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "includes.h"
#include "ADC.h"

// Bruges til at initialisere ADC hardwaren.
void init_ADC(int chanel)
{
  // Enable ADC
  ADCSRA |= (1<<ADEN);
  // Start sample
  ADCSRA |= (1<<ADSC); //fist sample takes 32 clk's
  // Auto trigger enable.
  //ADCSRA |= (1<<ADATE);
  // Aktiverer kald af sample.
  ADCSRA |= (1<<ADIF); 
  // Aktiverer interrupt.
  ADCSRA |= (1<<ADIE);
  // Setter prescale til 16, som resulterer i en 1 MHz clock.
  ADCSRA |= ((1<<ADPS2)|(0<<ADPS1)|(0<<ADPS0));

  // EAIN1 er sat til det negative input.
  // ADCSRB |= ((0<<ACME)|(0<<MUX2)|(1<<MUX1)|(0<<MUX0));
  // Vælger hvilken chanel der bruges.
  if(chanel > 7)
    ADCSRB |= (1<<MUX5);
  // Vælger trigger source. Her bruges Timer1 Overflow.
  //ADCSRB |= ((1<<ADTS2)|(1<<ADTS1)|(0<<ADTS0));
  // Bestemmer referencesepunktet. 
  ADMUX |= ((0<<REFS1)|(1<<REFS0)); // 5V
  // Højre- eller venstre justeret sample. (0 for højre, 1 for venstre)
  ADMUX |= (1<<ADLAR);
  // Vælger hvilken chanel der skal bruges.
  if(chanel < 8)
    ADMUX |= chanel;
  if(chanel > 7)
    ADMUX |= (chanel-7);
}

// Serviceroutine for ADC sample ready.
ISR(ADC_vect){
  
  buffer[ADC_count] = ADCH;
  ADC_count++;

  if(ADC_count == 1 && !(PINB&(1<<PB7)))
    ADC_count = 0;

  if(ADC_count == 64)
  {
    ADC_count = 0;
    done_flag = 1;
    run_flag = 0;
  }

}