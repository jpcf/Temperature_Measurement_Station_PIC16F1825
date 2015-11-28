#include <xc.h>

#define _XTAL_FREQ 4000000

#define DC    LATC3
#define SCE   LATC4
#define RST   LATC5
#define DIN   LATC2
#define SCK   LATC0

void initLCD();

void sendByteLCD(unsigned char* buf, unsigned char dataCommand);

void configLCD();

void clearLCD();

void printCharLCD(char c);

