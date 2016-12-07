/* 
 * File:   Light_Data.h
 * Author: le
 *
 * Created on November 29, 2016, 1:18 AM
 */

#ifndef LIGHT_DATA_H
#define	LIGHT_DATA_H

#ifdef	__cplusplus
extern "C" {
#endif
    void Config_Light_Sensor(void);
    char * Light_Sensor_Data_Receiving(unsigned char N);
    void Light_Sensor_Byte_Receiving(unsigned char position, unsigned char bit_value);
    void Start_bits_Error();
    void Parity_bit_Error();
#ifdef	__cplusplus
}
#endif

#endif	/* LIGHT_DATA_H */

