
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "../include/PIC16F1825_configs.h"
#include "../include/ds18b20.h"

int main(int argc, char** argv) {
    uint8_t rom_test_result;
    float tempe;
    
    pic16f1825_init();
    
    /*
     TESTE DA RAM
     */
    
    rom_test_result = memtest_program_mem();
    if(0 == rom_test_result){
        // METER NO LCD que deu merda xD   
    }else {
        // METER NO LCD ok!
    }
    
    set_precision_ds18b20(PRECISION_12);
    
    while(1){
        start_temp_measure_ds18b20();
        __delay_ms(1000);           // Wait for temperature measurement 
        tempe = read_temp_ds18b20();
        
        // IMPRIMIR NO LCD O VALOR DA TEMPERATURA
  
    }

    return (EXIT_SUCCESS);
}

