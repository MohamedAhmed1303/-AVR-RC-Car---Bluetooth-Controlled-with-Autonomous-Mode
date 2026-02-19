/*
 * WDT_private.h
 *
 *  Created on: Jan 5, 2026
 *      Author: Mohamed
 */

#ifndef WDT_PRIVATE_H_
#define WDT_PRIVATE_H_

#define WDTCR                     *((volatile u8*)0X41)
#define WDTCR_WDE                 3
#define WDTCR_WDP2                2
#define WDTCR_WDP1                1
#define WDTCR_WDP0                0



#endif /* WDT_PRIVATE_H_ */
