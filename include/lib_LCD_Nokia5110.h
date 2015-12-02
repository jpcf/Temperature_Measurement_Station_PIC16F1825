#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 4000000

#define DC    LATC3
#define SCE   LATC4
#define RST   LATC5
#define DIN   LATC2
#define SCK   LATC0

void initLCD();

void sendByteLCD(unsigned char* buf, unsigned char dataCommand);

void send_N_ByteLCD(unsigned char* buf, unsigned char dataCommand, int numBytes);

void gotoXY(uint8_t X, uint8_t Y);

void configLCD();

void clearLCD();

void printCharLCD(char c);

void printlnLCD(char* str, uint8_t numBytes, uint8_t alignment);

void printImageLCD(char* imageStr);