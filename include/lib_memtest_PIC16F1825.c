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

uint8_t memtest_program_mem(){
    
    uint16_t prog_space_addr,prog_space_data,checksum_calc;
    uint16_t CHECKSUM; // expected checksum
    
    for (prog_space_addr = 0x0000; prog_space_addr <= 0x1FFF; prog_space_addr++ ){
        
        prog_space_data = 0;
        
        EEADRL = prog_space_addr & 0x00FF;
        EEADRH = (prog_space_addr >> 8) & 0x00FF;
        EECON1bits.CFGS = 0;
        EECON1bits.EEPGD = 1;
        EECON1bits.RD = 1;
        asm("NOP");
        asm("NOP");
        
        prog_space_data = EEDATH;
        prog_space_data = prog_space_data << 8;
        prog_space_data |= EEDATL;
        
        if(prog_space_addr != 0x1FFF)
            checksum_calc = checksum_calc + prog_space_data;
        else
            CHECKSUM = prog_space_data; // the expected checksum is stored in the last address
    }
   
    return !((CHECKSUM & 0x3FFF) ^ (checksum_calc & 0x3FFF));
}


