#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void putstr(const char *str) {
    while(*str) {
        putchar(*str++);
    }
}

int main() {
    unsigned char serial_num[8];
    unsigned char serial_enc[8];
    puts("generate encrypt serial");
    putstr("\ninput serial num: ");
    gets(serial_num);
    putstr("\nyour input: ");
    putstr(serial_num);
    putchar('\n');

    putstr("\nyour input(hex): ");
    for(int i = 0; i < 8; i++) {
        printf("0x%x ", serial_num[i]);
    }
    putchar('\n');

    srand((unsigned)time(NULL));
    int offset = rand() % 4 + 1;
    printf("\nrand offset: %d\n", offset);

    for(int i = 0; i < 8; i++) {
        serial_enc[i] = (serial_num[i] << offset) + serial_num[7];
    }
    
    putstr("\nencrypt code(hex): ");
    
    for(int i = 0; i < 8; i++) {
        if(i < 7) {
            printf("0x%x, ", serial_enc[i]);
        }else {
            printf("0x%x \n\n", serial_enc[i]);
        }
        
    }
    return 0;  
}