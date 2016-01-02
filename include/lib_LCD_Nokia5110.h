/*
Authors: José Pedro Fonseca, 2015
University of Porto, Portugal
*/

#include <xc.h>
#include <stdint.h>

#define DC    LATC3
#define SCE   LATC4
#define RST   LATC5
#define DIN   LATC2
#define SCK   LATC0

typedef struct LCDcursor {
    uint8_t xPos;
    uint8_t yPos;
} LCDcursor;

void initLCD();

void sendByteLCD(unsigned char* buf, unsigned char dataCommand);

void send_N_ByteLCD(unsigned char* buf, unsigned char dataCommand, int numBytes);

void gotoXY(uint8_t X, uint8_t Y);

void configLCD();

void clearLCD(LCDcursor* cursor);

void printCharLCD(char c);

void printlnLCD(char* str, uint8_t numBytes, uint8_t alignment, LCDcursor* cursor);

void printImageLCD(char* imageStr);
