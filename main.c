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
#pragma config IOL1WAY = OFF            // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
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
#include <string.h>

unsigned int Fs = 10;
unsigned int Ts;
unsigned char e = 10;
unsigned char Byte_Receiving_State = 0;




int main(void) {
    Ts = 1000 / Fs; 
    unsigned int i;
    UART1_mapping(10, 11);
    UART1_init();
    
    TRISBbits.TRISB12 = 0;
    LATBbits.LATB12 = 1;
    TRISBbits.TRISB13 = 0;
    LATBbits.LATB13 = 0;
    
    TRISBbits.TRISB15 = 0;
    LATBbits.LATB15 = 1;
    
    while(1){
        __delay_ms(1500);
        LATBbits.LATB13 = !LATBbits.LATB13;
        LATBbits.LATB12 = !LATBbits.LATB12;
        UART1_write_string(Light_Sensor_Data_Receiving(8));
        UART1_write_string("\n");
//        UART1_write_string("It's OK \n");
    }
    return 0;
}

void __attribute__((__interrupt__, __shadow__)) _T1Interrupt(void){
    if(U1MODEbits.UARTEN & IFS0bits.T1IF ){
      switch(Byte_Receiving_State){
          case 0:
              Start_bits_Error();
              UART1_write_string(" T1-0 ");
              break;
          case 1:
              if(Light_Sensor_Input){
                  Byte_Receiving_State = 2;  // Change to State 2 if receive 2nd start bit
                  Config_Timer1(Ts);
//                   UART1_write_string(" T1-2 ");
              } 
              else {
                  UART1_write_string(" er 1 ");
                  Start_bits_Error();
              }
              break;
          case 2:
              if(!Light_Sensor_Input){
                  Byte_Receiving_State = 3;  // Change to State 2 if receive 2nd start bit
//                   UART1_write_string(" T1-3 ");
              } 
              else {
                  Start_bits_Error();
                  UART1_write_string(" er 2 ");
              }
              break;
          case 3:
              Byte_Receiving_State = 41;
              if(!Light_Sensor_Input){
                  Light_Sensor_Byte_Receiving(1,1);
              }
              break;
          case 41:
              Byte_Receiving_State = 42;
              if(!Light_Sensor_Input) Light_Sensor_Byte_Receiving(2,1);
              break;
          case 42:
              Byte_Receiving_State = 43;
              if(!Light_Sensor_Input) Light_Sensor_Byte_Receiving(3,1);
              break;
          case 43:
              Byte_Receiving_State = 44;
              if(!Light_Sensor_Input) Light_Sensor_Byte_Receiving(4,1);
              break;    
          case 44:
              Byte_Receiving_State = 45;
              if(!Light_Sensor_Input) Light_Sensor_Byte_Receiving(5,1);
              break;
          case 45:
              Byte_Receiving_State = 46;
              if(!Light_Sensor_Input) Light_Sensor_Byte_Receiving(6,1);
              break;  
          case 46:
              Byte_Receiving_State = 47;
              if(!Light_Sensor_Input) Light_Sensor_Byte_Receiving(7,1);
              break;
          case 47:
              Byte_Receiving_State = 48;
              if(!Light_Sensor_Input) Light_Sensor_Byte_Receiving(8,1);
              else Light_Sensor_Byte_Receiving(8,0);
              break;
          case 48:
              Byte_Receiving_State = 49;
              if(!Light_Sensor_Input) Light_Sensor_Byte_Receiving(9,1);
              else Light_Sensor_Byte_Receiving(9,0);
              break;
          case 49:
              Stop_Timer1();
              Byte_Receiving_State = 0;
              IEC1bits.INT1IE = 1; //    enable External Interrupt 1
              break;
          default:
              Start_bits_Error();
      } 
      
    IFS0bits.T1IF = 0; //clear Timer1 interrupt Flag
    }
    
}

//void __attribute__((__interrupt__)) _CNInterrupt(void){
//    if(IEC1bits.CNIE & IFS1bits.CNIF){
//        UART1_write_string(" Ok \n");
//        IFS1bits.CNIF = 0;
//    }
//}

void __attribute__((__interrupt__,__auto_psv__)) _INT1Interrupt(void){
    __delay_us(10);
    if(!PORTCbits.RC4){
        IEC1bits.INT1IE = 0;    //disable External Interrupt 1  
//    __delay_us(10);
//    if(!PORTCbits.RC4){
//        switch(Byte_Receiving_State){
//            case 0:
//                Config_Timer1(Ts * (1 + e / 100.0));
//                Byte_Receiving_State = 1; //change to State 1
//                UART1_write_string(" E-0 ");
//                break;
//            case 1: 
//                //not Data
//                Stop_Receiving_Data();
//                UART1_write_string(" E-1 ");
//                UART1_write_number(PR1);
//                break;
//            case 2:
//                Config_Timer1(Ts/2);
//                Byte_Receiving_State = 3;
//                UART1_write_string(" E-2 ");
//                break;
//            case 3:
//                //not Data
//                Stop_Receiving_Data();
//                UART1_write_string(" E-3 ");
//                break;
//            default:
//                //Error during transmission Light Data
//                ;
//        }
//        UART1_write_string(" 0->1 ");
//         
//    }
//    else UART1_write_string(" 1->0 ");
        if(Byte_Receiving_State == 0){
            Config_Timer1(Ts * 1.2);
            Byte_Receiving_State = 1;
        }
        else {
            Start_bits_Error();
            UART1_write_string(" er EXT ");
        }
    }
    IFS1bits.INT1IF = 0;    //Clear External Interrupt 1 Flag
//    IEC1bits.INT1IE = 1;    //enable External Interrupt 1 
}

//void __attribute__((__interrupt__)) _INT0Interrupt(void){
//    if (IFS0bits.INT0IF){
//        UART1_write_string(" Ok \n");
//        IFS0bits.INT0IF = 0;
//    }
//}

