#include <p24FJ64GA004.h>

#include "Light_Data.h"
#include "Peripheral_pin_select.h"
#include "UART.h"
#include "define.h"

void Config_Light_Sensor(){
//    // setup Light Sensor input Pin
//    TRISCbits.TRISC4 = 1;
//    IEC1bits.CNIE = 1;  //enable Input Change Notification Interrupt 
//    IFS1bits.CNIF = 0;  //Clear the CNxIF interrupt flag.
//    IPC4bits.CNIP = 3;  //set Priority level of Input Change Notification Interrupt
//    CNEN2bits.CN25IE = 1;
    
    //Light Sensor input Pin base on External Interrupt 1 at RP20/RC4 pin
    ExtInterrupt1_mapping(20);
    TRISCbits.TRISC4 = 1;
    IFS1bits.INT1IF = 0;    //Clear External Interrupt 1 Flag
    IPC5bits.INT1IP = 4;    //set Priority level of External Interrupt 1
    INTCON2bits.INT1EP = 1; //interrupt on negative edge
    IEC1bits.INT1IE = 1;    //enable External Interrupt 1    
    
}

void Light_Sensor_Data_Receiving(){
    
}

unsigned char Light_Sensor_Byte_Receiving(){
    
    
}