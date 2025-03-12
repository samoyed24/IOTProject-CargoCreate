/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RC522_SDA_Pin GPIO_PIN_4
#define RC522_SDA_GPIO_Port GPIOA
#define RC522_SCK_Pin GPIO_PIN_5
#define RC522_SCK_GPIO_Port GPIOA
#define RC522_MISO_Pin GPIO_PIN_6
#define RC522_MISO_GPIO_Port GPIOA
#define RC522_MOSI_Pin GPIO_PIN_7
#define RC522_MOSI_GPIO_Port GPIOA
#define HX_DAT_Pin GPIO_PIN_0
#define HX_DAT_GPIO_Port GPIOB
#define HX_SCK_Pin GPIO_PIN_1
#define HX_SCK_GPIO_Port GPIOB
#define RC522_RST_Pin GPIO_PIN_2
#define RC522_RST_GPIO_Port GPIOB
#define LED_GREEN_Pin GPIO_PIN_12
#define LED_GREEN_GPIO_Port GPIOB
#define LED_YELLOW_Pin GPIO_PIN_13
#define LED_YELLOW_GPIO_Port GPIOB
#define LED_RED_Pin GPIO_PIN_14
#define LED_RED_GPIO_Port GPIOB
#define ESP_RST_Pin GPIO_PIN_11
#define ESP_RST_GPIO_Port GPIOA
#define BUZ_SGN_Pin GPIO_PIN_4
#define BUZ_SGN_GPIO_Port GPIOB
#define DIG_CLK_Pin GPIO_PIN_5
#define DIG_CLK_GPIO_Port GPIOB
#define DIG_CS_Pin GPIO_PIN_6
#define DIG_CS_GPIO_Port GPIOB
#define DIG_DIN_Pin GPIO_PIN_7
#define DIG_DIN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
