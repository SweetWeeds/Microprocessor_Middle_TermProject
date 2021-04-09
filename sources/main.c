#include "main.h"

DataFrame* df;
unsigned char RX[35];
unsigned int led_digit = 0;
extern const u8 BYTE_SIZE_TYPE[6];

void LED_CONTROL(DataFrame* df) {
    unsigned int idx;
    switch (df->cmdnum) {
    case CMD_LED_CTRL_ON_SEL:
        led_digit = led_digit | (0b1 << atoi(df->data));
        break;
    case CMD_LED_CTRL_DEC:
        sscanf(df->data, "%d", &led_digit);
        break;
    case CMD_LED_CTRL_HEX:
        sscanf(df->data, "%x", &led_digit);
        break;
    case CMD_LED_CTRL_BIN:
        for (idx = 0; idx < BYTE_SIZE_TYPE[df->dataformat]; idx++) {
            led_digit = (led_digit | (*(df->data + idx) - '0' ? 0b1 : 0b0)) << 1;
        }
        break;
    case CMD_LED_CTRL_OFF_SEL:
        led_digit = led_digit & ~(0b1 << (*(df->data) - '0') );
        break;
    }
    set_led(led_digit);
}

void LCD_CONTROL(DataFrame* df) {
    // Low ����
    if (df->cmdnum == 0) {
        write_string(0x00, df->data);
    }
    // High ����
    else if (df->cmdnum == 1) {
        write_string(0x40, df->data);
    }
}

void main ()
{
    // ���ͷ�Ʈ �ʱ�ȭ
    int_disable();
    ini_interrupt();
    int_enable();
    xint_enable();

    // �ø��� �ʱ�ȭ
    init_sci0(19200, RX);
    write_sci0("SCI OK");

    // LED �ʱ�ȭ
    init_led();

    // ���� ���׸�Ʈ �ʱ�ȭ
    init_seven_seg();

    // LCD �ʱ�ȭ
    init_LCD();
    //write_string(0x00, "Init Complete");

    // DataFrame ���̺� �ʱ�ȭ
    InitFormatTable();

	//Insert Application Software Here.
	for (;;) {
        // ť���� ������ �о����
        df = QueuePop();
        // �� ������ üũ
        if (df) {
            //set_inst_register(CODE_CLR_DISP);
            // ��ɾ� ó��
            switch (df->groupnum) {
            case GROUP_LED:
                LED_CONTROL(df);
                break;
            case GROUP_LCD:
                LCD_CONTROL(df);
                break;
            }
            free(df);
            df = NULL;
        }
    }
}