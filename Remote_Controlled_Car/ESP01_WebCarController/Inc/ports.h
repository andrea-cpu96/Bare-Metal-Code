/*
 * ports.h
 *
 *  Created on: Nov 5, 2022
 *      Author: andre
 */

#ifndef PORTS_H_
#define PORTS_H_

uint8_t Get_Port_Pin_State(uint32_t port, uint8_t pin);
void Port_Pin_Toggle(uint32_t port, uint8_t pin);

#endif /* PORTS_H_ */
