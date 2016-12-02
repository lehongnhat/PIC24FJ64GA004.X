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
    void Light_Sensor_Data_Receiving();
    unsigned char Light_Sensor_Byte_Receiving();

#ifdef	__cplusplus
}
#endif

#endif	/* LIGHT_DATA_H */

