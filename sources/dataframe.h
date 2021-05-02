/* dataframe.h */

#ifndef DATAFRAME_H
#define DATAFRAME_H

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "exception.h"

#define MAX_FRAME_SIZE  24	// �ִ� ������ ������ ũ��: 24����Ʈ
#define TIMEOUT_SIZE    MAX_FRAME_SIZE + 5  // Timtout ���� : �ִ� ������ ������ ũ�� + 5 �̻�
#define MAX_DATA_SIZE   16	// �ִ� ������ ũ��

// Data ũ��
#define D1  0
#define D2  1
#define D3  2
#define D4  3
#define D10 4
#define D16 5

// Group No
#define GROUP_LED	  0x00
#define GROUP_SEG     0x01
#define GROUP_SWITCH  0x02
#define GROUP_LCD     0x03
#define GROUP_ADC     0x04
#define GROUP_SYS     0x05

// CMD Class
#define CMD_CLASS_CONTROL 0x00  // PC -> MCU
#define CMD_CLASS_UPDATE  0x01  // MCU -> PC

// CMD Num
#define CMD_LED_CTRL_ON_SEL  0	// LED ���� ���� (ON)
#define CMD_LED_CTRL_DEC     1  // LED ���� (10����)
#define CMD_LED_CTRL_HEX     2  // LED ���� (16����)
#define CMD_LED_CTRL_BIN     3  // LED ���� (2����)
#define CMD_LED_CTRL_OFF_SEL 4  // LED ���� ���� (OFF)
#define CMD_SEG_UPDATE_LED_CNT 0  // ���� ON�� LED�� ���� ǥ��
#define CMD_SWITCH_UPDATE_STAT 0  // ����ġ2�� ���� ����
#define CMD_LCD_CTRL_LOW   0    // LCD�� Low ���� �Է� ��
#define CMD_LCD_CTRL_HIGH  1    // LCD�� High ���� �Է� ��
#define CMD_ADC_UPDATE     0    // ���� ADC ��
#define CMD_SYS_UPDATE     0    // Error Code

#define ETX_VALID_BIT 0x00

// Data Format
#define BYTE_FORMAT_D1    0
#define BYTE_FORMAT_D2    1
#define BYTE_FORMAT_D3    2
#define BYTE_FORMAT_D4    3
#define BYTE_FORMAT_D10   4
#define BYTE_FORMAT_D16   5

typedef unsigned char  u8;		// 1 Byte
typedef unsigned short u16;		// 2 Byte
typedef unsigned int   u32;		// 4 Byte

// ������ ������
typedef struct {
	u16 groupnum;
	u16 cmdclass;
	u16 cmdnum;
	u16 dataformat;
	u8 data[MAX_DATA_SIZE + 6];
} DataFrame;

/* Function Prototypes */
void InitFormatTable();
DataFrame* GetDataFrame(const u8*);
unsigned int DataCheck(u8*, u8);
/* Function Prototypes */

#endif /* DATAFRAME_H */

/* dataframe.h */
