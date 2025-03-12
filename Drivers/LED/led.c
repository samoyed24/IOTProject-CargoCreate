/*
 * led.c
 *
 *  Created on: Mar 12, 2025
 *      Author: 16018
 */

#include "led.h"

GPIO_PinState state[2] = {
		GPIO_PIN_RESET,
		GPIO_PIN_SET
};

void LED_Red(uint8_t status) {
	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, state[status]);
}

void LED_Yellow(uint8_t status) {
	HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, state[status]);
}

void LED_Green(uint8_t status) {
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, state[status]);
}

void LED_ClearAll() {
	LED_Red(0);
	LED_Yellow(0);
	LED_Green(0);
}

void LED_Red_On() {
	LED_ClearAll();
	LED_Red(1);
}

void LED_Yellow_On() {
	LED_ClearAll();
	LED_Yellow(1);
}

void LED_Green_On() {
	LED_ClearAll();
	LED_Green(1);
}

void LED_CheckAndChange(uint8_t work, uint8_t waiting) {
	if (!work) LED_Red_On();
	else {
		if (waiting) LED_Yellow_On();
		else LED_Green_On();
	}
}
