#ifndef ATD_H        /*prevent duplicated includes*/
#define ATD_H

/*Includes*/
#include "projectglobals.h"

void init_atd0(void);
int get_atd0(int channel);

#define ANALOG_INPUT_CHANNEL 0
#define ATDCTL2_INIT 0x80
#define ATDCTL3_INIT 0x20
#define ATDCTL4_INIT 0x6d
#define ATDCTL5_INIT 0xa0
#define SCF_SET      0x80

#endif /*SCI_H*/
