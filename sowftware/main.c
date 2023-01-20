/*---------------------------------------------------------
Purpose: modulet har til formål at initialisere diverse
harwaremoduler og styre tilstandsmaskinen for en metaldetektor
Input: ADC
Output: PWM, display data
Uses: "OLED.h", "I2C.h", "ssd1306.h", "ADC.h", "BTN.h", 
"timer.h", "includes.h"
Author: buster nielsen (s211548)
Company: DTU
Version: 1
Date and year: 20/1 2023
-----------------------------------------------------*/

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <math.h>
#include "OLED.h"
#include "I2C.h"
#include "ssd1306.h"
#include "ADC.h"
#include "BTN.h"
#include "timer.h"
#include "includes.h"
#include <string.h>
#define PI 3.141592654

enum state {init, idle, DSP, recalibrate, display_update} state;

// I main er tilstandsmaskinen implementeret.
int main(void)
{ 
  while(1)
  {
    switch (state)
    {
      case init:
        sei();
        DDRB |= (1<<PB7);
        PORTB &=~ (1<<PB7);
        init_ADC(0);
        init_OLED();
        init_timer3(249);
        init_BTN_19();
        clear_display();

        state = idle;
        break;
      
      case idle:
        if(disp_flag){
          state = display_update;
          disp_flag = 0;
        } else if(BTN_flag){
            state = recalibrate;
            _delay_ms(200);
            BTN_flag = 0;
          } else if(done_flag){
              state = DSP;
              done_flag = 0;
            }
        break;

      case DSP:
        real = 0;
        imag = 0;
        for(int i=0;i<=60;i+=4)
        {
          real += buffer[i] - buffer[i+2];
          imag += buffer[i+1] - buffer[i+3];
        }

        imag = -imag;
        amp = amp*0.9 + 0.1*(int)sqrt(real*real + imag*imag);
        phase = phase*0.85 + 0.15*(int)((atan2(imag,real)*180.0)/PI);
        run_flag = 1;

        state = idle;
        break;

      case recalibrate:
        offset_phase = phase;
        sprintf(text,"offset: %d deg",offset_phase);
        sendStrXY("offset:          ",3,0);
        sprintf(text,"offset: %d deg",offset_phase);
        sendStrXY(text,3,0);

        state = idle;
        break;

      case display_update:
        true_phase = phase-offset_phase;  
        sendStrXY("amp:           \nphase:         ",0,0);
        sprintf(text,"amp: %d \nphase: %d deg",amp,true_phase);
        sendStrXY(text,0,0);
        disp_count=0;

        state = idle;
        break;
      
      default:
        break;
    }
  }

  return 0;
}
