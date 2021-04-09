/* dataframe.c */

#include "dataframe.h"

char VALID_TABLE[6][2][5];	// VALID_TABLE[GROUP_NUM][CMD_CLASS][CMD_NUM] = DATA_FORMAT
const u8 BYTE_SIZE_TYPE[6] = { 1, 2, 3, 4, 10, 16 };    // Byte Format 값 당 Byte size

// 커맨드 테이블 초기화
void InitFormatTable() {
	memset(VALID_TABLE, -1, sizeof(VALID_TABLE));
	// LED
	VALID_TABLE[GROUP_LED][CMD_CLASS_CONTROL][CMD_LED_CTRL_ON_SEL]  = D1;
	VALID_TABLE[GROUP_LED][CMD_CLASS_CONTROL][CMD_LED_CTRL_DEC]     = D4;
	VALID_TABLE[GROUP_LED][CMD_CLASS_CONTROL][CMD_LED_CTRL_HEX]     = D3;
	VALID_TABLE[GROUP_LED][CMD_CLASS_CONTROL][CMD_LED_CTRL_BIN]     = D10;
	VALID_TABLE[GROUP_LED][CMD_CLASS_CONTROL][CMD_LED_CTRL_OFF_SEL] = D1;
	// SEVEN_SEG
	VALID_TABLE[GROUP_SEG][CMD_CLASS_UPDATE][CMD_SEG_UPDATE_LED_CNT] = D1;
	// SWITCH
	VALID_TABLE[GROUP_SWITCH][CMD_CLASS_UPDATE][CMD_SWITCH_UPDATE_STAT] = D1;
	// LCD
	VALID_TABLE[GROUP_LCD][CMD_CLASS_CONTROL][CMD_LCD_CTRL_LOW]  = D16;
	VALID_TABLE[GROUP_LCD][CMD_CLASS_CONTROL][CMD_LCD_CTRL_HIGH] = D16;
	// ADC
	VALID_TABLE[GROUP_ADC][CMD_CLASS_UPDATE][CMD_ADC_UPDATE] = D1;
	// SYS
	VALID_TABLE[GROUP_SYS][CMD_CLASS_UPDATE][CMD_SYS_UPDATE] = D1;
}

ErrorCode DataCheck(u8* buf, u8 byte_size) {
	u32 byte_size_cnt = 0;
	while (buf[byte_size_cnt] != ' ' && byte_size_cnt < MAX_DATA_SIZE + 5) {
		byte_size_cnt++;
	}
	// '>' 제거
	if (buf[byte_size_cnt] == ' ')
		buf[byte_size_cnt] = 0;
	/* Exception */
	// Timeout
	if (MAX_DATA_SIZE + 5 <= byte_size_cnt) {
		return Timeout;
	}
	// OverDataSize
	else if (byte_size < byte_size_cnt) {
		return OverDataSize;
	}
	// LossDataSize
	else if (byte_size > byte_size_cnt) {
		return LossDataSize;
	}
	return Normal;
}

// 파싱
DataFrame* GetDataFrame(const u8 *buf) {
	ErrorCode ec;
	// ascii 임시 저장
	u8 tmp[16] = { 0, };

	// 동적할당
	DataFrame* df = (DataFrame*)malloc(sizeof(DataFrame));

	sscanf(buf, "<%2d%1d%2d%1d%[^>]s", &df->groupnum, &df->cmdclass, &df->cmdnum, &df->dataformat, df->data);

	// 예외 처리: OverGroupCnt (전송된 명령의 Group 번호가 범위를 벗어남)
	if (df->groupnum > 5) {
		ExceptionHandling(OverGroupCnt);
		free(df);
		return NULL;
	}
	// 예외 처리: OverClassCnt (전송된 명령의 Class 번호가 범위를 벗어남)
	if (VALID_TABLE[df->groupnum][df->cmdclass][df->cmdnum] == -1) {
		ExceptionHandling(OverClassCnt);
		free(df);
		return NULL;
	}
	// 예외 처리: OverFormatCnt (전송된 명령의 Format 번호가 범위를 벗어남)
	if (VALID_TABLE[df->groupnum][df->cmdclass][df->cmdnum] != df->dataformat) {
		ExceptionHandling(OverFormatCnt);
		free(df);
		return NULL;
	}
	// 예외 처리: Data 크기 검증
	ec = DataCheck(df->data, BYTE_SIZE_TYPE[df->dataformat]);
	if (ec != Normal) {
		ExceptionHandling(ec);
		free(df);
		return NULL;
	}
	return df;
}

/* dataframe.c */
