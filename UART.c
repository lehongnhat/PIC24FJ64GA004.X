/* 
 * File:   UART.c
 * Author: LEHONGNHAT
 *
 * Created on October 2, 2016, 12:24 AM
 */

#include "UART.h"
#include <xc.h>
#include "define.h"
// UART declaration

#define BAUDRATE 9600
#define BRGVAL (unsigned int)((FCY/BAUDRATE)/16)-1
#include <libpic30.h>
#include <stdio.h>

void UART1_init(){
    unsigned int i;
    U1MODEbits.STSEL = 0; // 1 Stop bit
    U1MODEbits.PDSEL = 0; // No Parity, 8 data bits
    //U1MODEbits.PDSEL = 1; // even Parity, 8 data bits
    U1MODEbits.ABAUD = 0; // Auto-Baud Disabled
    U1MODEbits.BRGH = 0; // Low Speed mode
    U1BRG = BRGVAL;
    
    U1STAbits.UTXISEL0 = 0; // Interrupt after one TX Character is transmitted
    U1STAbits.UTXISEL1 = 0;
    IEC0bits.U1TXIE = 0; // disable UART TX Interrupt
    IEC0bits.U1RXIE = 1;
    U1STAbits.URXISEL = 0; // Interrupt after one RX character is received;
    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable UART TX
    /* wait at least 104 usec (1/9600) before sending first char */
    for(i = 0; i < 4200; i++){
        Nop();
    }
}

void UART2_init(){
    unsigned int i;
    U2MODEbits.STSEL = 0; // 1 Stop bit
    U2MODEbits.PDSEL = 0; // No Parity, 8 data bits
    //U2MODEbits.PDSEL = 1; // even Parity, 8 data bits
    U2MODEbits.ABAUD = 0; // Auto-Baud Disabled
    U2MODEbits.BRGH = 0; // Low Speed mode
    U2BRG = BRGVAL;
    
    U2STAbits.UTXISEL0 = 0; // Interrupt after one TX Character is transmitted
    U2STAbits.UTXISEL1 = 0;
    IEC1bits.U2TXIE = 0; // disable UART TX Interrupt
    IEC1bits.U2RXIE = 1;
    U2STAbits.URXISEL = 0; // Interrupt after one RX character is received;
    U2MODEbits.UARTEN = 1; // Enable UART
    U2STAbits.UTXEN = 1; // Enable UART TX
    /* wait at least 104 usec (1/9600) before sending first char */
    for(i = 0; i < 4200; i++){
        Nop();
    }
}

void UART1_write_byte(unsigned char c){
    while(U1STAbits.UTXBF);
        U1TXREG = c;
}

void UART2_write_byte(unsigned char c){
    while(U2STAbits.UTXBF);
        U2TXREG = c;
}

void UART1_write_string(unsigned char *string){
    while(*string)
        UART1_write_byte(*string++);
}

void UART2_write_string(unsigned char *string){
    while(*string)
        UART2_write_byte(*string++);
}

void UART1_write_number(float num){
    unsigned char StrBuf[10];
    snprintf(StrBuf, 10, "%f", num);
    UART1_write_string(StrBuf);
}

void UART2_write_number(float num){
    unsigned char StrBuf[10];
    snprintf(StrBuf, 10, "%f", num);
    UART2_write_string(StrBuf);
}

