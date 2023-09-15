/*
 * projectconf.c
 *
 *  Created on: Nov 5, 2022
 *      Author: andre
 */

#include <stdint.h>

#include "projectconf.h"
#include "ports.h"


uint32_t SysTickCountUs = 0;


static void SysTick_Init(void);
static void port_Init(void);
static void systemClock_Init(void);


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

	systemClock_Init();

	SysTick_Init();

	port_Init();

}


void SysTick_Init(void)
{

	uint32_t *pSysTickCSR  = (uint32_t *)0xE000E010U;

	// [2] internal clock source ; [1] enable SysTick exception ; [0] enable counter

	*pSysTickCSR |= (7 << 0);

	// Reload value
	// 10us

	uint32_t reload = 160 - 1; // 16Mhz [system clock] * 10us [Systick exception]

	uint32_t *pSysTickRVR = (uint32_t *)0xE000E014U;

	*pSysTickRVR &= ~(0x00FFFFFF); // Clear
	*pSysTickRVR |= (reload); // Set

}


void port_Init(void)
{

	// GPIOB
	//
	// PIN_8 -> Output AM2302 sensor
	//

	// Enable clock

	uint32_t *RCCBaseAddr = (uint32_t *)0x40023800U;

	uint32_t *pRCCAHB1ENR = (uint32_t *)( (uint32_t)RCCBaseAddr + (uint32_t)0x30U );

	*pRCCAHB1ENR |= (1 << 1);

	// By default it is zero, we need to pull-up the port

	Port_Pin_Toggle(DATA_PORT, DATA_PIN);

	// PIN_8 configuration

	uint32_t *pGPIOBBaseAddr = (uint32_t *)0x40020400U;

	// MODER

	uint32_t *pGPIOMODER = (uint32_t *)( (uint32_t)pGPIOBBaseAddr + (uint32_t)0x00U );

	*pGPIOMODER |= ( 0x1 << (8 * 2) ); // GPIOB_8 output mode


	// OTYPER

	uint32_t *pGPIOOTYPER = (uint32_t *)( (uint32_t)pGPIOBBaseAddr + (uint32_t)0x04U );

	*pGPIOOTYPER |= ( 0x1 << 8 ); // GPIOB_8 open-drain


	// PULLUP

	uint32_t *pGPIOPUPDR = (uint32_t *)( (uint32_t)pGPIOBBaseAddr + (uint32_t)0x0CU );

	*pGPIOPUPDR |= ( 0x1 << (8 * 2) ); // GPIOB_8 PULL up

	// SPEED

	uint32_t *pGPIOOSPEEDR = (uint32_t *)( (uint32_t)pGPIOBBaseAddr + (uint32_t)0x08U );

	*pGPIOOSPEEDR |= ( 0x3 << (8 * 2) ); // GPIOB_8 speed

}


void systemClock_Init(void)
{

	/*
	// Enable PLL engine

	uint32_t *pRCCBaseAddr = (uint32_t *)0x40023800U;

	uint32_t *pRCCCR = (uint32_t *)( (uint32_t)pRCCBaseAddr + (uint32_t)0x00U );

	*pRCCCR |= ( 1 << 24 );

	// Select PLL as system clock

	uint32_t *pRCCCFGR = (uint32_t *)( (uint32_t)pRCCBaseAddr + (uint32_t)0x08U );

	*pRCCCFGR |= ( 0x02 << 2 );
	*/

}
