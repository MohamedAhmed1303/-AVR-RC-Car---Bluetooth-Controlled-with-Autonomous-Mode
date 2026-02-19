/*
 * GI_interface.h
 *
 *  Created on: Oct 3, 2025
 *      Author: Mohamed
 */

#ifndef GI_INTERFACE_H_
#define GI_INTERFACE_H_

#define SREG               *((volatile u8*)0x5F)
#define SREG_I             7

void GI_Enable();
void GI_Disable();


#endif /* GI_INTERFACE_H_ */
