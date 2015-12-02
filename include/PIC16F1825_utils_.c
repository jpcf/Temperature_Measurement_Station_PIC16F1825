#include "../include/PIC16F1825_utils.h"
#include "../include/PIC16F1825_configs.h"

void pic16f1825_init(void){
    // 16 mhz clock
    OSCCONbits.SCS = 0; // clear SCS bits <1:0> 
    OSCCONbits.IRCF = 0b1111; // Set IRCF<3:0> to 1111 ( bits 3-6 of OSCCON)
    while(OSCSTATbits.HFIOFR == 0 || OSCSTATbits.HFIOFS == 0); // wait for clock to get stable
    
}

bit one_wire_init(){
    uint8_t read_value;
    
    ANSELAbits.ANSA2 = 0; // RA2 is digital
    OPTION_REGbits.nWPUEN = 0; // enable individual pull-up control
    WPUAbits.WPUA2 = 0; // disable pull-up on rc2
    
    TRISA2 = 0; // RC2 as output
    LATA2 = 0; // write a zero
    __delay_us(490);
    
    TRISA2 = 1; // RC2 as input
    __delay_us(80);
   
    read_value = PORTA & RA2;
    __delay_us(425);
   
    if(!read_value)
        return 1;
    else
        return 0;
}

void one_wire_write_bit(uint8_t bit_value){
    
    TRISA2 = 1; // RA2 as input
    __delay_us(2);
    
    TRISA2 = 0; // RA2 as output
    
    if(bit_value == 0){
        LATA2 = 0; // write a zero 
        __delay_us(65);
        TRISA2 = 1; // change to input
    }else {
        LATA2 = 0; // write a zero 
        __delay_us(3);
        TRISA2 = 1; // change to input
        __delay_us(65);
    }
}

bit one_wire_read_bit(){
    uint8_t read_value;
    
    TRISA2 = 1; // RA2 as input
    __delay_us(2);  //-> recovering time
    
    TRISA2 = 0; // RA2 as output
    LATA2 = 0; // write a zero
    __delay_us(2);
    TRISA2 = 1; // change to input
    
    // reading should be near 15us after falling edge of RA2
    __delay_us(7);
    read_value = PORTA & RA2;
    
    __delay_us(53);
    
    if(read_value)
        return 1;
    else
        return 0;
    
}

void one_wire_write_byte(uint8_t byte_value){
    uint8_t i;
    
    for(i=0;i<8;i++){
        one_wire_write_bit(byte_value & 0x01);
        byte_value >>= 1;
    }
}

uint8_t one_wire_read_byte(){
    uint8_t i,res=0,aux=0;
    
    for(i=0;i<8;i++){
        aux=one_wire_read_bit();
        res |= (aux<<i);
        aux=0;
    }
    return res;
}

