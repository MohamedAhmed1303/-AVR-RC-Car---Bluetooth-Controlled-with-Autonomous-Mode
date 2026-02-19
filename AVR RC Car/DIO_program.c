/*
 * DIO_program.c
 *
 *  Created on: Sep 5, 2025
 *      Author: Mohamed
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"


/*********** TO CONTROL COMPLETE PORT ***********/
//CAL DIO_SetPortDirection(PORTA , 0X0F)
void DIO_SetPortDirection(u8 PortNum , u8 PortDirection)
{
	switch (PortNum)
	{
	case PORTA:DDRA_reg=PortDirection;break;
	case PORTB:DDRB_reg=PortDirection;break;
	case PORTC:DDRC_reg=PortDirection;break;
	case PORTD:DDRD_reg=PortDirection;break;
	}
}

//CALL DIO_SetPortValue(PORTB , 0XFF)
void DIO_SetPortValue(u8 PortNum , u8 PortValue)
{
	switch (PortNum)
	{
	case PORTA:PORTA_reg=PortValue;break;
	case PORTB:PORTB_reg=PortValue;break;
	case PORTC:PORTC_reg=PortValue;break;
	case PORTD:PORTD_reg=PortValue;break;
	}
}

/*********** TO CONTROL COMPLETE ONE PIN ***********/
//CALL DIO_SetPinDirection(PORTC ,PIN6, PIN_OUT)
//CALL DIO_SetPinDirection(PORTD ,PIN3, PIN_IN)
void DIO_SetPinDirection(u8 PortNum ,u8 PinNum, u8 PinDirection)
{
	if(PinDirection == PIN_OUT)
	{
		switch(PortNum)
		{
		case PORTA:SET_BIT(DDRA_reg,PinNum);break;
		case PORTB:SET_BIT(DDRB_reg,PinNum);break;
		case PORTC:SET_BIT(DDRC_reg,PinNum);break;
		case PORTD:SET_BIT(DDRD_reg,PinNum);break;
		}
	}
	else if(PinDirection == PIN_IN)
	{
		switch(PortNum)
		{
		case PORTA:CLR_BIT(DDRA_reg,PinNum);break;
		case PORTB:CLR_BIT(DDRB_reg,PinNum);break;
		case PORTC:CLR_BIT(DDRC_reg,PinNum);break;
		case PORTD:CLR_BIT(DDRD_reg,PinNum);break;
		}
	}
}

void DIO_SetPinValue(u8 PortNum ,u8 PinNum, u8 PinValue)
{
	if(PinValue == PIN_HIGH)
	{
		switch(PortNum)
		{
		case PORTA:SET_BIT(PORTA_reg,PinNum);break;
		case PORTB:SET_BIT(PORTB_reg,PinNum);break;
		case PORTC:SET_BIT(PORTC_reg,PinNum);break;
		case PORTD:SET_BIT(PORTD_reg,PinNum);break;
		}
	}
	else if(PinValue == PIN_LOW)
	{
		switch(PortNum)
		{
		case PORTA:CLR_BIT(PORTA_reg,PinNum);break;
		case PORTB:CLR_BIT(PORTB_reg,PinNum);break;
		case PORTC:CLR_BIT(PORTC_reg,PinNum);break;
		case PORTD:CLR_BIT(PORTD_reg,PinNum);break;
		}
	}
}

/*********** TO GET ONE PIN VALUE ***********/
u8 DIO_GetPinValue(u8 PortNum ,u8 PinNum)
{
	u8 PinState=255;
	switch(PortNum)
	{
	case PORTA:PinState=GET_BIT(PINA_reg,PinNum);break;
	case PORTB:PinState=GET_BIT(PINB_reg,PinNum);break;
	case PORTC:PinState=GET_BIT(PINC_reg,PinNum);break;
	case PORTD:PinState=GET_BIT(PIND_reg,PinNum);break;
	}

	return PinState;
}

u32 Mapping(u32 R1_min,u32 R1_max,u32 R2_min,u32 R2_max,u32 R1_reading)
{
	return (R2_max-((R2_max-R2_min)*(R1_max-R1_reading)/(R1_max-R1_min)));
}
