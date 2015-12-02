#include "../include/lib_memtest_PIC16F1825.h"

uint16_t memtest_MARCH_Cmin() {
    
    // Writing 0, upwards
    for(FSR1 = DATAMEM_START; FSR1 <= DATAMEM_END; FSR1++) {
        INDF1 = 0x00;
    }
    
    // Reading 0 and Writing 1 in place, upwards
    for(FSR1 = DATAMEM_START; FSR1 <= DATAMEM_END; FSR1++) {
        if(INDF1 != 0x00) {
            return FSR1;
        }
        INDF1 = 0xFF;
    }
    
    LATC1 = 0;
    
    // Reading 1 and Writing 0 in place, upwards
    for(FSR0 = DATAMEM_START; FSR0 <= DATAMEM_END; FSR0++) {
        if(INDF0 != 0xFF) {
            return FSR0;
        }

        INDF0 = 0x00;
    }
    
    // Reading 0 and Writing 1 in place, downwards
    for(FSR0 = DATAMEM_END; FSR0 >= DATAMEM_START; FSR0--) {
        if(INDF0 != 0x00) {
            return FSR0;
        }

        INDF0 = 0xFF;
    }
    
    // Reading 1 and Writing 0 in place, downwards
    for(FSR0 = DATAMEM_END; FSR0 >= DATAMEM_START; FSR0--) {
        if(INDF0 != 0xFF) {
            return FSR0;
        }
        INDF0 = 0x00;
    }
    
    // Finally, reading 0, upwards
    for(FSR0 = DATAMEM_START; FSR0 <= DATAMEM_END; FSR0++) {
        if(INDF0 != 0x00) {
            return FSR0;
        }
    }

    return 0x3000;
}

void eraseRAM() {
    for(FSR0 = DATAMEM_START; FSR0 <= DATAMEM_END; FSR0++) {
        INDF0 = 0x00;
    }
}


