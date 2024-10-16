/*
 * delay.h
 *
 *  Created on: Jul 31, 2024
 *      Author: Stardust
 */

#ifndef INC_DELAY_H_
#define INC_DELAY_H_

#include "top.h"
#include "pwm.h"
#include "uart.h"

extern volatile uint32_t lastTick;
extern uint16_t adcValue[2];

void motor_delayed();

#endif /* INC_DELAY_H_ */
