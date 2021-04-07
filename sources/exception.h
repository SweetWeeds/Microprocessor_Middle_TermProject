#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "stdio.h"
#include "stdlib.h"

// 에러코드 정의
typedef enum {
	OverDataSize = 0,
	LossDataSize,
	OverGroupCnt,
	OverClassCnt,
	OverFormatCnt,
	CantFindCmd_LED,
	CantFindCmd_LCD,
	Timeout,
	Normal
} ErrorCode;

// 예외처리
void ExceptionHandling(ErrorCode ec);
void write_string(char offset, const char *);

#endif	/* EXCEPTION_H */
