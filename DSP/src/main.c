#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
//#include <math.h>
#include <complex.h>

enum state {init, idle, DSP, recalibrate, display_update} state;
volatile static char done_flag, display_flag, BTN_flag;
volatile static long FIR_coef[0	0.0005225556	0	-0.009390916	0.03975988	-0.09536017	0.1588891	0.785726	0.1837596	-0.128544	0.06357345	-0.01842972	0	0.002403348	-0.0007247252]; // 11
volatile static long buffer[64], phase, amp;
double complex z = 0;

void init_display()
{

}

void init_PWM()
{
  
}

void init_ADC()
{

}

void init_BTN()
{
  
}

void DFT(buffer)
{
  z = 0;

  for(int i=0; i=!60 ;i+=5)
    z += buffer[i] + I*buffer[i+1] - buffer[i+2] - I*buffer[i+3] + buffer[i+4];
  z += buffer[60] + I*buffer[60+1] - buffer[60+2] - I*buffer[60+3];

  amp = 0.8*amp + 0.2*sqrt(creal(z)*creal(z) + cimag(z)*cimag(z));
  phase = 0.8*phase + 0.2*carg(z);
}

int main(void)
{
  switch (state)
  {
  case init:


    state = idle;
    break;
  
  case idle:
    if(display_flag)
    {
      state = display_update;
      display_flag = 0;
    }
    
    else if(BTN_flag)
    {
      state = recalibrate;
      BTN_flag = 0;
    }

    else if(done_flag)
    {
      state = DSP;
      done_flag = 0;
    }
    break;

  case DSP:
    DFT(buffer);

    state = idle;
    break;

  case recalibrate:
    /* code */

    state = idle;
    break;

  case display_update:
    /* code */

    state = idle;
    break;
  
  default:
    break;
  }

  return 0;
}