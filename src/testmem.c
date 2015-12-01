#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "../include/lib_LCD_Nokia5110.h"
#include "../include/lib_memtest_PIC16F1825.h"
#include <xc.h>

#pragma config WDTE = OFF // This disables the watchdog timer!

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
    uint8_t test __at(0x20);
    test = 0x70;
    //FSR1 = &test;
    //INDF1 = 0x68;
    CLOCKconfig();
    TRISC = 0x00;
    LATC1 = 1;
     __delay_ms(2000);
    memtest_MARCH_Cmin();
    LATC1 = 0;
     __delay_ms(1000);
    LATC1 = 1;
    
    initLCD();
    configLCD();
    clearLCD();
    
    if( test != 0x00 ) 
        printlnLCD("RAM Error!", strlen("RAM Error!")+1, 2);
    else
        printlnLCD("RAM Ok!", strlen("RAM Ok!")+1, 2);
    
    while(1) {
    }
}
