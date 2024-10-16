/*
 * pwm.h
 *
 *  Created on: Jul 31, 2024
 *      Author: Stardust
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

#include "top.h"

#define DIR_L_WHEEL_PORT1	GPIOB
#define DIR_L_WHEEL_PIN1	GPIO_PIN_4
#define DIR_L_WHEEL_PORT2	GPIOB
#define DIR_L_WHEEL_PIN2	GPIO_PIN_5

#define DIR_R_WHEEL_PORT1	GPIOB
#define DIR_R_WHEEL_PIN1	GPIO_PIN_3
#define DIR_R_WHEEL_PORT2	GPIOB
#define DIR_R_WHEEL_PIN2	GPIO_PIN_10

void pwm_start();
void control_motors(uint16_t x, uint16_t y);
void stop_motors();

extern TIM_HandleTypeDef htim4;
extern uint8_t power_on;

#endif /* INC_PWM_H_ */
