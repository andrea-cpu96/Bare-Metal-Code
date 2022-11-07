/*
 * projectconf.c
 *
 *  Created on: Nov 5, 2022
 *      Author: andre
 */

#include <stdint.h>

#include "projectconf.h"


uint32_t SysTickCountMs = 0;


static void SysTick_Init(void);
static void port_Init(void);


/*
 * System configuration:
 *
 * system clock;
 * processor peripherals configuration;
 * port configurations;
 *
*/
void System_Config(void)
{

	SysTick_Init();

	port_Init();

}


void SysTick_Init(void)
{

	uint32_t *pSysTickCSR  = (uint32_t *)0xE000E010U;

	// [2] internal clock source ; [1] enable SysTick exception ; [0] enable counter

	*pSysTickCSR |= (7 << 0);

	// Reload value
	// 1ms

	uint32_t reload = 16000 - 1; // 16Mhz [system clock] * 1ms [Systick exception]

	uint32_t *pSysTickRVR = (uint32_t *)0xE000E014U;

	*pSysTickRVR &= ~(0x00FFFFFF); // Clear
	*pSysTickRVR |= (reload); // Set

}


void port_Init(void)
{

	// GPIOB
	//
	// PIN_8 -> Input button
	// PIN_9 -> Output LED
	//

	// Enable clock

	uint32_t *RCCBaseAddr = (uint32_t *)0x40023800U;

	uint32_t *pRCCAHB1ENR = (uint32_t *)( (uint32_t)RCCBaseAddr + (uint32_t)0x30U );

	*pRCCAHB1ENR |= (1 << 1);


	// PIN_8  and PIN_9 configuration

	uint32_t *pGPIOBBaseAddr = (uint32_t *)0x40020400U;

	// MODER

	uint32_t *pGPIOMODER = (uint32_t *)( (uint32_t)pGPIOBBaseAddr + (uint32_t)0x00U );

	*pGPIOMODER &= ~( 0x3 << (8 * 2) ); // GPIOB_8 input mode

	*pGPIOMODER |= ( 0x1 << (9 * 2) ); // GPIOB_9 output mode

	// PULLDOWN

	uint32_t *pGPIOPUPDR = (uint32_t *)( (uint32_t)pGPIOBBaseAddr + (uint32_t)0x0CU );

	*pGPIOPUPDR |= ( 0x2 << (8 * 2) ); // GPIOB_8 PULL DOWN

}
