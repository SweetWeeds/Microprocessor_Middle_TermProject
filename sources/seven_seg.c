#include "seven_seg.h"

S_SEG_PIN seven_seg_pin = SEG_A;

/*******************************************************
 *  7-Segment�� ���Ǵ� ��Ʈ�� �ʱ�ȭ �Ѵ�.             *
 *******************************************************/
void init_seven_seg(void)
{
  // ��Ʈ H�� ��� ����
  Pim.ddrh.byte = 0xff;

  // ��Ʈ H 0�� ��(A ���׸�Ʈ) ON
  Pim.pth.byte = seven_seg_pin;
}

/*******************************************************
 *  7-Segment�� Ư�� ���׸�Ʈ�� �Ҵ�.                    *
 *******************************************************/
void set_seven_seg(S_SEG_PIN sp)
{
  Pim.pth.byte = sp;
}

/*******************************************************
 *  7-Segment�� LED�� �ð���� Ȥ�� �ݽð� �������� ȸ��. *
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