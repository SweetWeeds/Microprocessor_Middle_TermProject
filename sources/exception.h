#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "stdio.h"
#include "stdlib.h"
#include "sci.h"

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
    DynamicAllocFailed,
    QueueFault,
	Normal
} ErrorCode;

// 예외처리
void ExceptionHandling(ErrorCode ec);

#endif	/* EXCEPTION_H */
