#include "main.h"

unsigned char RX[35];
extern Node* Head;
extern Node* Tail;

void main ()
{
    // 인터럽트 초기화
    int_disable();
    ini_interrupt();
    int_enable();
    xint_enable();

    // 시리얼 초기화
    init_sci0(19200, RX);
    write_sci0("SCI OK");

    // LED 초기화
    init_led();

    // LCD 초기화
    init_LCD();
    write_string(0x00, "Init Complete");

	//Insert Application Software Here.
	for (;;) {
        // 큐에서 데이터 읽어오기
        DataFrame* df = QueuePop();
        // 널 포인터 체크
        if (df) {
            // 명령어 처리
            switch (df->groupnum) {
            case GROUP_LED:
                write_string(0x00, "GROUP LED");
                break;
            case GROUP_SEG:
                write_string(0x00, "GROUP SEG");
                break;
            case GROUP_SWITCH:
                write_string(0x00, "GROUP SWITCH");
                break;
            case GROUP_LCD:
                write_string(0x00, "GROUP LCD");
                break;
            case GROUP_ADC:
                write_string(0x00, "GROUP ADC");
                break;
            case GROUP_SYS:
                write_string(0x00, "GROUP SYS");
                break;
            }
        }
    }
}