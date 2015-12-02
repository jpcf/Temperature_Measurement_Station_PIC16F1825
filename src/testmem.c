#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "../include/lib_LCD_Nokia5110.h"
#include "../include/lib_memtest_PIC16F1825.h"
#include <xc.h>

#pragma config WDTE = OFF     // This disables the watchdog timer!

void TIMER2config (unsigned char comparePer, unsigned char preload,
                   unsigned char presc, unsigned char postsc) {
    PR2    = comparePer;  
    TMR2   = preload; 
    T2CON |= postsc | (presc<<3); 
}

void CLOCKconfig() {
    OSCCON  = 0x6A; //Sets the internal oscillator fosc = 4 MHz
    OSCSTAT = 0x00;
    OSCTUNE = 0x00;
}

void main(void) {
   
    CLOCKconfig();
    TRISC = 0x00;
    //sprintf(str, "Testing RAM");
    //printlnLCD(str, strlen(str), 2);
        
    initLCD();
    configLCD();
    clearLCD();
    
    uint16_t memAddrErr = memtest_MARCH_Cmin();
    
    char str[14] ; 
    if(0x3000 != memAddrErr ) {
        sprintf(str, "Error @ %4X", memAddrErr);
        printlnLCD(str, strlen(str), 2);
    } else {
        sprintf(str, "RAM OK!");
        printlnLCD(str, strlen(str), 2);
    }
    
    while(1) {
    }
}
