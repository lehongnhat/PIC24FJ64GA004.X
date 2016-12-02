
#include <p24FJ64GA004.h>

#include "Timer.h"
#include "define.h"

void Config_Timer1(unsigned int T){
    unsigned int P = T*FCY/1000/256;
    T1CON = 0x00;   //reset control register
    TMR1 = 0;       //reset Timer register
    PR1 = P;        //set Period value
    IPC0bits.T1IP = 3;  //set Priority level of Timer1 Interrupt
    IFS0bits.T1IF = 0;  //clear Timer1 interrupt Flag
    IEC0bits.T1IE = 1;  //enable Timer1 Interrupt
    T1CONbits.TCKPS = 0b11; //1:256 prescale value
    T1CONbits.TON = 1;  //Start Timer 1  
    
}

