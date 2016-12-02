#include "Peripheral_pin_select.h"
#include <xc.h>


/*mapping cac chan Rx, Tx cho UART1
 * Cac tham so:
 * Rxp: chan RP muon lam chan nhan data
 * TXp: chan RP muon lam chan truyen data
 */
void UART1_mapping(unsigned int Rxp, unsigned int Txp){
    // clear the bit 6 of OSCCONL to unlock Pin Re-map
    __builtin_write_OSCCONL(OSCCON & 0xBF); 
    // Assign U1RX To Pin Rx
    RPINR18bits.U1RXR = Rxp;
    // Assign U1TX To Pin Tx
    switch(Txp){
        case 0: RPOR0bits.RP0R = 3;
                break;
        case 1: RPOR0bits.RP1R = 3;
                break;
        case 2: RPOR1bits.RP2R = 3;
                break;
        case 3: RPOR1bits.RP3R = 3;
                break;
        case 4: RPOR2bits.RP4R = 3;
                break;
        case 5: RPOR2bits.RP5R = 3;
                break;
        case 6: RPOR3bits.RP6R = 3;
                break;
        case 7: RPOR3bits.RP7R = 3;
                break;
        case 8: RPOR4bits.RP8R = 3;
                break;
        case 9: RPOR4bits.RP9R = 3;
                break;
        case 10: RPOR5bits.RP10R = 3;
                break;
        case 11: RPOR5bits.RP11R = 3;
                break;
        case 12: RPOR6bits.RP12R = 3;
                break;
        case 13: RPOR6bits.RP13R = 3;
                break;
        case 14: RPOR7bits.RP14R = 3;
                break;
        case 15: RPOR7bits.RP15R = 3;
                break;
        case 16: RPOR8bits.RP16R = 3;
                break;
        case 17: RPOR8bits.RP17R = 3;   
                break;
        case 18: RPOR9bits.RP18R = 3;
                break;
        case 19: RPOR9bits.RP19R = 3;
                break;
        case 20: RPOR10bits.RP20R = 3;
                break;
        case 21: RPOR10bits.RP21R = 3;
                break;
        case 22: RPOR11bits.RP22R = 3;
                break;
        case 23: RPOR11bits.RP23R = 3;
                break;
        case 24: RPOR12bits.RP24R = 3;
                break;
        case 25: RPOR12bits.RP25R = 3;
    }
    // clear the bit 6 of OSCCONL to unlock Pin Re-map
    __builtin_write_OSCCONL(OSCCON | 0x40);
}

/*Mapping cho Exteranl Interrupt 1
 *Tham so RP: chan RP muon gan cho External Interrupt 1
 */
void ExtInterrupt1_mapping(unsigned int RP){
    // clear the bit 6 of OSCCONL to unlock Pin Re-map
    __builtin_write_OSCCONL(OSCCON & 0xBF); 
    RPINR0bits.INT1R = RP;
    // clear the bit 6 of OSCCONL to unlock Pin Re-map
    __builtin_write_OSCCONL(OSCCON | 0x40);
}