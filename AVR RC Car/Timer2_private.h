/*
 * Timer2_private.h
 *
 *  Created on: Jan 2, 2026
 *      Author: Mohamed
 */

#ifndef TIMER2_PRIVATE_H_
#define TIMER2_PRIVATE_H_


#define TCCR2                     *((volatile u8*)0X45)
#define TCCR2_WGM20               6
#define TCCR2_COM21               5
#define TCCR2_COM20               4
#define TCCR2_WGM21               3
#define TCCR2_CS22                2
#define TCCR2_CS21                1
#define TCCR2_CS20                0

#define TCNT2                     *((volatile u8*)0X44)

#define OCR2                      *((volatile u8*)0X43)


#endif /* TIMER2_PRIVATE_H_ */
