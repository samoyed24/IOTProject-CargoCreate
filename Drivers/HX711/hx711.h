#ifndef __HX711_H
#define __HX711_H

#include "main.h"


#define CLK_GPIO_Port GPIOB
#define CLK_Pin GPIO_PIN_1

#define DAT_GPIO_Port GPIOB
#define DAT_Pin GPIO_PIN_0

#define HX720_CLK_H()   HAL_GPIO_WritePin(CLK_GPIO_Port,CLK_Pin,GPIO_PIN_SET) //时钟线置高电平
#define HX720_CLK_L()   HAL_GPIO_WritePin(CLK_GPIO_Port,CLK_Pin,GPIO_PIN_RESET)//时钟线置低电平


extern uint32_t HX711_Read(uint8_t pulse);
extern void Get_Maopi(void);
extern void Get_Weight(void);

extern uint32_t HX711_Buffer;
extern uint32_t Weight_Maopi;
extern uint32_t Weight_Shiwu;
extern uint32_t Flag_Error;

#endif
