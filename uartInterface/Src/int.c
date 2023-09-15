/*
 * int.c
 *
 *  Created on: Nov 5, 2022
 *      Author: andre
 */

#include "int.h"
#include "main.h"

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


void USART2_IRQHandler(void)
{

	Uart_IRQHandler(&huart2);

}
