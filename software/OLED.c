/*---------------------------------------------------------
Purpose:  Dette modul initialiserer et OLED display.
Input: Ingen input
Output: Ingen output
Uses: "ssd1306.h", "I2C.h", "OLED.h"
Author: Buster Bøgild Nielsen & Thomas Ring
Version: 1
Date and year: 6/5 2022
-----------------------------------------------------*/
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#define F_CPU 16000000UL
#include "I2C.h"
#include "ssd1306.h"
#include "OLED.h"


// Funktionen initialiserer OLED displayet.
void init_OLED(){
  _i2c_address = 0X78;
  I2C_Init();
  InitializeDisplay();
  print_fonts();
  clear_display();
}