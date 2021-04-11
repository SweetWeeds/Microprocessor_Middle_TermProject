/* dataframe.c */

#include "dataframe.h"

char BYTE_SIZE_TABLE[6][2][5];	// BYTE_SIZE_TABLE[GROUP_NUM][CMD_CLASS][CMD_NUM] = DATA_FORMAT
const u8 BYTE_SIZE_TYPE[6] = { 1, 2, 3, 4, 10, 16 };    // Byte Format �� �� Byte size

// Ŀ�ǵ� ���̺� �ʱ�ȭ
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

// �Ľ�
DataFrame* GetDataFrame(const u8* buf) {
	unsigned int ec;
	// ������ �� ����
	u8 garbage[MAX_FRAME_SIZE] = { 0, };

	// �����Ҵ�
	DataFrame* df = (DataFrame*)malloc(sizeof(DataFrame));

    sscanf(buf, "%[^<]s", garbage); // �պκ��� ������ �� ����
	sscanf(buf + strlen(garbage) + 1, "%2d%1d%2d%1d%[^>]s", &df->groupnum, &df->cmdclass, &df->cmdnum, &df->dataformat, df->data);

	// ���� ó��: OverGroupCnt (���۵� ����� Group ��ȣ�� ������ ���)
	if (df->groupnum > 5) {
		ExceptionHandling(OverGroupCnt);
		free(df);
		return NULL;
	}

	// ���� ó��: OverClassCnt (���۵� ����� Class ��ȣ�� ������ ���)
	if (df->cmdclass != CMD_CLASS_CONTROL) {
		ExceptionHandling(OverClassCnt);
		free(df);
		return NULL;
    }
    
    if (BYTE_SIZE_TABLE[df->groupnum][df->cmdclass][df->cmdnum] == -1) {
        // ���� ó��: CantFindCmd_LED (���۵� ��ɾ LED �׷��� ã�� �� ����)
        if (df->groupnum == GROUP_LED) {
            ExceptionHandling(CantFindCmd_LED);
        }
        // ���� ó��: CantFindCmd_LCD (���۵� ��ɾ LCD �׷��� ã�� �� ����)
        else if (df->groupnum == GROUP_LCD) {
            ExceptionHandling(CantFindCmd_LCD);
        }
        free(df);
        return NULL;
	}

	// ���� ó��: OverFormatCnt (���۵� ����� Format ��ȣ�� ������ ���)
	if (BYTE_SIZE_TABLE[df->groupnum][df->cmdclass][df->cmdnum] != df->dataformat) {
		ExceptionHandling(OverFormatCnt);
		free(df);
		return NULL;
	}

    // ���� ó��: Data ũ�� ���� (Timeout, OverDataSize, LossDataSize)
	ec = DataCheck(df->data, BYTE_SIZE_TYPE[df->dataformat]);
	if (ec != Normal) {
		ExceptionHandling(ec);
		free(df);
		return NULL;
	}
	return df;
}

/* dataframe.c */
