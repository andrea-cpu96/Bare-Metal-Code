/*
 * ports.c
 *
 *  Created on: Nov 5, 2022
 *      Author: andre
 */


#include <stdint.h>

#include "ports.h"



uint8_t Get_Port_Pin_State(uint32_t port, uint8_t pin)
{

	uint8_t ret = 0;

	// Read IDR

	uint32_t *pGPIOXIDR = (uint32_t *)( (uint32_t)port + (uint32_t)0x10 );

	ret = ( ( *pGPIOXIDR  & (1 << pin) ) > 0 ) ? 1 : 0;

	return ret;

}


void Port_Pin_Toggle(uint32_t port, uint8_t pin)
{

	uint8_t pinState = 0;

	// Write ODR

	uint32_t *pGPIOXODR = (uint32_t *)( (uint32_t)port + (uint32_t)0x14 );

	pinState = ( *pGPIOXODR & (1 << pin) ) > 0 ? 1 : 0;

	if(pinState == 0)
		*pGPIOXODR |= ( 1 << pin );
	else
		*pGPIOXODR &= ~( 1 << pin );

}


