/*
 * main.h
 *
 *  Created on: Nov 5, 2022
 *      Author: andre
 */

#ifndef MAIN_H_
#define MAIN_H_



#define	USER_SEND_TO_ESP01		1
#define	ESP01_SEND_TO_USER		0

#define STOP					'3'
#define GO_AHEAD				'1'
#define GO_BACK					'2'
#define TURN_RIGHT				'4'
#define TURN_LEFT				'5'
#define GARBAGE1				'\n'
#define GARBAGE2				'\r'

extern uartHandler_t huart1;
extern uartHandler_t huart2;

#endif /* MAIN_H_ */
