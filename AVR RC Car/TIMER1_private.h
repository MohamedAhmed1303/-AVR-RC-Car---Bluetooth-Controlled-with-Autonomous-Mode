/*
 * TIMER1_private.h
 *
 *  Created on: Dec 2, 2025
 *      Author: Mohamed
 */

#ifndef TIMER1_PRIVATE_H_
#define TIMER1_PRIVATE_H_


#define TCCR1A                *((volatile u8*)0X4F)
#define TCCR1A_COM1A1         7
#define TCCR1A_COM1A0         6
#define TCCR1A_WGM10          0
#define TCCR1A_WGM11          1


#define TCCR1B                *((volatile u8*)0X4E)
#define TCCR1B_CS10           0
#define TCCR1B_CS11           1
#define TCCR1B_CS12           2
#define TCCR1B_WGM12          3
#define TCCR1B_WGM13          4
#define TCCR1B_ICES1          6


#define TCNT1                 *((volatile u16*)0X4C)

#define OCR1A                 *((volatile u16*)0X4A)

#define ICR1                  *((volatile u16*)0X46)

#define TIFR                  *((volatile u16*)0X58)
#define TIFR_ICF1            5


#endif /* TIMER1_PRIVATE_H_ */
