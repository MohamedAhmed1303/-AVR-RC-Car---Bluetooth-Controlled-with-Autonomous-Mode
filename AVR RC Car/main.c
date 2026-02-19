/*
 * main.c
 *
 *  Created on: Dec 29, 2025
 *      Author: Mohamed
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "UART_interface.h"
#include "GI_interface.h"
#include "TIMER0_interface.h"
#include "TIMER0_private.h"
#include "TIMER1_interface.h"
#include "TIMER1_private.h"
#include "Timer2_interface.h"
#include "LCD_interface.h"
#include <util/delay.h>

//======================== RC MODE ========================//

#define UART_TIMEOUT 300
u16 timeout_counter = 0;

u8 LastMotion = 'X';
u8 LCD_UpdateFlag = 0;

void Move_Forward();
void Move_ForwardRight();
void Move_ForwardLeft();
void Move_Back();
void Move_BackRight();
void Move_BackLeft();
void Move_Right();
void Move_Left();
void Stop();
void LCD_ShowMotion(u8 motion);

//======================== RC MODE ========================//

#define TRIG_PIN PIN5      // PORTD PIN5
#define ECHO_PIN PIN6      // ICP1 (PORTD PIN6)

volatile u16 t1 = 0;
volatile u16 t2 = 0;
volatile u8 flag = 0;

void Ultrasonic_Init(void);
u16 Ultrasonic_Read(void);
void AutoMode(void);

u8 Mode = 'K';   // K = RC mode, P = Auto mode
u8 PWM=0;

int main ()
{

	//configure LCD pins output
	//data -> output
	//ctrl port first 3 pins out
	DIO_SetPortDirection(PORTA,0XFF);
	DIO_SetPortDirection(PORTC,0X07);
	LCD_Init();
	LCD_ShowMotion('S');

	//RC CAR , CONNECT WITH BLUETOOTH , CONTROL DIRECTION AND SPEED
	//PIN CONFIGURATION
	//TX -> OUT , RX -> IN
	DIO_SetPinDirection(PORTD,PIN0,PIN_IN);          //RX--->>>TX FOR BLUETOOTH MODULE
	DIO_SetPinDirection(PORTD,PIN1,PIN_OUT);         //TX--->>>RX FOR BLUETOOTH MODULE
	DIO_SetPinDirection(PORTB,PIN3,PIN_OUT);         //TIMER0-->>PWM-->>LEFT
	DIO_SetPinDirection(PORTD,PIN7,PIN_OUT);         //TIMER2-->>PWM-->>RIGHT
	//LEFT MOTOR ON ENABLE A
	//RIGHT MOTOR ON ENABLE B
	DIO_SetPinDirection(PORTB,PIN4,PIN_OUT);         //INT1-->>CONTROL DIRECTION OF MOTOR
	DIO_SetPinDirection(PORTB,PIN5,PIN_OUT);         //INT2-->>CONTROL DIRECTION OF MOTOR
	DIO_SetPinDirection(PORTB,PIN6,PIN_OUT);         //INT3-->>CONTROL DIRECTION OF MOTOR
	DIO_SetPinDirection(PORTB,PIN7,PIN_OUT);         //INT4-->>CONTROL DIRECTION OF MOTOR

	UART_Init();
	TIMER0_Init();
	TIMER0_SetFastPWM_Mode(NON_INV_MODE);
	TIMER2_Init_FastPWM();
	GI_Enable();
	Ultrasonic_Init();

	u8 Motion='S';

	while(1)
	{

		if (UART_DataAvailable())
		{
			u8 Data = UART_Receive();
			timeout_counter = 0;

			// Switch Mode
			if (Data == 'K' || Data == 'P')
			{
				Mode = Data;
				LCD_UpdateFlag = 1;   // to update LCD
				continue;
			}

			if (Data >= '0' && Data <= '9')
			{
				u8 Speed = Data - '0';
				PWM = Mapping(0, 9, 0, 255, Speed);
				if (PWM > 255) PWM = 255;
			}
			else
			{
				if (Motion != Data)
				{
					Motion = Data;
					LCD_UpdateFlag = 1;
				}
			}
		}
		else
		{
			_delay_ms(1);
			timeout_counter++;
		}

		if (timeout_counter > UART_TIMEOUT)
		{
			// stop only if moving and timeout happens
			if (Motion == 'S')
			{
				//				Stop();
				Motion = 'S';
				LCD_UpdateFlag = 1;
			}
		}

		if (Mode == 'K')
		{
			// RC Mode
			switch (Motion)
			{
			case 'F':
				//MOVE FORWARD
				TIMER0_SetCompareValue(PWM);                  //LEFT PWM
				TIMER2_SetCompareValue(PWM);                  //RIGHT PWM
				Move_Forward();
				break;

			case 'I':
				//MOVE FORWARDRIGHT
				TIMER0_SetCompareValue(PWM);                  //LEFT PWM
				TIMER2_SetCompareValue((PWM*3)/5);            //RIGHT PWM-->>60%
				Move_ForwardRight();
				break;

			case 'G':
				//MOVE FORWARDLEFT
				TIMER0_SetCompareValue((PWM*3)/5);                  //LEFT PWM
				TIMER2_SetCompareValue(PWM);                  //RIGHT PWM
				Move_ForwardLeft();
				break;

			case 'B':
				//MOVE BACK
				TIMER0_SetCompareValue(PWM);                  //LEFT PWM
				TIMER2_SetCompareValue(PWM);                  //RIGHT PWM
				Move_Back();
				break;

			case 'J':
				//MOVE BACKRIGHT
				TIMER0_SetCompareValue(PWM);                  //LEFT PWM
				TIMER2_SetCompareValue((PWM*3)/5);                  //RIGHT PWM
				Move_BackRight();
				break;

			case 'H':
				//MOVE BACKLEFT
				TIMER0_SetCompareValue((PWM*3)/5);                  //LEFT PWM
				TIMER2_SetCompareValue(PWM);                  //RIGHT PWM
				Move_BackLeft();
				break;

			case 'R':
				//MOVE RIGHT
				TIMER0_SetCompareValue(PWM);                  //LEFT PWM
				TIMER2_SetCompareValue(PWM);                  //RIGHT PWM
				Move_Right();
				break;

			case 'L':
				//MOVE LEFT
				TIMER0_SetCompareValue((PWM*2)/5);            //LEFT PWM-->>40%
				TIMER2_SetCompareValue(PWM);                  //RIGHT PWM
				Move_Left();
				break;

			case 'S':
				//STOP
				TIMER0_SetCompareValue(0);                  //LEFT PWM
				TIMER2_SetCompareValue(0);                  //RIGHT PWM
				Stop();
				break;

			default:
				break;
			}
		}
		else if(Mode == 'P')
		{
			// AUTO MODE
			AutoMode();
		}
		if (LCD_UpdateFlag)
		{
			LCD_ShowMotion(Motion);
			LCD_UpdateFlag = 0;
		}

	}

	return 0;
}

//======================== RC MODE ========================//

void Move_Forward()
{
	DIO_SetPinValue(PORTB,PIN4,PIN_LOW);          //INT1
	DIO_SetPinValue(PORTB,PIN5,PIN_HIGH);         //INT2
	DIO_SetPinValue(PORTB,PIN6,PIN_LOW);          //INT3
	DIO_SetPinValue(PORTB,PIN7,PIN_HIGH);         //INT4
}

void Move_ForwardRight()
{
	DIO_SetPinValue(PORTB,PIN4,PIN_LOW);          //INT1
	DIO_SetPinValue(PORTB,PIN5,PIN_HIGH);         //INT2
	DIO_SetPinValue(PORTB,PIN6,PIN_LOW);          //INT3
	DIO_SetPinValue(PORTB,PIN7,PIN_HIGH);         //INT4
}

void Move_ForwardLeft()
{
	DIO_SetPinValue(PORTB,PIN4,PIN_LOW);          //INT1
	DIO_SetPinValue(PORTB,PIN5,PIN_HIGH);         //INT2
	DIO_SetPinValue(PORTB,PIN6,PIN_LOW);          //INT3
	DIO_SetPinValue(PORTB,PIN7,PIN_HIGH);         //INT4
}

void Move_Back()
{
	DIO_SetPinValue(PORTB,PIN4,PIN_HIGH);         //INT1
	DIO_SetPinValue(PORTB,PIN5,PIN_LOW);          //INT2
	DIO_SetPinValue(PORTB,PIN6,PIN_HIGH);         //INT3
	DIO_SetPinValue(PORTB,PIN7,PIN_LOW);          //INT4
}

void Move_BackRight()
{
	DIO_SetPinValue(PORTB,PIN4,PIN_HIGH);         //INT1
	DIO_SetPinValue(PORTB,PIN5,PIN_LOW);          //INT2
	DIO_SetPinValue(PORTB,PIN6,PIN_HIGH);         //INT3
	DIO_SetPinValue(PORTB,PIN7,PIN_LOW);          //INT4
}

void Move_BackLeft()
{
	DIO_SetPinValue(PORTB,PIN4,PIN_HIGH);         //INT1
	DIO_SetPinValue(PORTB,PIN5,PIN_LOW);          //INT2
	DIO_SetPinValue(PORTB,PIN6,PIN_HIGH);         //INT3
	DIO_SetPinValue(PORTB,PIN7,PIN_LOW);          //INT4
}

void Move_Right()
{
	DIO_SetPinValue(PORTB,PIN4,PIN_LOW);          //INT1
	DIO_SetPinValue(PORTB,PIN5,PIN_HIGH);         //INT2
	DIO_SetPinValue(PORTB,PIN6,PIN_LOW);          //INT3
	DIO_SetPinValue(PORTB,PIN7,PIN_LOW);         //INT4
}

void Move_Left()
{
	DIO_SetPinValue(PORTB,PIN4,PIN_LOW);          //INT1
	DIO_SetPinValue(PORTB,PIN5,PIN_LOW);         //INT2
	DIO_SetPinValue(PORTB,PIN6,PIN_LOW);          //INT3
	DIO_SetPinValue(PORTB,PIN7,PIN_HIGH);         //INT4
}

void Stop()
{
	DIO_SetPinValue(PORTB,PIN4,PIN_LOW);          //INT1
	DIO_SetPinValue(PORTB,PIN5,PIN_LOW);          //INT2
	DIO_SetPinValue(PORTB,PIN6,PIN_LOW);          //INT3
	DIO_SetPinValue(PORTB,PIN7,PIN_LOW);          //INT4
}

void LCD_ShowMotion(u8 motion)
{
	LCD_ClearDisplay();
	LCD_SetPosition(0,0);

	if (Mode == 'K')
		LCD_SendString("Mode: RC");
	else
		LCD_SendString("Mode: AUTO");

	LCD_SetPosition(1,0);

	if (Mode == 'P')
	{
		LCD_SendString("Auto Driving");
		return;
	}

	if (motion == 'S')
	{
		LCD_SendString("Car Stop");
		return;
	}

	LCD_SendString("Car Move");

	LCD_SetPosition(1,0);
	switch(motion)
	{
	case 'F': LCD_SendString("Forward"); break;
	case 'B': LCD_SendString("Back"); break;
	case 'L': LCD_SendString("Left"); break;
	case 'R': LCD_SendString("Right"); break;
	case 'I': LCD_SendString("ForwardRight"); break;
	case 'G': LCD_SendString("ForwardLeft"); break;
	case 'J': LCD_SendString("BackRight"); break;
	case 'H': LCD_SendString("BackLeft"); break;
	default:  LCD_SendString("Unknown"); break;
	}
}

//======================== AUTO MODE ========================//

void Ultrasonic_Init(void)
{
	// TRIG as output
	DIO_SetPinDirection(PORTD, TRIG_PIN, PIN_OUT);

	// ECHO (ICP1) as input
	DIO_SetPinDirection(PORTD, ECHO_PIN, PIN_IN);

	TIMER1_Init_Ultrasonic();
}

u16 Ultrasonic_Read(void)
{
	u32 sum = 0;
	u8 valid_samples = 0;

	for(u8 i=0; i<3; i++)
	{ // Taking 3 samples for speed
		flag = 0;
		TCNT1 = 0;
		SET_BIT(TIFR,TIFR_ICF1);  // Clear ICF1 Flag
		SET_BIT(TCCR1B, TCCR1B_ICES1);     // Trigger on Rising edge

		// Send Trigger Pulse
		DIO_SetPinValue(PORTD, TRIG_PIN, PIN_HIGH);
		_delay_us(10);
		DIO_SetPinValue(PORTD, TRIG_PIN, PIN_LOW);

		// Timeout Protection (approx 40ms)
		u32 counter = 0;
		while(flag < 2 && TCNT1 < 40000);

		if(flag == 2)
		{
			u16 time = t2 - t1;
			sum += (time / 58);
			valid_samples++;
		}
		_delay_ms(15);
	}
	return (valid_samples > 0) ? (u16)(sum / valid_samples) : 999;
}

void AutoMode(void)
{
	u16 dist = Ultrasonic_Read();

	if (dist < 20)
	{
		Stop();
		_delay_ms(200);

		Move_Right();
		_delay_ms(300);

		Stop();
		_delay_ms(200);
	}
	else
	{
		TIMER0_SetCompareValue(200);
		TIMER2_SetCompareValue(200);
		Move_Forward();
	}
}

void __vector_6(void) __attribute__((signal));
void __vector_6(void)
{
	if(flag == 0)
	{
		t1 = ICR1;
		CLR_BIT(TCCR1B, TCCR1B_ICES1);   // falling edge
		flag = 1;
	}
	else if(flag == 1)
	{
		t2 = ICR1;
		SET_BIT(TCCR1B, TCCR1B_ICES1);   // back to rising
		flag = 2;
	}
}
