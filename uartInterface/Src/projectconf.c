/*
 * projectconf.c
 *
 *  Created on: Nov 5, 2022
 *      Author: andre
 */

#include <stdint.h>

#include "projectconf.h"
#include "ports.h"


uint32_t SysTickCountMs = 0;


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
	// 1ms

	uint32_t reload = 16000 - 1; // 16Mhz [system clock] * 1ms [Systick exception]

	uint32_t *pSysTickRVR = (uint32_t *)0xE000E014U;

	*pSysTickRVR &= ~(0x00FFFFFF); // Clear
	*pSysTickRVR |= (reload); // Set

}


void port_Init(void)
{

	// GPIOA
	//
	// PIN_2 -> USART_2 TX
	// PIN_3 -> USART_2 RX

	// Enable clock GPIOA

	uint32_t *RCCBaseAddr = (uint32_t *)0x40023800U;

	uint32_t *pRCCAHB1ENR = (uint32_t *)( (uint32_t)RCCBaseAddr + (uint32_t)0x30U );

	*pRCCAHB1ENR |= (1 << 0);


	uint32_t *pGPIOABaseAddr = (uint32_t *)0x40020000U;

	// PIN_2 configuration

	// MODER

	uint32_t *pGPIOMODER = (uint32_t *)( (uint32_t)pGPIOABaseAddr + (uint32_t)0x00U );

	*pGPIOMODER |= ( 0x2 << (2 * 2) ); // GPIOA_2 alternate mode

	// OSPEED

	uint32_t *pGPIOOSPEED = (uint32_t *)( (uint32_t)pGPIOABaseAddr + (uint32_t)0x08U );

	*pGPIOOSPEED |= ( 0x3 << ( 2 * 2 ) ); // GPIOA_2 ospeed

	// AFRL

	uint32_t *pGPIOAFRL = (uint32_t *)( (uint32_t)pGPIOABaseAddr + (uint32_t)0x20U );

	*pGPIOAFRL |= ( 0x7 << (2 * 4) ); // GPIOA_2 AF7 -> USART_2 TX

	// PIN_3 configuration

	// MODER

	*pGPIOMODER |= ( 0x2 << (3 * 2) ); // GPIOA_3 alternate mode

	// OSPEED

	*pGPIOOSPEED |= ( 0x3 << ( 3 * 2 ) ); // GPIOA_3 ospeed

	// AFRL

	*pGPIOAFRL |= ( 0x7 << (3 * 4) ); // GPIOA_3 AF7 -> USART_2 RX

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
