/*
 * delay.c
 *
 *  Created on: Jul 31, 2024
 *      Author: Stardust
 */

#include "delay.h"

volatile uint32_t lastTick = 0;

void motor_delayed(){
	uint32_t currentTick = HAL_GetTick();
	if(currentTick - lastTick >= 50){
		lastTick = currentTick;
		control_motors(adcValue[0], adcValue[1]);
	}
}
