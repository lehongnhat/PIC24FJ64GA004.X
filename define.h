/* 
 * File:   define.h
 * Author: le
 *
 * Created on November 28, 2016, 10:34 PM
 */


#define FOSC 20000000
#define FCY FOSC/2

#define Light_Sensor_Input  PORTCbits.RC4 //RC4 lam dau vao cam bien anh sang

extern unsigned int Fs;    // Sample Frequency (Hz)
extern unsigned int Ts;    // Sample Time Cycle (ms)
extern unsigned char e;    // Sample Time Cycle Error acceptable (%)

extern unsigned char Receiving_State; /* State of Receiving
                                       * State 0: Nothing
                                       * State 1: received 1st start bit and waiting 2nd one
                                       * State 11: received 1st start bit and waiting 2nd one, but gone out of Sample Time Cycle
                                       * 
                                       */
//#define FRC 8000000
//#define FCY FOSC/2



