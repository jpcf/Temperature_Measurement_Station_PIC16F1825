#ifndef _PIC16F1825_UTILS_
#define _PIC16F1825_UTILS_

#include <xc.h>
#include <stdint.h>


/* PINS */
#define RA2 0x04

#define RC0 0x01
#define RC1 0x02
#define RC2 0x04
#define RC3 0x08
#define RC4 0x10
#define RC5 0x20


void pic16f1825_init(void); /* Configure PIC16F1825 oscillator */


/* MAKE SURE THAT THE INTERRUPTS ARE DISABLED BEFORE USING THE 1-WIRE FUNCTIONS TO AVOID TIMING PROBLEMS */
/* The following functions assume that the RA2 pin is used */

bit one_wire_init(); /* init sequence for 1-wire protocol */
void one_wire_write_bit(uint8_t bit_value);
void one_wire_write_byte(uint8_t byte_value);
bit one_wire_read_bit();
uint8_t one_wire_read_byte();

/* Functions to access EEPROM */
void write_eeprom(uint8_t addr, uint8_t data);
uint8_t read_eeprom(uint8_t addr);

#endif