#include "exception.h"

void ExceptionHandling(ErrorCode ec) {
    //char buf[5];
	if (ec < 4) {
		if (ec == OverDataSize) {
            //sprintf(buf, "%d", OverDataSize);
			//write_string(0x00, "OverDataSize");
            write_sci0("OverDataSize");
		}
		else if (ec == LossDataSize) {
            //sprintf(buf, "%d", OverDataSize);
			//write_string(0x00, "LossDataSize");
            write_sci0("LossDataSize");
		}
		else if (ec == OverGroupCnt) {
            //sprintf(buf, "%d", OverDataSize);
			//write_string(0x00, "OverGroupCnt");
            write_sci0("OverGroupCnt");
		}
		else if (ec == OverClassCnt) {
            //sprintf(buf, "%d", OverDataSize);
			//write_string(0x00, "OverClassCnt");
            write_sci0("OverClassCnt");
		}
	}
	else {
		if (ec == OverFormatCnt) {
            //sprintf(buf, "%d", OverFormatCnt);
			//write_string(0x00, "OverFormatCnt");
            write_sci0("OverFormatCnt");
		}
		else if (ec == CantFindCmd_LED) {
            //sprintf(buf, "%d", CantFindCmd_LED);
			//write_string(0x00, "CantFindCmd_LED");
            write_sci0("CantFindCmd_LED");
		}
		else if (ec == CantFindCmd_LCD) {
            //sprintf(buf, "%d", CantFindCmd_LCD);
			//write_string(0x00, "CantFindCmd_LCD");
            write_sci0("CantFindCmd_LCD");
		}
		else if (ec == Timeout) {
            //sprintf(buf, "%d", Timeout);
			//write_string(0x00, "Timeout");
            write_sci0("Timeout");
		}
	}
    //write_sci0(buf);
}
