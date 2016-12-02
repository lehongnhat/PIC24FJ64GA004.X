/* 
 * File:   I2C_functions.h
 * Author: LEHONGNHAT
 *
 * Created on October 2, 2016, 7:51 AM
 */

#ifndef I2C_functions_H
#define	I2C_functions_H

#ifdef	__cplusplus
extern "C" {
#endif
    void Open_I2C1(unsigned int BRG_value);
    void WriteByte_I2C1(unsigned char IC_WriteAddress,
            unsigned char RegisterAddress, unsigned char Byte);
    unsigned char ReadByte_I2C1 (unsigned char IC_WriteAddress, 
            unsigned char IC_ReadAddress, unsigned char RegisterAddress);
    void Acces_Register_I2C1(unsigned char IC_WriteAddress, 
            unsigned char RegisterAddress);
 

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_functions_H */

