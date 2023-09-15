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

	peripherals_Init();

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
	// PIN_9 -> USART_1 TX
	// PIN_10 -> USART_1 RX
	//
	// PIN_2 -> USART_2 TX
	// PIN_3 -> USART_3 RX
	//

	// Enable clock GPIOA

	uint32_t *RCCBaseAddr = (uint32_t *)0x40023800U;

	uint32_t *pRCCAHB1ENR = (uint32_t *)( (uint32_t)RCCBaseAddr + (uint32_t)0x30U );

	*pRCCAHB1ENR |= (1 << 0);


	uint32_t *pGPIOABaseAddr = (uint32_t *)0x40020000U;

	// PIN_9 configuration

	// MODER

	uint32_t *pGPIOMODER = (uint32_t *)( (uint32_t)pGPIOABaseAddr + (uint32_t)0x00U );

	*pGPIOMODER |= ( 0x2 << (9 * 2) ); // GPIOA_9 alternate mode

	// OSPEED

	uint32_t *pGPIOOSPEED = (uint32_t *)( (uint32_t)pGPIOABaseAddr + (uint32_t)0x08U );

	*pGPIOOSPEED |= ( 0x3 << ( 9 * 2 ) ); // GPIOA_9 ospeed


	// PUDN
/*
	uint32_t *pGPIOPUDN = (uint32_t *)( (uint32_t)pGPIOABaseAddr + (uint32_t)0x0CU );

	*pGPIOPUDN |= ( 0x1 << ( 9 * 2 ) ); // GPIOA_9 pudn
*/
	// AFRH

	uint32_t *pGPIOAFRH = (uint32_t *)( (uint32_t)pGPIOABaseAddr + (uint32_t)0x24U );

	*pGPIOAFRH |= ( 0x7 << (1 * 4) ); // GPIOA_9 AF7 -> USART_1


	//

	// PIN_10 configuration

	// MODER

	*pGPIOMODER |= ( 0x2 << (10 * 2) ); // GPIOA_10 alternate mode

	// OSPEED

	*pGPIOOSPEED |= ( 0x3 << ( 10 * 2 ) ); // GPIOA_10 ospeed
/*
	// PUDN

	*pGPIOPUDN |= ( 0x1 << ( 10 * 2 ) ); // GPIOA_10 pudn
*/
	// AFRL

	*pGPIOAFRH |= ( 0x7 << (2 * 4) ); // GPIOA_10 AF7 -> USART_1 RX



	// PIN_2 configuration

	// MODER

	*pGPIOMODER |= ( 0x2 << (2 * 2) ); // GPIOA_2 alternate mode

	// OSPEED

	*pGPIOOSPEED |= ( 0x3 << ( 2 * 2 ) ); // GPIOA_2 ospeed
/*
	// PUDN

	*pGPIOPUDN |= ( 0x1 << ( 2 * 2 ) ); // GPIOA_2 pudn
*/
	// AFRL

	uint32_t *pGPIOAFRL = (uint32_t *)( (uint32_t)pGPIOABaseAddr + (uint32_t)0x20U );

	*pGPIOAFRL |= ( 0x7 << (2 * 4) ); // GPIOA_2 AF7 -> USART_2 RX


	// PIN_3 configuration

	// MODER

	*pGPIOMODER |= ( 0x2 << (3 * 2) ); // GPIOA_3 alternate mode

	// OSPEED

	*pGPIOOSPEED |= ( 0x3 << ( 3 * 2 ) ); // GPIOA_3 ospeed
/*
	// PUDN

	*pGPIOPUDN |= ( 0x1 << ( 3 * 2 ) ); // GPIOA_3 pudn
*/
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

void peripherals_Init(void)
{

	// fck -> 16 MHz


	/* UART_1 and UART_2 */


	// Enable clock for

	uint32_t *pRccBaseAddr = (uint32_t *)0x40023800U;

	uint32_t *pRccAPB1 = (uint32_t *)( (uint32_t)pRccBaseAddr + 0x40U );
	uint32_t *pRccAPB2 = (uint32_t *)( (uint32_t)pRccBaseAddr + 0x44U );

	*pRccAPB1 |= ( 1 << 17 );
	*pRccAPB2 |= ( 1 << 4 );


	// Enable interrupt

	// UART1_IRQ -> 37
	// UART2_IRQ -> 38

	uint32_t *pNvicIserBaseAddr  = (uint32_t *)0xE000E100U;
	uint32_t *pNvicIser1 = (uint32_t *)( (uint32_t)pNvicIserBaseAddr + (uint32_t)0x04U );

	*pNvicIser1 |= ( 1 << 5 ); // Enable interrupt for UART1
	*pNvicIser1 |= ( 1 << 6 ); // Enable interrupt for UART2

	// Set the interrupt priority for UART1

	uint32_t *pNvicIprBaseAddr = (uint32_t *)0xE000E400U;
	uint32_t *pNvicIpr9 = (uint32_t *)( (uint32_t)pNvicIprBaseAddr + (uint32_t)0x24U );

	*pNvicIpr9 |= ( 0x3 << ( ( 8 * 1 ) + 4 )); // Priority for UART_1 set to 3
	*pNvicIpr9 |= ( 0x3 << ( ( 8 * 2 ) + 4 )); // Priority for UART_2 set to 3


}
