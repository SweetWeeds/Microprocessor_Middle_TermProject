#include "interrupt.h"
#include "led.h"

#define SW2_MASK_BIT 0x01
#define SW3_MASK_BIT 0x02
#define ALL_LED      0x3ff

/*************************************************/
/*  포트 J를 인터럽트로 사용하도록 설정한다.   */
/*************************************************/
void ini_interrupt(void){
    Pim.ddrj.byte = 0b00000000;   // 인터럽트 포트의 방향 결정 
    Pim.piej.byte = 0xff;		    // 인터럽트 포트의 인터럽트 enable
    Pim.ppsj.byte = 0x00;		    // 인터럽트 포트의 엣지 설정 (0x00: 하강엣지, 0xff: 상승엣지)  
}


/***********************************/
/*  SW2를 누르면 Bar LED 전체 점등  */
/*  SW3를 누르면 Bar LED 전체 소등  */
/***********************************/

void interruptJ_function(void)
{
    if(Pim.pifj.byte & SW2_MASK_BIT)      // SW2의 인터럽트 발생 
    {    
        //Regs.portb.byte = ~0b11111111;    // LED 점등
        set_led(~ALL_LED);
        Pim.pifj.byte |= SW2_MASK_BIT;    // 인터럽트 플래그 초기화 
    }
    else if(Pim.pifj.byte & SW3_MASK_BIT)  // SW3의 인터럽트 발생
    {  
        //Regs.portb.byte = ~0b00000000;   // LED 소등
        set_led(ALL_LED);
        Pim.pifj.byte |= SW3_MASK_BIT;   // 인터럽트 플래그 초기화 
    }
}
