/*
 * TIMER_program.c
 *
 *  Created on: Nov 20, 2025
 *      Author: Mohamed
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER0_config.h"
#include "TIMER0_interface.h"
#include "TIMER0_private.h"

static void(*GlobalPtrOVF)(void)=NULL;
static void(*GlobalPtrCTC)(void)=NULL;

void TIMER0_Init()
{

#if TIMER_MODE == OVF_MODE
	//WGM , PIE OVF
	CLR_BIT(TCCR0,TCCR0_WGM00);
	CLR_BIT(TCCR0,TCCR0_WGM01);
	SET_BIT(TIMSK,TIMSK_TOIE0);
#elif TIMER_MODE == CTC_MODE
	//WGM , PIE CTC
	CLR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
	SET_BIT(TIMSK,TIMSK_OCIE0);
#elif TIMER_MODE == FAST_PWM
	SET_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
	//don't needed interrupt
#else
#error("Wrong Mode Choice");
#endif

#if PRE_SCALER == DIV_BY_8
	CLR_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);
#elif PRE_SCALER == DIV_BY_64
	SET_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);
#else
#error("Wrong Mode Choice");
#endif

}

void TIMER0_SetPreload(u8 NumberOfTicks)
{
	TCNT0=NumberOfTicks;
}

void TIMER0_SetCompareValue(u8 NumberOfTicks)
{
	OCR0=NumberOfTicks;
}

void TIMER0_SetCallBackOVF(void(*PtrFunc)(void))
{
	if (PtrFunc != NULL)
	{
		GlobalPtrOVF = PtrFunc;
	}
}

void TIMER0_SetCallBackCTC(void(*PtrFunc)(void))
{
	if (PtrFunc != NULL)
	{
		GlobalPtrCTC = PtrFunc;
	}
}

void TIMER0_SetFastPWM_Mode(u8 Mode)
{
	switch (Mode)
	{
	case NON_INV_MODE:
		CLR_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
		break;
	case INV_MODE:
		SET_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
		break;
	}
}

//ISR Of CTC Vector 10
void __vector_10(void)       __attribute__((signal));
void __vector_10(void)
{
	GlobalPtrCTC();
}

//ISR Of OVF Vector 11
void __vector_11(void)       __attribute__((signal));
void __vector_11(void)
{
	GlobalPtrOVF();
}
