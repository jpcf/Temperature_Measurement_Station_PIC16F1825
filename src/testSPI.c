#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>

#pragma config WDTE = OFF // This disables the watchdog timer!

#define _XTAL_FREQ 4000000
#define DC    LATC3
#define SCE   LATC4
#define RST   LATC5
#define DIN   LATC2
#define SCK   LATC0

void TIMER2config (unsigned char comparePer, unsigned char preload,
                   unsigned char presc, unsigned char postsc) {
    PR2    = comparePer;  
    TMR2   = preload; 
    T2CON |= postsc | (presc<<3); 
}

void initLCD() {
    // Some initial configs on port C
    ANSELC &= 0x00; // All bits on port C are set to Digital I/O's
    TRISC  &= 0x00; // All bits on Port C are set to Outputs
    APFCON0 |= (1<<5); // Don't use special features on Pin RC3
    APFCON1 |= (1<<2); // Don't use special features on Pin RC3
    
    LATC = 0x00;
    
    // All pins are initialy idle (HIGH), except for DIN
    DC    = 1;
    SCE   = 1;
    RST   = 1;
    DIN   = 0;
    SCK   = 0;
    
    // Initial reset to the device
    __delay_ms(300);
    RST = 0;
    __delay_ms(300);
    RST = 1;
}

void sendByteLCD(unsigned char* buf, unsigned char dataCommand) {
    DC  = dataCommand;
    SCK = 0;
    __delay_us(1);
    SCE = 0;
    __delay_us(1);
    
    for(int i=0; i < 8; i++) {
        SCK = 0; // Clock goes idle
        
        // Since we send the MSB first, we mask bit 8 and we send its logical value
        (*buf) & 0b10000000 ? DIN = 1 : DIN = 0;  
        
        // Rising Edge of the Clock
        __delay_us(1);
        SCK = 1;
        __delay_us(1);
        
        // We shift the next bit
        (*buf) = ((*buf)<<1);
    }
    
    SCK = 0;
}

void printCharLCD(char c) {

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
        buf = rand() % 256;
        sendByteLCD(&buf, 1);
        __delay_ms(1);
    }
    
}
