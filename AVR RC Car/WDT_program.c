/*
 * WDT_program.c
 *
 *  Created on: Jan 5, 2026
 *      Author: Mohamed
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "WDT_interface.h"
#include "WDT_private.h"

void WDT_Enable()
{
	//ENABLE
	SET_BIT(WDTCR,WDTCR_WDE);
	//PERSCALER ->DEPEND ON WDT TABLE 1SEC
	WDTCR=0B00001110;
}

void WDT_Disable()
{
	//DISABLE
	WDTCR |= 0B00011000;
	WDTCR = 0B00000000;
}
