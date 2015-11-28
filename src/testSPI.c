#include <stdlib.h>
#include <stdint.h>
#include "../include/lib_LCD_Nokia5110.h"
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
    
    unsigned char buf;
    
    CLOCKconfig();
    initLCD();
    
    buf = 0x21;
    sendByteLCD(&buf, 0);
    buf = 0xC0; // Set the Operation Voltage to a good value
    sendByteLCD(&buf, 0);
    buf = 0x07; // Set the TempCoef to 4
    sendByteLCD(&buf, 0);
    buf = 0x13; // Set Bias bits BSx. This way we get Mux of 1:48
    sendByteLCD(&buf, 0);
    buf = 0x20; // Normal set of controls
    sendByteLCD(&buf, 0);
    buf = 0x08; // Clears the screen
    sendByteLCD(&buf, 0);
    buf = 0x0C; // Normal Display Mode
    sendByteLCD(&buf, 0);
    
    LATC1 = 1;
    __delay_ms(1000);
    
    while(1) {
        printCharLCD('T');
        __delay_ms(1000);
    }
    
}
