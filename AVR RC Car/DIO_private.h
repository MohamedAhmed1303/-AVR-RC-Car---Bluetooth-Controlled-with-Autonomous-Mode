/*
 * DIO_private.h
 *
 *  Created on: Sep 5, 2025
 *      Author: Mohamed
 */

#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_


#define PORTA_reg    *((volatile u8*)0X3B)
#define DDRA_reg     *((volatile u8*)0X3A)
#define PINA_reg     *((volatile u8*)0X39)
/*************************************/
#define PORTB_reg    *((volatile u8*)0X38)
#define DDRB_reg     *((volatile u8*)0X37)
#define PINB_reg     *((volatile u8*)0X36)
/*************************************/
#define PORTC_reg    *((volatile u8*)0X35)
#define DDRC_reg     *((volatile u8*)0X34)
#define PINC_reg     *((volatile u8*)0X33)
/*************************************/
#define PORTD_reg    *((volatile u8*)0X32)
#define DDRD_reg     *((volatile u8*)0X31)
#define PIND_reg    *((volatile u8*)0X30)



#endif /* DIO_PRIVATE_H_ */
