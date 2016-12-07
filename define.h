/* 
 * File:   define.h
 * Author: le
 *
 * Created on November 28, 2016, 10:34 PM
 */


#define FOSC 20000000
#define FCY FOSC/2

#define Light_Sensor_Input PORTCbits.RC4 //LATCbits.LATC4 //RC4 lam dau vao cam bien anh sang

extern unsigned int Fs;    // Sample Frequency (Hz)
extern unsigned int Ts;    // Sample Time Cycle (ms)
extern unsigned char e;    // Sample Time Cycle Error acceptable (%)

extern unsigned char Byte_Receiving_State; /* State of Receiving each Byte
                                       * State 0: Nothing
                                       * State 1: received 1st start bit and waiting 2nd one
                                       * State 2: received 2nd start bit and waiting 3rd one
                                       * State 3: received 3rd start bit and waiting to the end of this one
                                       * State 41: receiving 1st bit of data byte   
                                       * State 42: receiving 2nd bit of data byte
                                       * State 43: receiving 3rd bit of data byte
                                       * State 44: receiving 4th bit of data byte
                                       * State 45: receiving 5th bit of data byte  
                                       * State 46: receiving 6th bit of data byte
                                       * State 47: receiving 7th bit of data byte
                                       * State 48: receiving 8th bit of data byte
                                       * State 49: receiving odd parity bit
                                       */
extern unsigned char Receiving_State;    /* State of Receiving Process
                                         * State 0: being freezed
                                         * State 1: receiving
                                         * State 2: Error during the Receiving Process (Start bits Error)
                                         * State 3: Parity Error
                                         */
//#define FRC 8000000
//#define FCY FOSC/2



