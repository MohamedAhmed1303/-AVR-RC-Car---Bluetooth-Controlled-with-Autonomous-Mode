/*
 * UART_interface.h
 *
 *  Created on: Dec 15, 2025
 *      Author: Mohamed
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void UART_Init();
void UART_SendByte(u8 Data);
u8 UART_Receive();
u16 UART_ReceiveNumber();
u8 UART_Receive_NoBlock(u8 *Data);
u8 UART_DataAvailable(void);

#endif /* UART_INTERFACE_H_ */
