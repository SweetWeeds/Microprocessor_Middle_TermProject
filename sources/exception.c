#include "exception.h"

void write_string(char offset, const char *cStr) {
	printf("%s\n", cStr);
}

void ExceptionHandling(ErrorCode ec) {
	if (ec < 4) {
		if (ec == OverDataSize) {
			write_string(0x00, "OverDataSize");
		}
		else if (ec == LossDataSize) {
			write_string(0x00, "LossDataSize");
		}
		else if (ec == OverGroupCnt) {
			write_string(0x00, "OverGroupCnt");
		}
		else if (ec == OverClassCnt) {
			write_string(0x00, "OverClassCnt");
		}
		// Unexpected
		else {
			write_string(0x00, "Unexpected");
		}
	}
	else {
		if (ec == OverFormatCnt) {
			write_string(0x00, "OverFormatCnt");
		}
		else if (ec == CantFindCmd_LED) {
			write_string(0x00, "CantFindCmd_LED");
		}
		else if (ec == CantFindCmd_LCD) {
			write_string(0x00, "CantFindCmd_LCD");
		}
		else if (ec == Timeout) {
			write_string(0x00, "Timeout");
		}
		// Unexpected
		else {
			write_string(0x00, "Unexpected");
		}
	}
}
