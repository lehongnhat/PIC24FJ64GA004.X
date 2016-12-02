/* 
 * File:   UART.h
 * Author: LEHONGNHAT
 *
 * Created on October 2, 2016, 12:19 AM
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif
    void UART1_init();
    void UART1_write_byte(unsigned char c);
    void UART1_write_string(unsigned char *s);
    void UART1_write_number(float num);
    
    void UART2_init();    
    void UART2_write_byte(unsigned char c);
    void UART2_write_string(unsigned char *s);
    void UART2_write_number(float num);
    
#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

