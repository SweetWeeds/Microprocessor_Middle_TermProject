#include "atd.h"
/*****************************************************/
/*  ATD ����� �ʱ�ȭ �Ѵ�.                           */
/*****************************************************/

void init_atd0(void) {

    Atd0.atdctl2.byte = ATDCTL2_INIT;   // ADPU: Power Up
    Atd0.atdctl3.byte = ATDCTL3_INIT;   // Conversion Sequence Length = 2, FIFO off, Backgroud Debug freeze: Continue conversion
    Atd0.atdctl4.byte = ATDCTL4_INIT;   // A/D resolution 10bit, Sample time 16 A/D conversion clock period
                                        // Clock prescale value: (divided by 28)
    Atd0.atdctl5.byte = ATDCTL5_INIT;   // Right justification, Unsigned, Continuous Scan, Multi-Channel off, AN0 
}

/******************************************************/
/*  �Է� ���� ä�ο� �ش��ϴ� ATD ��ȯ ���� ��ȯ�Ѵ�.    */
/******************************************************/
int get_atd0(int channel) 
{ 
   
    Atd0.atdctl5.byte |= SCF_SET;            //Write to ATDCTL5 (a new conversion sequence is started)
 
    if (channel >= 0 && channel <= 7) {     // Check channel range
        return (int)(Atd0.atddr[0].d10);      // return ATD result register data
    }
    else return -1;                                  // Invalid channel
}
