/* 
 * File:   ds18b20.h
 * Author: Carlos Ferreira
 *
 * Created on 22 de Novembro de 2015, 16:08
 */

#ifndef DS18B20_H
#define	DS18B20_H

#include <stdint.h>

//CONFIGURATION
#define PRECISION_9 0x1F
#define PRECISION_10 0x3F
#define PRECISION_11 0x5F
#define PRECISION_12 0x7F


//ROM COMMANDS
#define READ_ROM 0x33
#define SKIP_ROM 0xCC

//FUNCTION COMMANDS
#define READ_SCRATCHPAD 0xBE 
#define WRITE_SCRATCHPAD 0x4E
#define CONVERT_T 0x44           //Single temperature measure

float read_temp_ds18b20();
void set_precision_ds18b20(uint8_t precision);
void start_temp_measure_ds18b20();


#endif	/* DS18B20_H */

