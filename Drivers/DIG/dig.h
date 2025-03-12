/*
 * dig.h
 *
 *  Created on: Feb 6, 2025
 *      Author: 16018
 */

#ifndef DIG_DIG_H_
#define DIG_DIG_H_

#include "main.h"

#define DIG_GPIO GPIOB

#define GPIO_PIN_RESET RESET
#define GPIO_PIN_SET SET

#define DIG_DIN GPIO_PIN_7
#define DIG_CS GPIO_PIN_6		// 片选信号低电平触发
#define DIG_CLK GPIO_PIN_5

#define DIG0_Register  0x01//选位0寄存器
#define DIG1_Register  0x02//选位1寄存器
#define DIG2_Register  0x03//选位2寄存器
#define DIG3_Register  0x04//选位3寄存器
#define DIG4_Register  0x05//选位4寄存器
#define DIG5_Register  0x06//选位5寄存器
#define DIG6_Register  0x07//选位6寄存器
#define DIG7_Register  0x08//选位7寄存器

#define DECODE_MODE   0x09//译码模式寄存器
//0x00：7-0不采用译码
//0x01：0采用BCD译码，7-1不采用
//0x0F：3-0采用BCD译码，7-4不采用
//0xFF：7-0采用BCD译码
//当选择BCD译码模式时，译码器只对数据的低四位进行译码（D3-D0），D4-D6为无效位。D7位用来设置小数点，不受译码器的控制且为高电平。
//当选择不译码时，数据的八位与MAX7219的各段线上的信号一致。

#define INTENSITY    0x0A//亮度寄存器
//亮度等级设置 0x00-0x0F 设置电流为最大电流的 1/32 - 31/32（间隔2/32）
//也可以通过硬件来改变，修改V+和ISET之间的电阻阻值大小，最小阻值为9.53kΩ，它设定段电流为40mA。

#define SCAN_LIMIT   0x0B//扫描寄存器
//0x00：只显示数字0
//0x01：显示数字0&1
//0x02：显示数字0，1，2
//0x03：显示数字0，1，2，3
//0x04：显示数字0，1，2，3，4
//0x05：显示数字0，1，2，3，4，5
//0x06：显示数字0，1，2，3，4，5，6
//0x07：显示数字0，1，2，3，4，5，6，7

#define SHUTDOWN 0x0C//掉电寄存器
//0x00：掉电模式
//0x01：正常模式

#define DISPLAY_TEST  0x0F//显示测试寄存器
//0x00：正常模式
//0x01：显示测试模式

typedef struct {
	uint8_t tempIsPositive;
	uint8_t temp[3];
	uint8_t humid[4];
} DIG_TempHumidStruct;


uint8_t DIG_Init();
void DIG_ShowWeight(uint32_t weight);

#endif /* DIG_DIG_H_ */
