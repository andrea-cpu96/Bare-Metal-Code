/*
 * main.h
 *
 *  Created on: Nov 5, 2022
 *      Author: andre
 */

#ifndef MAIN_H_
#define MAIN_H_


#define DEBOUNCING_DELAY		200


typedef enum
{

	IDLE,
	BUTTON_PRESSED,
	BUTTON_RELEASED,

}buttonState_t;

#endif /* MAIN_H_ */
