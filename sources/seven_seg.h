#ifndef SEVEN_SEG_H        /*prevent duplicated includes*/
#define SEVEN_SEG_H

/* Includes */
#include "projectglobals.h"

/* Macros */
#define SEVEN_SEGMENT_A   0x01
#define SEVEN_SEGMENT_B   0x02
#define SEVEN_SEGMENT_C   0x04
#define SEVEN_SEGMENT_D   0x08
#define SEVEN_SEGMENT_E   0x10
#define SEVEN_SEGMENT_F   0x20
#define SEVEN_SEGMENT_G   0x40
#define SEVEN_SEGMENT_DP  0x80

typedef enum {
    SEG_A = SEVEN_SEGMENT_A,
    SEG_B = SEVEN_SEGMENT_B,
    SEG_C = SEVEN_SEGMENT_C,
    SEG_D = SEVEN_SEGMENT_D,
    SEG_E = SEVEN_SEGMENT_E,
    SEG_F = SEVEN_SEGMENT_F
} S_SEG_PIN;

typedef enum {
    CLOCK_WISE = 0,
    COUNTER_CLOCK_WISE = 1
} DIRECTION;

void init_seven_seg(void);
void set_seven_seg(S_SEG_PIN sp);
void rotate_seg(DIRECTION dir);

#endif /* SEVEN_SEG */