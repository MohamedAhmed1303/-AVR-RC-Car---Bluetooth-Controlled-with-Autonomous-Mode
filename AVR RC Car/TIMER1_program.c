/*
 * TIMER1_program.c
 *
 *  Created on: Dec 2, 2025
 *      Author: Mohamed
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "GI_interface.h"
#include "TIMER1_config.h"
#include "TIMER1_interface.h"
#include "TIMER1_private.h"
#include "TIMER0_private.h"


void TIMER1_Init()
{
	//SELECT FAST PWM -> MODE 14
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);

	//NON-INVERTED MODE
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);
	SET_BIT(TCCR1A,TCCR1A_COM1A1);

	//PRESCALER 8
	CLR_BIT(TCCR1B,TCCR1B_CS10);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS12);
}

void TIMER1_Init_Ultrasonic(void)
{
	TCNT1 = 0;

	// Normal mode
	CLR_BIT(TCCR1A, TCCR1A_WGM10);
	CLR_BIT(TCCR1A, TCCR1A_WGM11);
	CLR_BIT(TCCR1B, TCCR1B_WGM12);
	CLR_BIT(TCCR1B, TCCR1B_WGM13);

	// Prescaler = 8 (1µs per tick)
	SET_BIT(TCCR1B, TCCR1B_CS11);

	// Enable Input Capture Interrupt
	SET_BIT(TIMSK, TIMSK_TICIE1);

	// Rising edge initially
	SET_BIT(TCCR1B, TCCR1B_ICES1);
}

void TIMER1_SetICRValue(u16 NumberOfTicks)
{
	ICR1=NumberOfTicks;
}

void TIMER1_SetCompareValue(u16 NumberOfTicks)
{
	OCR1A=NumberOfTicks;
}
