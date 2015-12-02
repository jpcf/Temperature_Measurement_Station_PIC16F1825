#include "../include/PIC16F1825_utils.h"
#include "../include/PIC16F1825_configs.h"

void pic16f1825_init(void){
    // 16 mhz clock
    OSCCONbits.SCS = 0; // clear SCS bits <1:0> 
    OSCCONbits.IRCF = 0b1111; // Set IRCF<3:0> to 1111 ( bits 3-6 of OSCCON)
    while(OSCSTATbits.HFIOFR == 0 || OSCSTATbits.HFIOFS == 0); // wait for clock to get stable
    
}


inline void timer6delay(uint8_t tmr6_value, uint8_t prescaler, uint8_t postscaler){
    TMR6 = 0; 
    PR6 = tmr6_value;
    T6CONbits.T6OUTPS = postscaler;
    T6CONbits.T6CKPS  = prescaler;
    PIR3bits.TMR6IF = 0; // clear timer6 interrupt flag 
    
    T6CONbits.TMR6ON  = 1;
    while(PIR3bits.TMR6IF ==0 ); // wait
    PIR3bits.TMR6IF =0;
    T6CONbits.TMR6ON  = 0;
    
}

void uart2_init(uint8_t baudrate){
    APFCON0bits.RXDTSEL = 0; // Alternate pin function control register
    APFCON0bits.TXCKSEL = 0;
    TRISC |= (RC5); // RC5 as a input
 
    if(baudrate == BAUD_RATE_57600){
        BAUDCONbits.BRG16 = 1;
        TXSTAbits.BRGH = 1;
        SPBRGL = BAUD_RATE_57600;// @ 16 Mhz
        SPBRGH = 0;
    }else {
        BAUDCONbits.BRG16 = 1;
        TXSTAbits.BRGH = 0;
        SPBRGL = BAUD_RATE_9600;// @ 16 Mhz 
    }
    
    TXSTAbits.SYNC = 0; // async. operation
    RCSTAbits.SPEN = 1; // enable receiver   
    RCSTAbits.CREN = 1; // enable receiver
    TXSTAbits.TXEN = 1; // enable transmitter
         
    
}


bit one_wire_RC2_init(){
    uint8_t read_value;
    
    ANSELCbits.ANSC2 = 0; // RC2 is digital
    OPTION_REGbits.nWPUEN = 0; // enable individual pull-up control
    WPUCbits.WPUC2 = 0; // disable pull-up on rc2
    
    TRISC &= !RC2; // RC2 as output
    LATC &= !RC2; // write a zero
    __delay_us(490);
    
    TRISC |= RC2; // RC2 as input
    __delay_us(80);
   
    read_value = PORTC & RC2;
    __delay_us(425);
   
    if(!read_value)
        return 1;
    else
        return 0;
}

void one_wire_RC2_write_bit(uint8_t bit_value){
    
    TRISC |= RC2; // RC2 as input
    __delay_us(2);
    
    TRISC &= !RC2; // RC2 as output
    
    if(bit_value == 0){
        LATC &= !RC2; // write a zero 
        __delay_us(65);
        TRISC |= RC2; // change to input
    }else {
        LATC &= !RC2; // write a zero 
        __delay_us(3);
        TRISC |= RC2; // change to input
        __delay_us(65);
    }
}

bit one_wire_RC2_read_bit(){
    uint8_t read_value;
    
    TRISC |= RC2; // RC2 as input
    __delay_us(2);  //-> recovering time
    
    TRISC &= !RC2; // RC2 as output
    LATC &= !RC2; // write a zero
    __delay_us(2);
    TRISC |= RC2; // change to input
    
    // reading should be near 15us after falling edge of RC2
    __delay_us(7);
    read_value = PORTC & RC2;
    
    __delay_us(53);
    
    if(read_value)
        return 1;
    else
        return 0;
    
}

void one_wire_RC2_write_byte(uint8_t byte_value){
    uint8_t i;
    
    for(i=0;i<8;i++){
        one_wire_RC2_write_bit(byte_value & 0x01);
        byte_value >>= 1;
    }
}

uint8_t one_wire_RC2_read_byte(){
    uint8_t i,res=0,aux=0;
    
    for(i=0;i<8;i++){
        aux=one_wire_RC2_read_bit();
        res |= (aux<<i);
        aux=0;
    }
    return res;
}

void i2c_init(){
    SSP1CON1bits.SSPEN = 0;  // disable i2c
    SSP1ADD = I2C_SLAVE_ADDRESS << 1;
    SSPMSK = 0xFF; // consider all bits of the received address
    SSP1STATbits.SMP = 1; // disable slew rate control in i2c mode of operation
    SSP1STATbits.CKE = 0; // disable SMbus
    SSP1CON1bits.CKP = 1; //enable clock in i2c slave mode (SCL release control)
    SSP1CON1bits.SSPM = 0b0110; // I2C slave mode, 7bit-address 
    SSP1CON2bits.GCEN = 0; // disable general call
    SSP1CON2bits.SEN = 1; // Start condition enable/stretch enable bit
    SSP1CON3bits.SBCDE = 1; // enable slave bus collision interrupts
    SSP1CON3bits.AHEN = 1; // Adress hold enable to decide to ack or not
    SSP1CON3bits.DHEN = 1; // Data hold enable to decide to ack or not
    PIR1bits.SSP1IF = 0; // clear interrupt flag
    PIE1bits.SSP1IE = 1; // enable i2c interrupts 
    
    ANSELCbits.ANSC0 = 0; // digital pin RC0
    ANSELCbits.ANSC1 = 0; // digital pin RC1
    TRISC |= RC0; // Input
    TRISC |= RC1; // Input
    SSP1CON1bits.SSPEN = 1;  //enable i2c
}

inline void enable_glb_peripheral_int(){
    INTCONbits.PEIE = 1; // enable peripheral interrupts
    INTCONbits.GIE = 1; // enable global interrupts
}

inline void disable_all_int(){
    INTCON = 0;
}

void putch(char data) {  // THIS FUNCTION REDIRECTS OUTPUT TO UART (for using printf)
 while(!PIR1bits.TXIF)
    continue;
 TXREG = data;
}

