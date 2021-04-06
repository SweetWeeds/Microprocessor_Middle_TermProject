#include "seven_seg.h"

S_SEG_PIN seven_seg_pin = SEG_A;

/*******************************************************
 *  7-Segment에 사용되는 포트를 초기화 한다.             *
 *******************************************************/
void init_seven_seg(void)
{
  // 포트 H를 출력 설정
  Pim.ddrh.byte = 0xff;

  // 포트 H 0번 핀(A 세그먼트) ON
  Pim.pth.byte = seven_seg_pin;
}

/*******************************************************
 *  7-Segment의 특정 세그먼트를 켠다.                    *
 *******************************************************/
void set_seven_seg(S_SEG_PIN sp)
{
  Pim.pth.byte = sp;
}

/*******************************************************
 *  7-Segment의 LED를 시계방향 혹은 반시계 방향으로 회전. *
 *******************************************************/
void rotate_seg(DIRECTION dir) {
  if (dir == CLOCK_WISE) {
    seven_seg_pin <<= 1;
    if (seven_seg_pin > SEG_F) {
      seven_seg_pin = SEG_A;
    }
    set_seven_seg(seven_seg_pin);
  }
  else if (dir == COUNTER_CLOCK_WISE) {
    seven_seg_pin >>= 1;
    if (seven_seg_pin < SEG_A) {
      seven_seg_pin = SEG_F;
    }
    set_seven_seg(seven_seg_pin);
  }
}