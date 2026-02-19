/*
 * TIMER_private.h
 *
 *  Created on: Nov 20, 2025
 *      Author: Mohamed
 */

#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_


#define TCCR0                 *((volatile u8*)0X53)
#define TCCR0_WGM00           6
#define TCCR0_COM01           5
#define TCCR0_COM00           4
#define TCCR0_WGM01           3
#define TCCR0_CS02            2
#define TCCR0_CS01            1
#define TCCR0_CS00            0

/******************************************************/

#define TCNT0                 *((volatile u8*)0X52)

/******************************************************/

#define OCR0                  *((volatile u8*)0X5C)

/******************************************************/

#define TIMSK                 *((volatile u8*)0X59)
#define TIMSK_TOIE0           0
#define TIMSK_OCIE0           1
#define TIMSK_TICIE1          5


#endif /* TIMER0_PRIVATE_H_ */
