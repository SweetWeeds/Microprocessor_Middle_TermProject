/* dataframe.c */

#include "dataframe.h"

char BYTE_SIZE_TABLE[6][2][5];	// BYTE_SIZE_TABLE[GROUP_NUM][CMD_CLASS][CMD_NUM] = DATA_FORMAT
const u8 BYTE_SIZE_TYPE[6] = { 1, 2, 3, 4, 10, 16 };    // Byte Format 값 당 Byte size

// 커맨드 테이블 초기화
void InitFormatTable() {
    unsigned int i, j, k;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 5; k++) {
                BYTE_SIZE_TABLE[i][j][k] = -1;
            }
        }
    }
	// LED
	BYTE_SIZE_TABLE[GROUP_LED][CMD_CLASS_CONTROL][CMD_LED_CTRL_ON_SEL]  = D1;
	BYTE_SIZE_TABLE[GROUP_LED][CMD_CLASS_CONTROL][CMD_LED_CTRL_DEC]     = D4;
	BYTE_SIZE_TABLE[GROUP_LED][CMD_CLASS_CONTROL][CMD_LED_CTRL_HEX]     = D3;
	BYTE_SIZE_TABLE[GROUP_LED][CMD_CLASS_CONTROL][CMD_LED_CTRL_BIN]     = D10;
	BYTE_SIZE_TABLE[GROUP_LED][CMD_CLASS_CONTROL][CMD_LED_CTRL_OFF_SEL] = D1;
	// SEVEN_SEG
	BYTE_SIZE_TABLE[GROUP_SEG][CMD_CLASS_UPDATE][CMD_SEG_UPDATE_LED_CNT] = D1;
	// SWITCH
	BYTE_SIZE_TABLE[GROUP_SWITCH][CMD_CLASS_UPDATE][CMD_SWITCH_UPDATE_STAT] = D1;
	// LCD
	BYTE_SIZE_TABLE[GROUP_LCD][CMD_CLASS_CONTROL][CMD_LCD_CTRL_LOW]  = D16;
	BYTE_SIZE_TABLE[GROUP_LCD][CMD_CLASS_CONTROL][CMD_LCD_CTRL_HIGH] = D16;
	// ADC
	BYTE_SIZE_TABLE[GROUP_ADC][CMD_CLASS_UPDATE][CMD_ADC_UPDATE] = D1;
	// SYS
	BYTE_SIZE_TABLE[GROUP_SYS][CMD_CLASS_UPDATE][CMD_SYS_UPDATE] = D1;
}

unsigned int DataCheck(u8* buf, u8 byte_size) {
	u32 byte_size_cnt = strlen(buf);
	/* Exception */
	// Timeout
	if (MAX_DATA_SIZE + 5 <= byte_size_cnt) return Timeout;
	// OverDataSize
	else if (byte_size < byte_size_cnt) return OverDataSize;
	// LossDataSize
	else if (byte_size > byte_size_cnt) return LossDataSize;

	return Normal;
}

// 파싱
DataFrame* GetDataFrame(const u8* buf) {
	unsigned int ec;
	// 쓰레기 값 저장
	u8 garbage[MAX_FRAME_SIZE] = { 0, };

	// 동적할당
	DataFrame* df = (DataFrame*)malloc(sizeof(DataFrame));

    sscanf(buf, "%[^<]s", garbage); // 앞부분의 쓰레기 값 제거
	sscanf(buf + strlen(garbage) + 1, "%2d%1d%2d%1d%[^>]s", &df->groupnum, &df->cmdclass, &df->cmdnum, &df->dataformat, df->data);

	// 예외 처리: OverGroupCnt (전송된 명령의 Group 번호가 범위를 벗어남)
	if (df->groupnum > 5) {
		ExceptionHandling(OverGroupCnt);
		free(df);
		return NULL;
	}

	// 예외 처리: OverClassCnt (전송된 명령의 Class 번호가 범위를 벗어남)
	if (df->cmdclass != CMD_CLASS_CONTROL) {
		ExceptionHandling(OverClassCnt);
		free(df);
		return NULL;
    }
    
    if (BYTE_SIZE_TABLE[df->groupnum][df->cmdclass][df->cmdnum] == -1) {
        // 예외 처리: CantFindCmd_LED (전송된 명령어를 LED 그룹을 찾을 수 없다)
        if (df->groupnum == GROUP_LED) {
            ExceptionHandling(CantFindCmd_LED);
        }
        // 예외 처리: CantFindCmd_LCD (전송된 명령어를 LCD 그룹을 찾을 수 없다)
        else if (df->groupnum == GROUP_LCD) {
            ExceptionHandling(CantFindCmd_LCD);
        }
        free(df);
        return NULL;
	}

	// 예외 처리: OverFormatCnt (전송된 명령의 Format 번호가 범위를 벗어남)
	if (BYTE_SIZE_TABLE[df->groupnum][df->cmdclass][df->cmdnum] != df->dataformat) {
		ExceptionHandling(OverFormatCnt);
		free(df);
		return NULL;
	}

    // 예외 처리: Data 크기 검증 (Timeout, OverDataSize, LossDataSize)
	ec = DataCheck(df->data, BYTE_SIZE_TYPE[df->dataformat]);
	if (ec != Normal) {
		ExceptionHandling(ec);
		free(df);
		return NULL;
	}
	return df;
}

/* dataframe.c */
