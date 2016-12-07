/* 
 * File:   Timer.h
 * Author: le
 *
 * Created on November 28, 2016, 10:07 PM
 */

#ifndef TIMER_H
#define	TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

    void Config_Timer1(unsigned int T);  //T is time cycle (ms)
    void Stop_Timer1(); 

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

