/*
 * systemfunctions.c
 *
 *  Created on: Nov 5, 2022
 *      Author: andre
 */

#include <stdint.h>

#include "systemfunctions.h"
#include "projectconf.h"

/*
*
* Get SysTicCount
*
*/
uint32_t Get_SystemTimeUs(void)
{

	return SysTickCountUs;

}


/*
*
* Compare captured value with actual
*
*/
uint32_t Compare_SystemTimeUs(uint32_t capturedTimeUs)
{

	uint32_t ret = 0;

	if(SysTickCountUs >= capturedTimeUs)
		ret = SysTickCountUs - capturedTimeUs;
	else
		ret = capturedTimeUs - SysTickCountUs;

	return ret;

}
