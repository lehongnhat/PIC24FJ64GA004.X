/* 
 * File:   I2C.c
 * Author: LEHONGNHAT
 *
 * Created on October 2, 2016, 10:50 AM
 */

#include <i2c.h>
#include "I2C_functions.h"
#include "UART.h"

void Acces_Register_I2C1(unsigned char IC_Address, 
            unsigned char Register_Address);
void Wait_ACK_I2C1(void);
void Wait_Flag_I2C1(void);

void Open_I2C1(unsigned int BRG_value){
    unsigned int config1, config2;
    
    config2 = BRG_value;  
    config1 = (I2C1_ON & I2C1_IDLE_CON & I2C1_CLK_HLD &
             I2C1_IPMI_DIS & I2C1_7BIT_ADD &
             I2C1_SLW_DIS & I2C1_SM_DIS &
             I2C1_GCALL_DIS & I2C1_STR_DIS &
             I2C1_NACK & I2C1_ACK_DIS & I2C1_RCV_DIS &
             I2C1_STOP_DIS & I2C1_RESTART_DIS &
             I2C1_START_DIS);
    OpenI2C1(config1,config2);
    IdleI2C1();
}

void WriteByte_I2C1(unsigned char IC_WriteAddress,
            unsigned char RegisterAddress, unsigned char Byte){
    Acces_Register_I2C1(IC_WriteAddress, RegisterAddress);
    
    MasterWriteI2C1(Byte);
    while(I2C1STATbits.TBF); 
    Wait_Flag_I2C1(); 
    Wait_ACK_I2C1();
    
    StopI2C1();
    /* Wait till Stop sequence is completed */
    while(I2C1CONbits.PEN);
    /* Clear interrupt flag */ 
    IFS1bits.MI2C1IF = 0; 
//    IdleI2C1();
    UART2_write_string(" Success ");
}

unsigned char ReadByte_I2C1(unsigned char IC_WriteAddress, 
            unsigned char IC_ReadAddress, unsigned char RegisterAddress){
    unsigned char value=1;
    Acces_Register_I2C1(IC_WriteAddress, RegisterAddress);
    
    //Generate Repeated Start Bus Event
    I2C1CONbits.RSEN = 1;
    Wait_Flag_I2C1();
    //Write Read Adrress
    MasterWriteI2C1(IC_ReadAddress);
    while(I2C1STATbits.TBF); 
    Wait_Flag_I2C1(); 
    Wait_ACK_I2C1();
    
    I2C1CON &= 0xFFE0; // Clear 5 lowers bit of I2CxCON register before set RCEN
    value = MasterReadI2C1();
    while(I2C1CONbits.RCEN);
    Wait_Flag_I2C1();
    //Generate NACK
    I2C1CON &= 0xFFE0; // Clear 5 lowers bit of I2CxCON register before set RCEN
    NotAckI2C1();
    Wait_Flag_I2C1();
    
     StopI2C1();
    /* Wait till Stop sequence is completed */
    while(I2C1CONbits.PEN);
    /* Clear interrupt flag */ 
    IFS1bits.MI2C1IF = 0; 
//    IdleI2C1();
    return value;
}
/*****************************************************************************
 Descrip: Khoi dong I2C1, ghi dia chi doc cua IC va dia chi thanh ghi can truy cap
 * 
*****************************************************************************/
void Acces_Register_I2C1(unsigned char IC_WriteAddress, 
            unsigned char RegisterAddress){
    StartI2C1();
    /* Wait till Start sequence is completed */
    while(I2C1CONbits.SEN);
    /* Clear interrupt flag */ 
    IFS1bits.MI2C1IF = 0; 
    /* Write Slave address and set master for transmission */
    MasterWriteI2C1(IC_WriteAddress);
    /* Wait till address is transmitted */
    while(I2C1STATbits.TBF);  // 8 clock cycles
    Wait_Flag_I2C1(); // Wait for 9th clock cycle
    Wait_ACK_I2C1();
    
    MasterWriteI2C1(RegisterAddress);
    while(I2C1STATbits.TBF); 
    Wait_Flag_I2C1(); 
    Wait_ACK_I2C1();
}

void Wait_Flag_I2C1(void)
{
    while(!IFS1bits.MI2C1IF);           // wait for flag to be high
    IFS1bits.MI2C1IF=0;
}
void Wait_ACK_I2C1(void)
{
    while(I2C1STATbits.ACKSTAT);        // wait for ack receive from slave
}

