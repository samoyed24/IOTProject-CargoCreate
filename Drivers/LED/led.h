/*
 * led.h
 *
 *  Created on: Mar 12, 2025
 *      Author: 16018
 */

#ifndef LED_LED_H_
#define LED_LED_H_

#include "main.h"

void LED_Red(uint8_t status);
void LED_Yellow(uint8_t status);
void LED_Green(uint8_t status);
void LED_ClearAll();
void LED_Red_On();
void LED_Yellow_On();
void LED_Green_On();
void LED_CheckAndChange(uint8_t work, uint8_t waiting);

#endif /* LED_LED_H_ */
