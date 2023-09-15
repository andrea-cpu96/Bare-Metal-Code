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
uint32_t Get_SystemTimeMs(void)
{

	return SysTickCountMs;

}


/*
*
* Compare captured value with actual
*
*/
uint32_t Compare_SystemTimeMs(uint32_t capturedTimeMs)
{

	uint32_t ret = 0;

	if(SysTickCountMs >= capturedTimeMs)
		ret = SysTickCountMs - capturedTimeMs;
	else
		ret = capturedTimeMs - SysTickCountMs;

	return ret;

}
