#include "../include/PIC16F1825_utils.h"
#include "../include/ds18b20.h"

float read_temp_ds18b20(){
    uint8_t temperature[2],configs;
    int16_t res;
    float temp;
    
    one_wire_RC2_init();
    one_wire_RC2_write_byte(SKIP_ROM);
    one_wire_RC2_write_byte(READ_SCRATCHPAD);
    temperature[0] = one_wire_RC2_read_byte(); // LSB
    temperature[1] = one_wire_RC2_read_byte(); // MSB
    one_wire_RC2_read_byte(); // ignore
    one_wire_RC2_read_byte(); // ignore
    configs = one_wire_RC2_read_byte();
    
    res=0;
    // See datasheet to understand LSB and MSB structure and why the following operations are used
    res = (((int16_t)temperature[1])<<4) | ((int16_t)(temperature[0] & 0xF0))>>4; // integer part of the temperature
    
    temp = (float) res;
    
    if(configs == PRECISION_9)
        temp += 0.5 * ((temperature[0] & 0x08)>>3);
    else if (configs == PRECISION_10)
        temp += 0.5 * ((temperature[0] & 0x08)>>3) + 0.25 * ((temperature[0] & 0x04)>>2);
    else if (configs == PRECISION_11)
        temp += 0.5 * ((temperature[0] & 0x08)>>3) + 0.25 * ((temperature[0] & 0x04)>>2) + 0.125 * ((temperature[0] & 0x02)>>1);
    else
        temp += 0.5 * ((temperature[0] & 0x08)>>3) + 0.25 * ((temperature[0] & 0x04)>>2) + 0.125 * ((temperature[0] & 0x02)>>1) + 0.0625 * (temperature[0] & 0x01) ;
 
    return temp;
}

void set_precision_ds18b20(uint8_t precision){
    uint8_t actual_values[2];
    
    one_wire_RC2_init();
    one_wire_RC2_write_byte(SKIP_ROM);
    one_wire_RC2_write_byte(READ_SCRATCHPAD);
    
    one_wire_RC2_read_byte(); // ignore
    one_wire_RC2_read_byte(); // ignore
    
    actual_values[0] = one_wire_RC2_read_byte(); // To preserve this config
    actual_values[1] = one_wire_RC2_read_byte();
    
    one_wire_RC2_init();
    one_wire_RC2_write_byte(SKIP_ROM);
    one_wire_RC2_write_byte(WRITE_SCRATCHPAD);
   
    one_wire_RC2_write_byte(actual_values[0]);
    one_wire_RC2_write_byte(actual_values[1]);
    one_wire_RC2_write_byte(precision);
    
}

void start_temp_measure_ds18b20(){
    one_wire_RC2_init();
    one_wire_RC2_write_byte(SKIP_ROM);
    one_wire_RC2_write_byte(CONVERT_T); 
}