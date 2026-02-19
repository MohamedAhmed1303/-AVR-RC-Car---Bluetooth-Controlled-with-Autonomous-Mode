/*
 * Timer2_program.c
 *
 *  Created on: Jan 2, 2026
 *      Author: Mohamed
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "Timer2_interface.h"
#include "Timer2_private.h"

void TIMER2_Init_FastPWM(void)
{
	// Fast PWM Mode
	SET_BIT(TCCR2, TCCR2_WGM20);
	SET_BIT(TCCR2, TCCR2_WGM21);

	// Prescaler = 8
	CLR_BIT(TCCR2, TCCR2_CS20);
	SET_BIT(TCCR2, TCCR2_CS21);
	CLR_BIT(TCCR2, TCCR2_CS22);

	// Non-Inverting Mode
	CLR_BIT(TCCR2, TCCR2_COM20);
	SET_BIT(TCCR2, TCCR2_COM21);
}

void TIMER2_SetCompareValue(u8 NumberOfTicks)
{
	OCR2=NumberOfTicks;
}

