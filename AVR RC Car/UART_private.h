/*
 * UART_private.h
 *
 *  Created on: Dec 15, 2025
 *      Author: Mohamed
 */


#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#define UDR                *((volatile u8*)0X2C)

#define UCSRA              *((volatile u8*)0X2B)
#define UCSRA_RXC          7
#define UCSRA_UDRE         5

#define UCSRB              *((volatile u8*)0X2A)
#define UCSRB_RXEN         4
#define UCSRB_TXEN         3
#define UCSRB_UCSZ2        2

#define UCSRC              *((volatile u8*)0X40)

#define UBRRL              *((volatile u8*)0X29)


#endif /* UART_PRIVATE_H_ */
