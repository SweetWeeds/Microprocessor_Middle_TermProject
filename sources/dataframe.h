/* dataframe.h */

#ifndef DATAFRAME_H
#define DATAFRAME_H

#include "string.h"
#include "stdlib.h"

#define MAX_FRAME_SIZE  24	// 최대 데이터 프레임 크기: 24바이트
#define MAX_DATA_SIZE   17

#define GROUP_LED	  0x00
#define GROUP_SEG     0x01
#define GROUP_SWITCH  0x02
#define GROUP_LCD     0x03
#define GROUP_ADC     0x04
#define GROUP_SYS     0x05

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
u32 GetBytes(const u8* buf, u8 byte_size, u8 data[]);
DataFrame* GetDF(const u8 *buf);
/* Function Prototypes */

#endif /* DATAFRAME_H */

/* dataframe.h */