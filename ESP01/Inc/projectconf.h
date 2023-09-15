/*
 * projectconf.h
 *
 *  Created on: Nov 5, 2022
 *      Author: andre
 */

#ifndef PROJECTCONF_H_
#define PROJECTCONF_H_

#define DATA_PORT					0x40020400U // GPIOB address
#define DATA_PIN					0x00000008U

void System_Config(void);
void peripherals_Init(void);

extern uint32_t SysTickCountMs;

#endif /* PROJECTCONF_H_ */
