#include "interrupt.h"

extern unsigned int led_digit;
unsigned char buf[27];

/*************************************************/
/*  ��Ʈ J�� ���ͷ�Ʈ�� ����ϵ��� �����Ѵ�.   */
/*************************************************/
void ini_interrupt(void){
    Pim.ddrj.byte = 0b00000000;   // ���ͷ�Ʈ ��Ʈ�� ���� ���� 
    Pim.piej.byte = 0xff;		    // ���ͷ�Ʈ ��Ʈ�� ���ͷ�Ʈ enable
    Pim.ppsj.byte = 0x00;		    // ���ͷ�Ʈ ��Ʈ�� ���� ���� (0x00: �ϰ�����, 0xff: ��¿���)  
}


/***********************************
 *  SW2�� ������ Bar LED ��ü ����  *
 *  SW3�� ������ Bar LED ��ü �ҵ�  *
 ***********************************/

void interruptJ_function(void)
{
    unsigned char atd_value;
    if(Pim.pifj.byte & SW2_MASK_BIT)      // SW2�� ���ͷ�Ʈ �߻� (GUI ī���� ���)
    { 
        write_sci0("<0210001>");
        Pim.pifj.byte |= SW2_MASK_BIT;    // ���ͷ�Ʈ �÷��� �ʱ�ȭ 
    }
    else if(Pim.pifj.byte & SW3_MASK_BIT)  // SW3�� ���ͷ�Ʈ �߻� (ADC �� ����)
    {
        atd_value = convert_value(get_atd0(ANALOG_INPUT_CHANNEL));  // �Ƴ��α� �� -> 0 ~ 9
        sprintf(buf, "<041000%d>", atd_value);
        write_sci0(buf);
        Pim.pifj.byte |= SW3_MASK_BIT;   // ���ͷ�Ʈ �÷��� �ʱ�ȭ 
    }
}

/***********************************
 *  SW1�� ������ LED ���� ����      *
 ***********************************/
void interruptX_function (void)    //XIRQ interrupt ���� �Լ� (SW1�� ���ͷ�Ʈ �߻�)
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