#ifndef RTI_H        /*prevent duplicated includes*/
#define RTI_H

/*Includes*/
#include "projectglobals.h"
#include "seven_seg.h"

/*Macros*/
#define DEFAULT_TIME_OUT    0x17
#define ONE_SEC             2000

void init_rti(int s);
void rti_handler(void);
void rti_service(void);

#endif /*RTI_H*/
