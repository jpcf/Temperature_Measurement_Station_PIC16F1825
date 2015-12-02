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

    char str[14] ;
    
    CLOCKconfig();
    TRISC = 0x00;
    LATC1 = 1;
    // __delay_ms(2000);
    LATC1 = 0;

     //__delay_ms(1000);
    
    initLCD();
    configLCD();
    clearLCD();
    
    //sprintf(str, "Testing RAM");
    //printlnLCD(str, strlen(str), 2);
    
    LATC1 = 1;
    
    eraseRAM();
    uint16_t resultRAMtest = memtest_MARCH_Cmin();
    LATC1 = 0;
    
    if(0x3000 != resultRAMtest) {
        sprintf(str, "RAM Error!");
        printlnLCD(str, strlen(str), 2);
    } else {
        sprintf(str, "RAM Ok!");
        printlnLCD(str, strlen(str), 2);
    }
    
    while(1) {
    }
}
