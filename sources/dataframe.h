/* dataframe.h */

#ifndef DATAFRAME_H
#define DATAFRAME_H

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "exception.h"

#define MAX_FRAME_SIZE  24	// 최대 데이터 프레임 크기: 24바이트
#define MAX_DATA_SIZE   17	// 최대 데이터 크기

#define D1  0
#define D2  1
#define D3  2
#define D4  3
#define D10 4
#define D16 5

#define GROUP_LED	  0x00
#define GROUP_SEG     0x01
#define GROUP_SWITCH  0x02
#define GROUP_LCD     0x03
#define GROUP_ADC     0x04
#define GROUP_SYS     0x05

#define CMD_CLASS_CONTROL 0x00  // PC -> MCU
#define CMD_CLASS_UPDATE  0x01  // MCU -> PC

#define CMD_LED_CTRL_ON_SEL  0	// LED 개별 제어 (ON)
#define CMD_LED_CTRL_DEC     1  // LED 제어 (10진수)
#define CMD_LED_CTRL_HEX     2  // LED 제어 (16진수)
#define CMD_LED_CTRL_BIN     3  // LED 제어 (2진수)
#define CMD_LED_CTRL_OFF_SEL 4  // LED 개별 제어 (OFF)
#define CMD_SEG_UPDATE_LED_CNT 0  // 현재 ON된 LED의 개수 표시
#define CMD_SWITCH_UPDATE_STAT 0  // 스위치2의 상태 정보
#define CMD_LCD_CTRL_LOW   0    // LCD의 Low 라인 입력 값
#define CMD_LCD_CTRL_HIGH  1    // LCD의 High 라인 입력 값
#define CMD_ADC_UPDATE     0    // 현재 ADC 값
#define CMD_SYS_UPDATE     0    // Error Code

#define ETX_VALID_BIT 0x00

// Byte 포맷
#define BYTE_FORMAT_D1    0
#define BYTE_FORMAT_D2    1
#define BYTE_FORMAT_D3    2
#define BYTE_FORMAT_D4    3
#define BYTE_FORMAT_D10   4
#define BYTE_FORMAT_D16   5

typedef unsigned char  u8;		// 1 Byte
typedef unsigned short u16;		// 2 Byte
typedef unsigned int   u32;		// 4 Byte

// 데이터 프레임 (파싱 완료)
typedef struct _DataFrame {
	u16 groupnum;
	u8 cmdclass;
	u16 cmdnum;
	u8 dataformat;
	u8 data[MAX_DATA_SIZE];
} DataFrame;

/* Function Prototypes */
u32 GetBytes(u8* buf, u8 byte_size, u8 data[]);
DataFrame* GetDataFrame(const u8 *buf);
/* Function Prototypes */

#endif /* DATAFRAME_H */

/* dataframe.h */
