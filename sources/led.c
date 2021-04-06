#include "led.h"

/*******************************************************
 *  BAR-LED�� ���Ǵ� ��Ʈ�� �ʱ�ȭ �Ѵ�.               *
 *******************************************************/

void init_led(void) {
    // ��Ʈ B�� ��Ʈ M �� ������� ����
    Regs.ddrb.byte = DDRB_LED_MASK_BIT;
    Pim.ddrm.byte = DDRM_LED_MASK_BIT;
  
    // ��Ʈ B�� ��Ʈ M �� ����� ��� LED�� ��
    Regs.portb.byte = DDRB_LED_MASK_BIT;
    Pim.ptm.byte = DDRM_LED_MASK_BIT;
}

/*******************************************************
 *  10��Ʈ�� ���ڸ� �Է��ϸ� �� ���� BAR-LED�� ����Ѵ�.  *
 *  0b11110000 = OFF OFF OFF OFF ON ON ON ON           *
 *******************************************************/
void set_led(unsigned int digit) {
    unsigned char upper_digit, lower_digit;
    digit = ~digit;
    
    upper_digit = (digit & UPPER_TWO_BIT) >> 2; // 10 ��Ʈ �߿��� ���� 2 ��Ʈ�� ���� ����, 6,7��Ʈ ��ġ�� �̵�

    lower_digit = digit & LOWER_EIGHT_BIT;      // 10 ��Ʈ �߿��� ���� 8 ��Ʈ�� ���� ����

    Pim.ptm.byte = upper_digit;     // ���� 2��Ʈ�� ���� ��Ʈ M�� ���
    Regs.portb.byte = lower_digit;  // ���� 8��Ʈ�� ���� ��Ʈ B�� ���
}

void set_led_counter(unsigned int cnt) {
    unsigned int digit = 0;
    unsigned int i = 0;

    for (i = 0; i < cnt; i++) {
        digit = digit | (0x01 << i);
    }

    set_led(digit);
}