/*
 * int.c
 *
 *  Created on: Nov 5, 2022
 *      Author: andre
 */


#include <stdint.h>

#include "uart.h"
#include "main.h"

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


void USART1_IRQHandler(void)
{

	Uart_IRQHandler(&huart1);

}

void USART2_IRQHandler(void)
{

	Uart_IRQHandler(&huart2);

}

void WWDG_IRQHandler(void)
{

	while(1);

}

void UsageFault_Handler(void)
{

	while(1);

}
