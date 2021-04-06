#include "interrupt.h"
#include "led.h"

#define SW2_MASK_BIT 0x01
#define SW3_MASK_BIT 0x02
#define ALL_LED      0x3ff

/*************************************************/
/*  ��Ʈ J�� ���ͷ�Ʈ�� ����ϵ��� �����Ѵ�.   */
/*************************************************/
void ini_interrupt(void){
    Pim.ddrj.byte = 0b00000000;   // ���ͷ�Ʈ ��Ʈ�� ���� ���� 
    Pim.piej.byte = 0xff;		    // ���ͷ�Ʈ ��Ʈ�� ���ͷ�Ʈ enable
    Pim.ppsj.byte = 0x00;		    // ���ͷ�Ʈ ��Ʈ�� ���� ���� (0x00: �ϰ�����, 0xff: ��¿���)  
}


/***********************************/
/*  SW2�� ������ Bar LED ��ü ����  */
/*  SW3�� ������ Bar LED ��ü �ҵ�  */
/***********************************/

void interruptJ_function(void)
{
    if(Pim.pifj.byte & SW2_MASK_BIT)      // SW2�� ���ͷ�Ʈ �߻� 
    {    
        //Regs.portb.byte = ~0b11111111;    // LED ����
        set_led(~ALL_LED);
        Pim.pifj.byte |= SW2_MASK_BIT;    // ���ͷ�Ʈ �÷��� �ʱ�ȭ 
    }
    else if(Pim.pifj.byte & SW3_MASK_BIT)  // SW3�� ���ͷ�Ʈ �߻�
    {  
        //Regs.portb.byte = ~0b00000000;   // LED �ҵ�
        set_led(ALL_LED);
        Pim.pifj.byte |= SW3_MASK_BIT;   // ���ͷ�Ʈ �÷��� �ʱ�ȭ 
    }
}
