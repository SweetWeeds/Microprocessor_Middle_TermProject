#include "exception.h"

// ����ó��
void ExceptionHandling(unsigned int ec) {
    unsigned char buf[27];
    sprintf(buf, "<050000%d>", ec);
    write_sci0(buf);
}
