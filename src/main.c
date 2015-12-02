#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <xc.h>
#include "../include/PIC16F1825_configs.h"
#include "../include/ds18b20.h"
#include "../include/lib_LCD_Nokia5110.h"
#include "../include/lib_memtest_PIC16F1825.h"

int main(int argc, char** argv) {
    
    char tempStr[14];
        
    // ----- Device Initial Config ----- //
    pic16f1825_init();
    
    // ------ LCD Initial Config ------- //
    initLCD();
    configLCD();
    clearLCD();
    
    // ---------- RAM Testing ---------- //
    uint16_t RAMtest = memtest_MARCH_Cmin();
    LATC1 = 1;
    
    // Returns 0x3000 if no Errors, otherwise returns the address of the first error
    if(0x3000 == RAMtest){
        sprintf(tempStr, "RAM Test OK!");  
        printlnLCD(tempStr, strlen(tempStr), 2);
    }else {
        sprintf(tempStr, "!RAM @ 0x%04X", RAMtest);
        printlnLCD(tempStr, strlen(tempStr), 2);
    }
    
    // ---------- ROM Testing ---------- //
    uint8_t ROMtest = memtest_program_mem();
    if(0 == ROMtest){
        sprintf(tempStr, "ROM Test OK!");  
        printlnLCD(tempStr, strlen(tempStr), 2); 
    }else {
        sprintf(tempStr, "ROM Error!");  
        printlnLCD(tempStr, strlen(tempStr), 2);
    }
    
    //set_precision_ds18b20(PRECISION_12);
    
    while(1){
        //start_temp_measure_ds18b20();
        //__delay_ms(1000);           // Wait for temperature measurement 
        //tempe = read_temp_ds18b20();
        
        // IMPRIMIR NO LCD O VALOR DA TEMPERATURA
  
    }

    return (EXIT_SUCCESS);
}

