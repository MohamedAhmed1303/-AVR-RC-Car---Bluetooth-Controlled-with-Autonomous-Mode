/*
 * DIO_interface.h
 *
 *  Created on: Sep 5, 2025
 *      Author: Mohamed
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


/*********** TO CONTROL COMPLETE PORT ***********/
void DIO_SetPortDirection(u8 PortNum , u8 PortDirection);
void DIO_SetPortValue(u8 PortNum , u8 PortValue);

/*********** TO CONTROL COMPLETE ONE PIN ***********/
void DIO_SetPinDirection(u8 PortNum ,u8 PinNum, u8 PinDirection);
void DIO_SetPinValue(u8 PortNum ,u8 PinNum, u8 PinValue);

/*********** TO GET ONE PIN VALUE ***********/
u8 DIO_GetPinValue(u8 PortNum ,u8 PinNum);

/*********** TO SELECT CERTAIN PORT ***********/
#define PORTA     1
#define PORTB     2
#define PORTC     3
#define PORTD     4

/*********** TO SELECT CERTAIN PIN ***********/
#define PIN0      0
#define PIN1      1
#define PIN2      2
#define PIN3      3
#define PIN4      4
#define PIN5      5
#define PIN6      6
#define PIN7      7

/*********** TO SET PIN DIRECTION ***********/
#define PIN_IN    0
#define PIN_OUT   1

/*********** TO SET PIN VALUE ***********/
#define PIN_LOW   0
#define PIN_HIGH  1

u32 Mapping(u32 R1_max,u32 R1_min,u32 R2_max,u32 R2_min,u32 R1_reading);

#endif /* DIO_INTERFACE_H_ */
