/*
 * UART_program.c
 *
 *  Created on: Dec 15, 2025
 *      Author: Mohamed
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "UART_config.h"
#include "UART_interface.h"
#include "UART_private.h"


void UART_Init()
{
	//UCSRC -> WRITE IN ONE OPERATION
	//OPTIONS -> TO OPERATE
	//CHARA SIZE -> 8 BIT
	//NO PARITY
	//1 STOP BIT
	//SPEED (BAUD RATE) 9600
	//FULL DUPLEX -> TX_ENABLE,RX_ENABLE
	SET_BIT(UCSRB,UCSRB_RXEN);
	SET_BIT(UCSRB,UCSRB_TXEN);
	CLR_BIT(UCSRB,UCSRB_UCSZ2);

	UCSRC=0B10000110;

	UBRRL=51;
}

void UART_SendByte(u8 Data)
{
	//SEND -> UDR =1;
	while(GET_BIT(UCSRA,UCSRA_UDRE)==0);
	UDR=Data;
}

u8 UART_Receive()
{
	while(GET_BIT(UCSRA,UCSRA_RXC)==0);
	return UDR;
}

u8 UART_Receive_NoBlock(u8 *Data)
{
	if (GET_BIT(UCSRA, UCSRA_RXC))
	{
		*Data = UDR;
		return 1;   // data received
	}
	return 0;       // no data
}


u16 UART_ReceiveNumber()
{
    u16 num = 0;
    u8 received;

    while(1)
    {
        received = UART_Receive();
        if(received >= '0' && received <= '9')
        {
            num = num*10 + (received - '0');
        }
        else
        {
            break;
        }
    }
    return num;
}

u8 UART_DataAvailable(void)
{
    if (UCSRA & (1 << UCSRA_RXC))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

