#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "stdio.h"
#include "stdlib.h"
#include "sci.h"

// 에러코드 정의
#define OverDataSize  0
#define LossDataSize  1
#define OverGroupCnt  2
#define OverClassCnt  3
#define OverFormatCnt 4
#define CantFindCmd_LED 5
#define CantFindCmd_LCD 6
#define Timeout 7
#define Normal  8

// 예외처리
void ExceptionHandling(unsigned int ec);

#endif	/* EXCEPTION_H */
