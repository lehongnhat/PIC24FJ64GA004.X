
#include <p24FJ64GA004.h>

#include "Timer.h"
#include "define.h"
#include "UART.h"

void Config_Timer1(unsigned int T){
    unsigned int P = (T/1000.0) * FCY / 64;
    T1CON = 0x00;   //reset control register
    TMR1 = 0;       //reset Timer register
    PR1 = P;        //set Period value
    IPC0bits.T1IP = 3;  //set Priority level of Timer1 Interrupt
    IFS0bits.T1IF = 0;  //clear Timer1 interrupt Flag
    IEC0bits.T1IE = 1;  //enable Timer1 Interrupt
    T1CONbits.TCKPS = 0b10; //64:1 prescale value
    T1CONbits.TON = 1;  //Start Timer 1  
}

void Stop_Timer1(){
    IFS0bits.T1IF = 0;  //clear Timer1 interrupt Flag
    T1CONbits.TON = 0;
}

