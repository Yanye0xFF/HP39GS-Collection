#include "verify.h"

const unsigned char encrypt[8] = {0x61, 0x11, 0x41, 0x31, 0x71, 0xa1, 0xb1, 0x41};
const unsigned int offset = 4;

unsigned char check_serial() {

    unsigned char local[8] = {0};
    unsigned char temp = 0;

    unsigned char *serial = (unsigned char *) SERIAL;

    for(int i = 0; i < 8; i++) {
        local[i] = *(serial + i);
    }
    for(int i = 0; i < 8; i++) {
        temp = (local[i] << offset) + local[7];
        if(temp != encrypt[i]) {
            return 0;
        }
    }
    return 1;
}
