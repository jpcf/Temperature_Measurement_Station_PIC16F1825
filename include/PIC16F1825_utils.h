#ifndef _PIC16F1825_UTILS_
#define _PIC16F1825_UTILS_

#include <xc.h>
#include <stdint.h>

// TIMER2/4/6 Constants 
#define TMR_PRESCALER_1_1          0x00
#define TMR_PRESCALER_1_4          0x01
#define TMR_PRESCALER_1_16         0x02
#define TMR_PRESCALER_1_64         0x03

#define TMR_POSTSCALER_1_1         0x00
#define TMR_POSTSCALER_1_2         0x01
#define TMR_POSTSCALER_1_3         0x02
#define TMR_POSTSCALER_1_4         0x03
#define TMR_POSTSCALER_1_5         0x04
#define TMR_POSTSCALER_1_6         0x05
#define TMR_POSTSCALER_1_7         0x06
#define TMR_POSTSCALER_1_8         0x07
#define TMR_POSTSCALER_1_9         0x08
#define TMR_POSTSCALER_1_10        0x09
#define TMR_POSTSCALER_1_11        0x0A
#define TMR_POSTSCALER_1_12        0x0B
#define TMR_POSTSCALER_1_13        0x0C
#define TMR_POSTSCALER_1_14        0x0D
#define TMR_POSTSCALER_1_15        0x0E
#define TMR_POSTSCALER_1_16        0x0F

// UART2 CONSTANTS @ Fosc = 16mhz
#define BAUD_RATE_57600 68
#define BAUD_RATE_9600 103


// PINS
#define RC0 0x01
#define RC1 0x02
#define RC2 0x04
#define RC3 0x08
#define RC4 0x10
#define RC5 0x20

// I2C
#define I2C_SLAVE_ADDRESS 0x23


void pic16f1825_init(void); // Configure PIC16F1825 oscillator

// for high precision delays in the order of us the following routine should NOT BE USED
inline void timer6delay(uint8_t tmr6_value, uint8_t prescaler, uint8_t postscaler); // ((4*Prescaler*Postscaler)/Fosc) * PRx = Delay


void uart2_init(uint8_t baudrate); // Pin RC4 = Tx ; Pin RC5 = Rx
void i2c_init();                   // Pin RC0 = SCL ; Pin RC1 = SDA

// MAKE SURE THAT THE INTERRUPTS ARE DISABLED BEFORE USING THE 1-WIRE FUNCTIONS TO AVOID TIMING PROBLEMS
bit one_wire_RC2_init(); // init sequence for 1-wire protocol on pin RC2 if return ==1 then ok!
void one_wire_RC2_write_bit(uint8_t bit_value);
void one_wire_RC2_write_byte(uint8_t byte_value);
bit one_wire_RC2_read_bit();
uint8_t one_wire_RC2_read_byte();

inline void enable_glb_peripheral_int(); // set global and peripheral bits of INTCON SFR
inline void disable_all_int();          // clear all bits of INTCON SFR

#endif