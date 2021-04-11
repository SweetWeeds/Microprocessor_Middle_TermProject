#include "interrupt.h"

extern unsigned int led_digit;
unsigned char buf[27];

/*************************************************/
/*  포트 J를 인터럽트로 사용하도록 설정한다.   */
/*************************************************/
void ini_interrupt(void){
    Pim.ddrj.byte = 0b00000000;   // 인터럽트 포트의 방향 결정 
    Pim.piej.byte = 0xff;		    // 인터럽트 포트의 인터럽트 enable
    Pim.ppsj.byte = 0x00;		    // 인터럽트 포트의 엣지 설정 (0x00: 하강엣지, 0xff: 상승엣지)  
}


/***********************************
 *  SW2를 누르면 Bar LED 전체 점등  *
 *  SW3를 누르면 Bar LED 전체 소등  *
 ***********************************/

void interruptJ_function(void)
{
    unsigned char atd_value;
    if(Pim.pifj.byte & SW2_MASK_BIT)      // SW2의 인터럽트 발생 (GUI 카운터 상승)
    { 
        write_sci0("<0210001>");
        Pim.pifj.byte |= SW2_MASK_BIT;    // 인터럽트 플래그 초기화 
    }
    else if(Pim.pifj.byte & SW3_MASK_BIT)  // SW3의 인터럽트 발생 (ADC 값 전송)
    {
        atd_value = convert_value(get_atd0(ANALOG_INPUT_CHANNEL));  // 아날로그 값 -> 0 ~ 9
        sprintf(buf, "<041000%d>", atd_value);
        write_sci0(buf);
        Pim.pifj.byte |= SW3_MASK_BIT;   // 인터럽트 플래그 초기화 
    }
}

/***********************************
 *  SW1을 누르면 LED 개수 전송      *
 ***********************************/
void interruptX_function (void)    //XIRQ interrupt 서비스 함수 (SW1의 인터럽트 발생)
{
    unsigned int cnt = 0;
    unsigned int i;
    for (i = 0; i < 10; i++) {
        if (led_digit & (0b1 << i))
            cnt++;
    }
    if (cnt < 10) {
        set_7segment(cnt);
        sprintf(buf, "<011000%d>", cnt);
        write_sci0(buf);
    }
    else {
        set_7segment(cnt);
        sprintf(buf, "<011000X>");
        write_sci0(buf);
    }
}