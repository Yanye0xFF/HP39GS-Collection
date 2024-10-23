#include "gpio.h"

void output_set(unsigned char state) {
    //set output
    *GPBCON &= 0x1FFFCF;
	*GPBCON |= 0x10;
    *GPBDAT = (state) ? ((*GPBDAT) | 0x04) : ((*GPBDAT) & 0x0B);
}

unsigned char input_get() {
    //set input
    *GPBCON &= 0x1FFFCF;
    return (*GPBDAT & 0x4) >> 2;
}

void pull_up() {
    *GPBUP &= 0x04;
}

void pull_up_dis() {
    *GPBUP |= 0x04;
}

/*
#define rGPHCON    (*(volatile unsigned *)0x07A00070) //Port H control
#define rGPHDAT    (*(volatile unsigned *)0x07A00074) //Port H data
#define rGPHUP     (*(volatile unsigned *)0x07A00078) //Pull-up control H

//H PIN2 PIN3
//output
rGPHCON |= 0x50;

//pull up enable
rGPHUP |= 0x0c;

rGPHDAT |=0x0c; //set 1

rGPHDAT &=0x7F3; //set 0
*/