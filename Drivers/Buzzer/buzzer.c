/*
 * buzzer.c
 *
 *  Created on: Sep 24, 2024
 *      Author: 16018
 */
#include "stdlib.h"
#include "stdint.h"
#include "buzzer.h"


void BUZZER_SHORT(uint32_t buzz_time_ms) {
	uint32_t startTime = HAL_GetTick();
	HAL_GPIO_WritePin(BUZ_SGN_GPIO_Port, BUZ_SGN_Pin, GPIO_PIN_RESET);
	while (HAL_GetTick() - startTime < buzz_time_ms);
	HAL_GPIO_WritePin(BUZ_SGN_GPIO_Port, BUZ_SGN_Pin, GPIO_PIN_SET);
}

void BUZZER_BUZZ_TWICE(uint32_t buzz_time_ms, uint32_t mid_time_ms) {
	BUZZER_SHORT(buzz_time_ms);
	uint32_t startTime = HAL_GetTick();
	while (HAL_GetTick() - startTime < mid_time_ms);
	BUZZER_SHORT(buzz_time_ms);
}

void BUZZER_Success() {
	BUZZER_BUZZ_TWICE(50, 50);
}

void BUZZER_Fail() {
	BUZZER_BUZZ_TWICE(200, 200);
}
