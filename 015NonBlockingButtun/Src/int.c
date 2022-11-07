/*
 * int.c
 *
 *  Created on: Nov 5, 2022
 *      Author: andre
 */

#include <stdint.h>

#include "int.h"

void HardFault_Handler()
{

	// If you are here an error occurs
	// Check the call stack
	// Check exception faults

	// Error loop

	while(1);

}

void SysTick_Handler(void)
{

	SysTick_CallBack();

}
