/*
 * File:   main.c
 * Author: le
 *
 * Created on November 25, 2016, 9:07 PM
 */


#include "xc.h"
#include "Peripheral_pin_select.h"
#include "UART.h"
#include "Timer.h"
#include <stdio.h>
#include "define.h"
#include "Light_Data.h"

// CONFIG2
#pragma config POSCMOD = HS             // Primary Oscillator Select (HS Oscillator mode selected)
#pragma config I2C1SEL = PRI            // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF             // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = OFF           // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = PRI              // Oscillator Select (Primary Oscillator (XT, HS, EC))
#pragma config SOSCSEL = SOSC           // Sec Oscillator Select (Default Secondary Oscillator (SOSC))
#pragma config WUTSEL = LEG             // Wake-up timer Select (Legacy Wake-up Timer)
#pragma config IESO = ON                // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)


// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Windowed Watchdog Timer enabled; FWDTEN must be 1)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config ICS = PGx1               // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)


#include <libpic30.h>

unsigned int Fs = 50;


int main(void) {
    unsigned int i;
    UART1_mapping(10, 11);
    UART1_init();
    
    Config_Timer1(1000);
    
    Config_Light_Sensor();
    
    TRISBbits.TRISB12 = 0;
    LATBbits.LATB12 = 1;
    TRISBbits.TRISB13 = 0;
    LATBbits.LATB13 = 0;
    
    TRISBbits.TRISB15 = 0;
    LATBbits.LATB15 = 1;
    
    while(1){
        __delay_ms(2000);
        LATBbits.LATB13 = !LATBbits.LATB13;
        LATBbits.LATB12 = !LATBbits.LATB12;
//        UART1_write_string("It's OK \n");
    }
    return 0;
}

void __attribute__((__interrupt__, __shadow__)) _T1Interrupt(void){
    if(U1MODEbits.UARTEN & IFS0bits.T1IF ){
//    UART1_write_string(" da du 2s ");
    IFS0bits.T1IF = 0; //clear Timer1 interrupt Flag
    }
    
}

//void __attribute__((__interrupt__)) _CNInterrupt(void){
//    if(IEC1bits.CNIE & IFS1bits.CNIF){
//        UART1_write_string(" Ok \n");
//        IFS1bits.CNIF = 0;
//    }
//}
//
void __attribute__((__interrupt__,__shadow__)) _INT1Interrupt(void){
    if(IFS1bits.INT1IF){
        UART1_write_string(" Ok 1 \n");
        IFS1bits.INT1IF = 0;    //Clear External Interrupt 1 Flag
    }
}

//void __attribute__((__interrupt__)) _INT0Interrupt(void){
//    if (IFS0bits.INT0IF){
//        UART1_write_string(" Ok \n");
//        IFS0bits.INT0IF = 0;
//    }
//}