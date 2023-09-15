/*
 * projectconf.h
 *
 *  Created on: Nov 5, 2022
 *      Author: andre
 */

#ifndef PROJECTCONF_H_
#define PROJECTCONF_H_

#define BUTTON_PORT					0x40020400U // GPIOB address
#define LED_PORT					0x40020400U // GPIOB address
#define BUTTON_PIN					0x00000008U
#define LED_PIN						0x00000009U

void System_Config(void);

extern uint32_t SysTickCountMs;

#endif /* PROJECTCONF_H_ */
