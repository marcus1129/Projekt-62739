/*---------------------------------------------------------
Purpose: modulet har til formål at oprette alle de globale
variabler.
Input: Ingen Input
Output: Ingen Output
Uses: "includes.h"
Author: buster nielsen (s211548)
Company: DTU
Version: 1
Date and year: 20/1 2023
-----------------------------------------------------*/

#include "includes.h"

char done_flag=0, disp_flag=0, BTN_flag=0, run_flag=1;
int ADC_count=0, disp_count=0, PWM_count=1;
double real=0, imag=0;
int phase=0, amp=0, offset_phase=0, true_phase;
char text[100], item[50];
double buffer[64];
//volatile static double buffer[64]={2.5,539.7848215,2.5,-532.309767,2.5,532.6019336,2.5,-521.1221568,2.5,518.5047223,2.5,-505.4952777,2.5,502.8778432,2.5,-491.3980664,2.5,491.690233,2.5,-484.2151785,2.5,489.2151785,2.5,-486.690233,2.5,496.3980664,2.5,-497.8778432,2.5,510.4952777,2.5,-513.5047223,2.5,526.1221568,2.5,-527.6019336,2.5,537.309767,2.5,-534.7848215,2.5,539.7848215,2.5,-532.309767,2.5,532.6019336,2.5,-521.1221568,2.5,518.5047223,2.5,-505.4952777,2.5,502.8778432,2.5,-491.3980664,2.5,491.690233,2.5,-484.2151785,2.5,489.2151785,2.5,-486.690233};
