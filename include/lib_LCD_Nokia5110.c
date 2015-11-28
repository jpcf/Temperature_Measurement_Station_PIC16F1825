#include "lib_LCD_Nokia5110.h"

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

void configLCD() {
    unsigned char buf;
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

void clearLCD() {
    unsigned char buf = 0x00;
    
    for(int i=0; i<6; i++) {
        for(int j=0; j < 84; j++) {
            sendByteLCD(&buf, 1);
        }
    }
}

void printCharLCD(char c) {
    for(int i=0; i<5; i++) {
        sendByteLCD(ASCII[c][i], 1);
    }
}



