/*
 * uart.h
 *
 *  Created on: 17 nov 2022
 *      Author: andre
 */

#ifndef UART_H_
#define UART_H_


#define UART_1_BASE_ADDR			0x40011000U
#define UART_2_BASE_ADDR			0x40004400U


typedef struct uart2Reg
{

	uint32_t uart_sr;
	uint32_t uart_dr;
	uint32_t uart_brr;
	uint32_t uart_cr1;
	uint32_t uart_cr2;
	uint32_t uart_cr3;
	uint32_t uart_gtpr;

}uart2Reg_t;


typedef struct uartHandler
{

	uart2Reg_t *uart_Istance;

	uint8_t *uart_dataBuffTx;
	uint32_t uart_IndexTx;
	uint32_t uart_ContTx;

	uint8_t *uart_dataBuffRx;
	uint32_t uart_IndexRx;
	uint32_t uart_ContRx;

	uint8_t uart_TxState;
	uint8_t uart_RxState;

}uartHandler_t;


#define UART_1 					 (uart2Reg_t *)UART_1_BASE_ADDR;
#define UART_2	                 (uart2Reg_t *)UART_2_BASE_ADDR;


enum uartState
{

	UART_READY = 0,
	UART_BUSY_IN_TX = 1,
	UART_BUSY_IN_RX = 2

};


#define 	USART_EVENT_TX_CMPLT   0
#define		USART_EVENT_RX_CMPLT   1
#define		USART_EVENT_IDLE       2
#define		USART_EVENT_CTS        3
#define		USART_EVENT_PE         4
#define		USART_ERR_FE     	   5
#define		USART_ERR_NE    	   6
#define		USART_ERR_ORE    	   7

/* Blocking mode */

void uart_Init(uartHandler_t *huart);

void uart_MultiByte_Tx(uartHandler_t *huart, uint8_t *dataBuff, uint32_t length);
void uart_SingleByte_Tx(uartHandler_t *huart, uint8_t data);

void uart_MultiByte_Rx(uartHandler_t *huart, uint8_t *dataBuff, uint32_t length);
void uart_SingleByte_Rx(uartHandler_t *huart, uint8_t *data);


/* Interrupt mode */

void uart_Init_It(uartHandler_t *huart);

void uart_Start_Tx_It(uartHandler_t *huart, uint8_t *dataBuff, uint32_t length);
void uart_Start_Rx_It(uartHandler_t *huart, uint8_t *dataBuff, uint32_t length);
void Uart_IRQHandler(uartHandler_t *huart);
extern void USART_ApplicationEventCallback(uartHandler_t *huart, uint8_t event);

void uart_End_Rx_It(uartHandler_t *huart);

#endif /* UART_H_ */
