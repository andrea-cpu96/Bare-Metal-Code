/*
 * uart.c
 *
 *  Created on: 17 nov 2022
 *      Author: andre
 */


#include <stdint.h>

#include "uart.h"


/********************************************** Blocking communication mode **********************************************/

void uart_Init(uartHandler_t *huart)
{

	/* Baud rate configuration BRR */

	// BR = 115200 = fck / ( 16 * USARTDIV )
	// USARTDIV = fck / ( 16 * 9600 ) = 8.68
	// DIV_FRACTION = 16 * 0.68 = 11 = 0xB
	// DIV_MANTISSA = 8 = 0x08
	// USART_BRR = 0x08B

	huart->uart_Istance->uart_brr = 0x08BU; // 115200 baud rate


	/* Control register configuration CR1 */

	// word length

	huart->uart_Istance->uart_cr1 &= ~( 1 << 12 ); // 8 bits of data

	// uart enable

	huart->uart_Istance->uart_cr1 |= ( 1 << 13 ); // uart enabled

	// receiver enable

	huart->uart_Istance->uart_cr1 |= ( 1 << 2 ); // RE

	// transmission enable

	huart->uart_Istance->uart_cr1 |= ( 1 << 3 ); // TE


	/* Control register configuration CR2 */

	// stop bits

	huart->uart_Istance->uart_cr2 &= ~( 0x3 << 12 );


}


void uart_MultiByte_Tx(uartHandler_t *huart, uint8_t *dataBuff, uint32_t length)
{

	for(int i = 0 ; i < length ; i++)
		uart_SingleByte_Tx(huart, dataBuff[i]);

}

void uart_SingleByte_Tx(uartHandler_t *huart, uint8_t data)
{

	// Wait TXE

	while(! ( huart->uart_Istance->uart_sr & ( 1 << 7  ) ) );

	// Write the data into the data register

	huart->uart_Istance->uart_dr  = data;

	// Wait until the transmission completes

	while( ! ( huart->uart_Istance->uart_sr & ( 1 << 6  ) ) ); // TC == 1

}


void uart_MultiByte_Rx(uartHandler_t *huart, uint8_t *dataBuff, uint32_t length)
{

	for(int i = 0 ; i < length ; i++)
		uart_SingleByte_Rx(huart, &dataBuff[i]);

}

void uart_SingleByte_Rx(uartHandler_t *huart, uint8_t *data)
{

	// Wait until the data register is not empty

	while( ! ( huart->uart_Istance->uart_sr & ( 1 << 5  ) ) ); // RXNE == 1

	// Read data from data register

	*data = huart->uart_Istance->uart_dr;


}


/********************************************** Interrupt communication mode **********************************************/

void uart_Init_It(uartHandler_t *huart)
{


	/* Baud rate configuration BRR */

	// BR = 115200 = fck / ( 16 * USARTDIV )
	// USARTDIV = fck / ( 16 * 9600 ) = 8.68
	// DIV_FRACTION = 16 * 0.68 = 11 = 0xB
	// DIV_MANTISSA = 8 = 0x08
	// USART_BRR = 0x08B

	huart->uart_Istance->uart_brr = 0x08BU; // 115200 baud rate


	/* Control register configuration CR1 */

	// word length

	huart->uart_Istance->uart_cr1 &= ~( 1 << 12 ); // 8 bits of data

	// uart enable

	huart->uart_Istance->uart_cr1 |= ( 1 << 13 ); // uart enabled

	// receiver enable

	huart->uart_Istance->uart_cr1 |= ( 1 << 2 ); // RE

	// transmission enable

	huart->uart_Istance->uart_cr1 |= ( 1 << 3 ); // TE

	// IDLE interrupt enable

	//huart->uart_Istance->uart_cr1 |= ( 1 << 4 ); // IDLEEI

	// PE interrupt enable

	//huart->uart_Istance->uart_cr1 |= ( 1 << 8 ); // PEIE


	/* Control register configuration CR2 */

	// stop bits

	huart->uart_Istance->uart_cr2 &= ~( 0x3 << 12 );


}


void uart_Start_Tx_It(uartHandler_t *huart, uint8_t *dataBuff, uint32_t length)
{

	if(huart->uart_TxState != UART_BUSY_IN_TX)
	{

		huart->uart_TxState = UART_BUSY_IN_TX;
		huart->uart_dataBuffTx = dataBuff;
		huart->uart_IndexTx = 0;
		huart->uart_ContTx = length;

		// TC interrupt enable

		huart->uart_Istance->uart_cr1 |= ( 1 << 6 ); // TCIE

		// TXE interrupt enable

		huart->uart_Istance->uart_cr1 |= ( 1 << 7 ); // TXEIE

	}

}

void uart_Start_Rx_It(uartHandler_t *huart, uint8_t *dataBuff, uint32_t length)
{

	if(huart->uart_RxState != UART_BUSY_IN_RX)
	{

		huart->uart_RxState = UART_BUSY_IN_RX;
		huart->uart_dataBuffRx = dataBuff;
		huart->uart_IndexRx = 0;
		huart->uart_ContRx = length;

		// RXNE interrupt enable

		huart->uart_Istance->uart_cr1 |= ( 1 << 5 ); // RXNEIE

	}

}

void uart_End_Rx_It(uartHandler_t *huart)
{


	huart->uart_RxState = UART_READY;
	huart->uart_IndexRx = 0;
	huart->uart_ContRx = 0;

	// RXNE interrupt disable

	huart->uart_Istance->uart_cr1 &= ~( 1 << 5 ); // RXNEIE

}

void Uart_IRQHandler(uartHandler_t *huart)
{

	uint32_t temp1;


	/*************************Check for TC flag ********************************************/

	temp1 = ( huart->uart_Istance->uart_sr & ( 1 << 6 ) );

	if(temp1)
	{

		// Interrupt due to TC flag

		if(huart->uart_TxState == UART_BUSY_IN_TX)
		{

			if(huart->uart_ContTx == 0)
			{

				// Close the transmission

				// Clear the TC flag (otherwise it remains 1)
				huart->uart_Istance->uart_sr &= ~( 1 << 6 );

				//Reset the application state
				huart->uart_TxState = UART_READY;

				//Reset Buffer address to NULL
				//huart->uart_dataBuffTx = NULL;

				//Reset the length to zero
				huart->uart_ContTx = 0;

				//Implement the code to clear the TCIE bit (disable interrupt for TC flag )
				huart->uart_Istance->uart_cr1 &= ~( 1 << 6 );

				//Call the application call back with event USART_EVENT_TX_CMPLT
				USART_ApplicationEventCallback(huart, USART_EVENT_TX_CMPLT);

			}

		}

	}

	/*************************Check for TXE flag ********************************************/

	//Implement the code to check the state of TXE bit in the SR
	temp1 = huart->uart_Istance->uart_sr & ( 1 << 7 );

	if(temp1)
	{

		//this interrupt is because of TXE

		if(huart->uart_TxState == UART_BUSY_IN_TX)
		{
			//Keep sending data until Txlen reaches to zero
			if(huart->uart_ContTx > 0)
			{

					//This is 8bit data transfer
					huart->uart_Istance->uart_dr = ( huart->uart_dataBuffTx[huart->uart_IndexTx] );

					//Implement the code to increment the buffer address
					huart->uart_IndexTx++;
					huart->uart_ContTx -= 1;

			}

			if (huart->uart_ContTx == 0 )
			{
				//TxLen is zero
				//Implement the code to clear the TXEIE bit (disable interrupt for TXE flag )
				huart->uart_Istance->uart_cr1 &= ~( 1 << 7 );
			}
		}
	}

	/*************************Check for RXNE flag ********************************************/

	temp1 = huart->uart_Istance->uart_sr & ( 1 << 5 );

	if(temp1)
	{

		//this interrupt is because of rxne

		if(huart->uart_RxState == UART_BUSY_IN_RX)
		{
			if(huart->uart_ContRx > 0)
			{

				//We are going to receive 8bit data in a frame

				//read 8 bits from DR
				huart->uart_dataBuffRx[huart->uart_IndexRx] = (uint8_t)( huart->uart_Istance->uart_dr );

				//Now , increment the pRxBuffer
				huart->uart_IndexRx++;
				huart->uart_ContRx -= 1;

			}

			if(!huart->uart_ContRx )
			{
				//disable the rxne
				huart->uart_Istance->uart_cr1 &= ~( 1 << 5 );
				huart->uart_RxState = UART_READY;
				USART_ApplicationEventCallback(huart, USART_EVENT_RX_CMPLT);
			}
		}
	}

}





