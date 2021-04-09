#ifndef MAIN_H        /*prevent duplicated includes*/
#define MAIN_H

#include "projectglobals.h"
#include "queue.h"
#include "dataframe.h"
#include "stdio.h"
#include "lcd.h"
#include "led.h"
#include "seven_seg.h"
#include "interrupt.h"
#include "sci.h"

void LED_CONTROL(DataFrame* df);
void LCD_CONTROL(DataFrame* df);

#endif /*MAIN_H*/