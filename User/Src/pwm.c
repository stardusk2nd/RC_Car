/*
 * pwm.c
 *
 *  Created on: Jul 31, 2024
 *      Author: Stardust
 */

#include "pwm.h"

bool switching = false;

void pwm_start(){
    HAL_TIM_PWM_Start_IT(&htim4, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start_IT(&htim4, TIM_CHANNEL_2);
}

void control_motors(uint16_t x, uint16_t y){

	if(power_on){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		// -512 ~ 511의 범위로 조정
		int16_t signed_x = x - 512;

//		// y값 반전
//		y = 1023 - y;

		// -512 ~ 511의 범위로 조정
		int16_t signed_y = y - 512;

		// channel 1(PB6) - left
		// channel 2(PB7) - right
		int16_t right_motor_speed = signed_y + signed_x;
		int16_t left_motor_speed = signed_y - signed_x;

		// absolute value
		uint16_t abs_left = abs(left_motor_speed);
		uint16_t abs_right = abs(right_motor_speed);

//		abs_left = abs_left * 999 / 512;
//		abs_right = abs_right * 999 / 512;

		if(left_motor_speed >= 0){
			HAL_GPIO_WritePin(DIR_L_WHEEL_PORT1, DIR_L_WHEEL_PIN1, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DIR_L_WHEEL_PORT2, DIR_L_WHEEL_PIN2, GPIO_PIN_RESET);
		}
		else{
			HAL_GPIO_WritePin(DIR_L_WHEEL_PORT1, DIR_L_WHEEL_PIN1, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DIR_L_WHEEL_PORT2, DIR_L_WHEEL_PIN2, GPIO_PIN_SET);
		}
		if(right_motor_speed >= 0){
			HAL_GPIO_WritePin(DIR_R_WHEEL_PORT1, DIR_R_WHEEL_PIN1, GPIO_PIN_SET);
			HAL_GPIO_WritePin(DIR_R_WHEEL_PORT2, DIR_R_WHEEL_PIN2, GPIO_PIN_RESET);
		}
		else{
			HAL_GPIO_WritePin(DIR_R_WHEEL_PORT1, DIR_R_WHEEL_PIN1, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DIR_R_WHEEL_PORT2, DIR_R_WHEEL_PIN2, GPIO_PIN_SET);
		}

		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, abs_left);
		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, abs_right);
	}

	else{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		stop_motors();
	}

}

void stop_motors(){
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 0);
	HAL_GPIO_WritePin(DIR_L_WHEEL_PORT1, DIR_L_WHEEL_PIN1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DIR_L_WHEEL_PORT2, DIR_L_WHEEL_PIN2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DIR_R_WHEEL_PORT1, DIR_R_WHEEL_PIN1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DIR_R_WHEEL_PORT2, DIR_R_WHEEL_PIN2, GPIO_PIN_RESET);
}
