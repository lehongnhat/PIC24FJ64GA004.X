#include <p24FJ64GA004.h>

#include "Light_Data.h"
#include "Peripheral_pin_select.h"
#include "UART.h"
#include "define.h"
#include "Timer.h"
#include <math.h>
#include <string.h>

char Light_Data[] = "";
unsigned char byte_value = 0;
unsigned char Receiving_State = 0;
unsigned char number_of_byte_received = 0;
unsigned char odd_parity = 0;

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
    IPC5bits.INT1IP = 4;    //set Priority level of External Interrupt 1
    INTCON2bits.INT1EP = 1; //interrupt on negative edge
    IFS1bits.INT1IF = 0;    //Clear External Interrupt 1 Flag
    IEC1bits.INT1IE = 1;    //enable External Interrupt 1    
}

char * Light_Sensor_Data_Receiving(unsigned char N){
    
    Receiving_State = 1;
    Byte_Receiving_State = 0;
    number_of_byte_received = 0;
    byte_value = 0;
    odd_parity = 0;
    Config_Light_Sensor();
    UART1_write_string("bat dau nhan \n");
    while (Receiving_State == 1) {
        if(number_of_byte_received == N) break;
    }
    if(Receiving_State == 2){
        // notice the Start bits error
        return "";
    }
    if(Receiving_State == 3){
        //notice the Parity error
        return "";
    }
    Receiving_State = 0;
    Stop_Timer1();
    IEC1bits.INT1IE = 0; //disable External Interrupt 1
    UART1_write_string("nhan xong \n");
    UART1_write_number(strlen(Light_Data));
    UART1_write_number(number_of_byte_received);
    return Light_Data;
}

void Light_Sensor_Byte_Receiving(unsigned char position, unsigned char bit_value){
    
    if(position == 8){
        if(bit_value){
            byte_value += powf(2, position - 1);    // Little Endian
            odd_parity ^= 1;    //  XOR vs 1 function 
//            UART1_write_number(byte_value);
        } 
    }
    else if(position == 9){
                if(bit_value != odd_parity) Parity_bit_Error();
                else{
//                     UART1_write_string(" ok ");
                     Light_Data[number_of_byte_received] = byte_value;
                     number_of_byte_received++;
//                     UART1_write_string(" nhan byte ok: ");
                     UART1_write_byte(byte_value);
                     byte_value = 0;
                     odd_parity = 0;
//                     UART1_write_string(Light_Data);
                }
    }
    else {
        byte_value += powf(2, position - 1);    // Little Endian
        odd_parity ^= 1;    //  XOR vs 1 function 
//        UART1_write_number(byte_value);
    }
}

void Start_bits_Error(){
    Stop_Timer1();
    IEC1bits.INT1IE = 0; //     disable External Interrupt 1
    Receiving_State = 2;
    UART1_write_string(" S-e \n");
}

void Parity_bit_Error(){
    Stop_Timer1();
    Receiving_State = 3;
    UART1_write_string(" P-e \n");
}
