/*
 * Gl_program.c
 *
 *  Created on: Oct 3, 2025
 *      Author: Mohamed
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GI_interface.h"
#include "GI_private.h"

void GI_Enable()
{
	SET_BIT(SREG,SREG_I);
}

void GI_Disable()
{
	CLR_BIT(SREG,SREG_I);
}

