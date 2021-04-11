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

unsigned char convert_value(int cnt)
{
    // VR_FOUR�� �������� ����
    if (cnt < VR_FOUR) {
        // ��� : 0
        if (cnt < VR_ZERO) {
            return 0;
        }
        // ��� : 1
        else if (cnt < VR_ONE) {
            return 1;
        }
        // ��� : 2
        else if (cnt < VR_TWO) {
            return 2;
        }
        // ��� : 3
        else if (cnt < VR_THREE) {
            return 3;
        }
        // ��� : 4
        else {
            return 4;
        }
    // 551���� ū ���
    } else {
        // ��� : 5
        if (cnt < VR_FIVE) {
            return 5;
        }
        // ��� : 6
        else if (cnt < VR_SIX) {
            return 6;
        }
        // ��� : 7
        else if (cnt < VR_SEVEN) {
            return 7;
        }
        // ��� : 8
        else if (cnt < VR_EIGHT) {
            return 8;
        }
        // ��� : 9
        else {
            return 9;
        }
    }
    return 0;   // ���� ó��
}
