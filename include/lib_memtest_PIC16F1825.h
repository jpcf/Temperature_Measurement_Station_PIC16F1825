#ifndef LIB_MEMTEST_PIC16F1825_H
#define LIB_MEMTEST_PIC16F1825_H

#include <xc.h>
#include <stdint.h>

#define DATAMEM_START 0x2000
#define DATAMEM_END   0x23EF

uint16_t memtest_MARCH_Cmin();
void     eraseRAM();

//For this function to work, is necessary to change compiler settings to compute the checksum and store it
// on the last program memory address.
// the checksum option should be: 0-1ffe@1FFF,algorithm=2
// return 0 if errors were detected in the program memory
uint8_t memtest_program_mem();

#endif
