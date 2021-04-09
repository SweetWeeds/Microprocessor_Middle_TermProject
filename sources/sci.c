
//#include "main.h"
#include "sci.h"
#include "queue.h"


unsigned char *txbuffer_sci0; //text�� �����ϴ� �����̴�. 
int txoffset_sci0;            //text���ڿ� ���̸� �˱����� �ʿ��� �����̴�.
unsigned char *rxbuffer_sci0; //rx�� �����ϴ� �����̴�.
unsigned int rxoffset_sci0 = 0;

//extern Node* Head;
//extern Node* Tail;

/*********************************************************/
/*  �ø��� ��� 0�� ä���� �ʱ�ȭ �Ѵ�.				       */
/*********************************************************/ 
void init_sci0(int baud_rate, unsigned char *rxbuf) 
{
    /*sci�� �ʱ�ȭ �ϴ� �Լ��̴�. bps�� ���ڿ��� ���� �׸��� �ۼ��� interrupt�� ������� ���� �����Ѵ�.*/
    unsigned long oscclk, modclk;  //SCIBD register�� SBR�� �����ϱ� ���� ����
    unsigned short br;    //�츮 ����� �ϴ� bps�� �����ϴ� ����
    oscclk = 16000000;	  //MCU�� ���ļ��� 16 MHz�̴�.
    modclk = 8000000;	  //Set SCI module clock = (Oscillator Freq.)/2
    br = 26;    //Set BR, SCI baud rate = (SCI module clock)/(16*BR)
    /*���� �ĵ��� �츮�� ����ϴ� MCU�� ������ ���� �������� ���̴�. */

    Sci0.scibd.word = br;  //������ BR ���� SCIBD register�� ����
    Sci0.scicr1.byte = SCICR1_INIT_DEFAULT;  //SCI ���� ���� register �ʱ�ȭ. Normal operation & 8 data bit format & Parity disabled
    Sci0.scicr2.byte = SCICR2_INIT_DEFAULT;  //SCI ���� ���� register �ʱ�ȭ. transmit & receive & receive interrupt Ȱ��ȭ 
    /* ���⼭ transmit interrpt�� ���� �� interrupt�� �߻���Ű�� ������ �ʱ�ȭ �� �� �ʿ����. */ 
    txoffset_sci0 = 0;
    rxbuffer_sci0 = rxbuf;
    /*������ offset�� buffer�� �ʱ�ȭ �Ѵ�.*/     
}


/*********************************************************/
/*  �Է¹��� ���ڿ��� �ø��� ������� �����Ѵ�.                          */
/*  �Է¹��� ���ڿ��� ���̸� ���ۿ� �����ϰ� �۽� interrupt�� enable����     */
/*  MCU�� interrupt handler�� �����ϵ��� �Ѵ�.                   */
/*********************************************************/ 
void write_sci0(unsigned char *text)
{
    /*�� �Լ��� �Է¹��� ���ڿ��� ��ǻ�Ϳ� ������ ������ �ϴ� �Լ��̴�. transmit interrupt�� �߻����� sci interrupt handler�Լ��� ȣ���ϰ� �ȴ�*/

	txbuffer_sci0 = text;
    /*���ڿ� ���̸� offset�� ���� ��Ų��.*/
	Sci0.scicr2.byte |= (TIE_ENABLE | TE_ENABLE);         //TIE & TE Ȱ��ȭ
}


/*****************************************************************/
//  �ø��� ��� �۽� �� ���� ���ͷ�Ʈ�� �߻����� �� ó���Ǵ� �Լ�.                      
//  �� ����Ʈ�� ���ڰ� �۽� �� ���� �� ������ ���ͷ�Ʈ�� �߻���                        
//  sci�� interrupt TDRE�� RDRF�� �߻����� �� ȣ��Ǵ� �Լ��̴�. ���� ���� �� �Լ��� projectvectors.c�� ����� �Ǿ� �־�� �Ѵ�. ���������� ��Ʈ ���Ͽ� ���� ��/���� ���°� �����ȴ�.
/*****************************************************************/ 
void sci0_handler(void)
{
    unsigned int cnt;
    DataFrame* df = NULL;

    if(Sci0.scisr1.bit.rdrf == 1)   //���� �����̸� RDRF�� �ݵ�� 1�� �Ǿ��ִ�.
    {
        *rxbuffer_sci0 = Sci0.scidrl.byte;  // scidrl�� ����� 1bit ���� �����͸� ���� ���ۿ� ����
        if ((*rxbuffer_sci0) == '>') {
            *(rxbuffer_sci0 + 1) = 0;
            rxbuffer_sci0 -= rxoffset_sci0;
            rxoffset_sci0 = 0;
            df = GetDataFrame(rxbuffer_sci0);
            if (df) QueuePush(df);
        }
        else {
            rxoffset_sci0++;
            rxbuffer_sci0++;
        }
    }
    else if (Sci0.scisr1.bit.tdre == 1)  
    /*���� ���°� �ƴ� �۽� �����̸� TDRE�� 1�̵ǰ� ���� ���� status�� ���� �ָ� �ȴ�. */
    {
        Sci0.scidrl.byte = *txbuffer_sci0;    // scidrl�� �۽��� ������ ����
        txbuffer_sci0++;

        if((*txbuffer_sci0) == '\0') {
            Sci0.scicr2.bit.tie = 0;        // Transmitter Interrupt Enable Bit�� Ŭ����
        }
    }
}