/*
 * onewire.c
 *
 *  Created on: Nov 11, 2022
 *      Author: andre
 */

#include <stdint.h>

#include "projectconf.h"
#include "systemfunctions.h"
#include "ports.h"

uint32_t timeStampAM2302 = 0;

void start(void)
{

	uint32_t *pGPIOMODER = (uint32_t *)0x40023800U;

	// set as an Output

	*pGPIOMODER |= ( 0x1 << (8 * 2) ); // GPIOB_8 output mode


	Port_Pin_Toggle(DATA_PORT, DATA_PIN);

	timeStampAM2302 = Get_SystemTimeUs();

	while(Compare_SystemTimeUs(timeStampAM2302) < 200); // 2Ms delay

	Port_Pin_Toggle(DATA_PORT, DATA_PIN);

	// set as an input

	*pGPIOMODER &= ~( 0x00 << (8 * 2) ); // GPIOB_8 input mode

}


