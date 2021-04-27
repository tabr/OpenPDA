/*
 * interrrupts.h
 *
 * Created: 20.09.2017 18:39:36
 *  Author: tabr
 */ 


#ifndef INTERRRUPTS_H_
#define INTERRRUPTS_H_

ISR(INT1_vect);
ISR(TIMER1_OVF_vect); //inactive
ISR(TIMER2_OVF_vect);//10ms


#endif /* INTERRRUPTS_H_ */