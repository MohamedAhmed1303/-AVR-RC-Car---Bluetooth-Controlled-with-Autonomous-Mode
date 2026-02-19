/*
 * LCD_program.c
 *
 *  Created on: Sep 6, 2025
 *      Author: Mohamed
 */

#include "STD_TYPES.h"
#include <util/delay.h>
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"

void LCD_SendData(u8 Data)
{
	//RS -> 1, RW -> 0
	DIO_SetPinValue(CTRL_PORT,RS,PIN_HIGH);
	DIO_SetPinValue(CTRL_PORT,RW,PIN_LOW);
	//Data -> PORT
	DIO_SetPortValue(DATA_PORT,Data);
	//Enable Pulse
	DIO_SetPinValue(CTRL_PORT,EN,PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(CTRL_PORT,EN,PIN_LOW);
}

void LCD_SendCmd(u8 Cmd)
{
	//RS -> 0, RW -> 1
	DIO_SetPinValue(CTRL_PORT,RS,PIN_LOW);
	DIO_SetPinValue(CTRL_PORT,RW,PIN_LOW);
	//Data -> PORT
	DIO_SetPortValue(DATA_PORT,Cmd);
	//Enable Pulse
	DIO_SetPinValue(CTRL_PORT,EN,PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(CTRL_PORT,EN,PIN_LOW);
}

void LCD_Init()
{
	_delay_ms(40);
	LCD_SendCmd(0X38);
	_delay_ms(1);
	LCD_SendCmd(0X0c);
	_delay_ms(1);
	LCD_SendCmd(0X01);
	_delay_ms(2);
}

void LCD_SendString(char *ptrstring)
{
	u8 i=0;
	while(ptrstring[i] !='\0')
	{
		LCD_SendData(ptrstring[i]);
		i++;

	}
}

void LCD_SetPosition(u8 x,u8 y)
{
	u8 location;
	switch (x) {
	case 0:
		location=y;
		break;
	case 1:
		location=y+0X40;
		break;
	}
	LCD_SendCmd(location+128);
}

void LCD_ClearDisplay()
{
	LCD_SendCmd(0X01);
}

void LCD_SendNumber(u16 Number)
{
	u8 i=0;
	u8 arr[100]={0};

	while(Number>0)
	{
		arr[i]=Number%10;
		Number/=10;
		i++;
	}

	u8 j=0;
	for(j=i;j>0;j--)
	{
		LCD_SendData(arr[j-1]+'0');
	}
}

void LCD_SendSpecialCharacter(u8 BlockNum,u8 *ptrpattern,u8 x,u8 y )
{
	u8 StartingAddress=BlockNum*8;
	//set CGRAM address
	LCD_SendCmd(StartingAddress+64);
	//write inside CGRAM
	for (u8 i = 0;i < 8; i++)
	{
		LCD_SendData(ptrpattern[i]);
	}
	//display data
	LCD_SetPosition(x,y);
	LCD_SendData(BlockNum);
}






