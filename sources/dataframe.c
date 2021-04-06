/* dataframe.c */

#include "dataframe.h"

const u8 BYTE_SIZE_TYPE[6] = { 1, 2, 3, 4, 10, 16 };    // Byte Format �� �� Byte size

u32 GetBytes(const u8* buf, u8 byte_size, u8 data[]) {
    u32 byte_size_cnt = 0;
    while (buf[byte_size_cnt] != '>' && byte_size_cnt < MAX_DATA_SIZE) {
        data[byte_size_cnt] = buf[byte_size_cnt];
        byte_size_cnt++;
    }
    // OverDataSize
    if (byte_size < byte_size_cnt) {
        
    }
    // LossDataSize
    else if (byte_size > byte_size_cnt) {
        
    }
}

// �Ľ�
DataFrame* GetDF(const u8 *buf) {
	u8 tmp[16] = {0,};
    // �����Ҵ�
    DataFrame* df = (DataFrame*)malloc(sizeof(DataFrame));
    
    // Group ��ȣ ó��
    strncpy(tmp, buf + 1, 2);
    tmp[2] = 0;
    df->groupnum = atoi(tmp);

    // CMD Class ó��
    strncpy(tmp, buf + 3, 1);
    tmp[1] = 0;
	df->cmdclass = atoi(tmp);

    // CMD Num ó��
    strncpy(tmp, buf + 4, 2);
    tmp[2] = 0;
	df->cmdnum   = atoi(tmp);

    // DataFormat ó��
    strncpy(tmp, buf + 6, 1);
    tmp[1] = 0;
	df->dataformat = atoi(tmp);

    // Data ó��
    memset(df->data, 0, sizeof(u8) * MAX_DATA_SIZE);
    GetBytes(buf + 7, BYTE_SIZE_TYPE[df->dataformat], df->data);

	return df;
}

/* dataframe.c */