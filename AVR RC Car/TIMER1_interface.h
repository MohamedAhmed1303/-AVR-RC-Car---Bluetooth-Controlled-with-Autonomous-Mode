/*
 * TIMER1_interface.h
 *
 *  Created on: Dec 2, 2025
 *      Author: Mohamed
 */

#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_
#include "STD_TYPES.h"


void TIMER1_Init();
void TIMER1_Init_Ultrasonic();
void TIMER1_SetICRValue(u16 NumberOfTicks);
void TIMER1_SetCompareValue(u16 NumberOfTicks);


#endif /* TIMER1_INTERFACE_H_ */
