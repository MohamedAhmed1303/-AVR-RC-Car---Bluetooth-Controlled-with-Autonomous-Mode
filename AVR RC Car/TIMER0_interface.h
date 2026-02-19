/*
 * TIMER_interface.h
 *
 *  Created on: Nov 20, 2025
 *      Author: Mohamed
 */

#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

#define INV_MODE          1
#define NON_INV_MODE      2

void TIMER0_Init();
void TIMER0_SetPreload(u8 NumberOfTicks);
void TIMER0_SetCompareValue(u8 NumberOfTicks);
void TIMER0_SetCallBackOVF(void(*PtrFunc)(void));
void TIMER0_SetCallBackCTC(void(*PtrFunc)(void));
void TIMER0_SetFastPWM_Mode(u8 Mode);

#endif /* TIMER0_INTERFACE_H_ */
