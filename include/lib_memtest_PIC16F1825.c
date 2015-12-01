#include "../include/lib_memtest_PIC16F1825.h"

void memtest_MARCH_Cmin() {
    
    uint8_t result __at(0x2000) = 0x00;
    
    // Writing 0, upwards
    for(FSR1 = 0x2000; FSR1 <= 0x29AF; FSR1++) {
        INDF1 = 0x00;
    }
    
    // Reading O and Writing 1 in place, upwards
    for(FSR1 = 0x2000; FSR1 <= 0x29AF; FSR1++) {
        if(INDF1 != 0x00) {
            result = 0xFF;
            return;
        }
        INDF1 = 0xFF;
    }
    
    // Reading 1 and Writing 0 in place, upwards
    for(FSR1 = 0x2000; FSR1 <= 0x29AF; FSR1++) {
        if(INDF1 != 0xFF) {
            result = 0xFF;
            return;
        }
        INDF1 = 0x00;
    }
    
    // Reading 0 and Writing 1 in place, downwards
    for(FSR1 = 0x29AF; FSR1 <= 0x2000; FSR1--) {
        if(INDF1 != 0x00) {
            result = 0xFF;
            return;
        }
        INDF1 = 0xFF;
    }
    
    // Reading 1 and Writing 0 in place, downwards
    for(FSR1 = 0x29AF; FSR1 <= 0x2000; FSR1--) {
        if(INDF1 != 0xFF) {
            result = 0xFF;
            return;
        }
        INDF1 = 0x00;
    }
    
    // Finally, reading 0, upwards
    for(FSR1 = 0x2000; FSR1 <= 0x29AF; FSR1++) {
        if(INDF1 != 0x00) {
            result = 0xFF;
            return;
        }
    }
    
    result = 0x00;
    
}




