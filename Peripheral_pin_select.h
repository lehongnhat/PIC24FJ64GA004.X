/* 
 * File:   Peripheral_pin_select.h
 * Author: le
 *
 * Created on November 27, 2016, 8:18 AM
 */

#ifndef PERIPHERAL_PIN_SELECT_H
#define	PERIPHERAL_PIN_SELECT_H

#ifdef	__cplusplus
extern "C" {
#endif
    void UART1_mapping(unsigned int Rx, unsigned int Tx);
    void ExtInterrupt1_mapping(unsigned int RP);


#ifdef	__cplusplus
}
#endif

#endif	/* PERIPHERAL_PIN_SELECT_H */

