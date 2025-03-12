/*
 * dig.c
 *
 *  Created on: Feb 6, 2025
 *      Author: 16018
 */
#include "dig.h"

#define DIG_CS_LOW HAL_GPIO_WritePin(DIG_GPIO, DIG_CS, RESET)
#define DIG_CS_HIGH HAL_GPIO_WritePin(DIG_GPIO, DIG_CS, SET)
#define DIG_CLK_LOW HAL_GPIO_WritePin(DIG_GPIO, DIG_CLK, RESET)
#define DIG_CLK_HIGH HAL_GPIO_WritePin(DIG_GPIO, DIG_CLK, SET)
#define DIG_DIN_LOW HAL_GPIO_WritePin(DIG_GPIO, DIG_DIN, RESET)
#define DIG_DIN_HIGH HAL_GPIO_WritePin(DIG_GPIO, DIG_DIN, SET)

#define DIG_NEGATIVE 0b00000001
#define DIG_NOTHING 0b00000000

uint8_t DIG_Arr[8] = {
		DIG7_Register,
		DIG6_Register,
		DIG5_Register,
		DIG4_Register,
		DIG3_Register,
		DIG2_Register,
		DIG1_Register,
		DIG0_Register,
}; // 数码管从高位到低位的数组...


uint8_t DIG_Number[10] = {
		0b01111110,
		0b00110000,
		0b01101101,
		0b01111001,
		0b00110011,
		0b01011011,
		0b01011111,
		0b01110000,
		0b01111111,
		0b01111011,
};

uint8_t DIG_NumberPoint[10] = {
		0b11111110,
		0b10110000,
		0b11101101,
		0b11111001,
		0b10110011,
		0b11011011,
		0b11011111,
		0b11110000,
		0b11111111,
		0b11111001,
};

/*******************************************************************************
 * 函数名：DIG_Write_Data
 * 描述  ：向Max7219写入数据
 * 输入  ：addr地址，dat数据
 * 输出  ：void
 * 调用  ：内部调用
 * 备注  ：
*******************************************************************************/
void DIG_Write_Data(uint8_t addr,uint8_t dat)
{
	uint8_t i;

	DIG_CLK_LOW;
	DIG_CS_LOW;//拉低CS,选中器件

	//发送地址
	for(i=0;i<8;i++)
	{
		  if(addr & 0x80)
			{
		    DIG_DIN_HIGH;
			}
			else
			{
		    DIG_DIN_LOW;
			}
		  //HAL_Delay(1);
			addr <<= 1;
			DIG_CLK_HIGH;
			  //HAL_Delay(1);
	        DIG_CLK_LOW;
			  //HAL_Delay(1);
	}

	//发送数据
	for(i=0;i<8;i++)
	{
		  if(dat & 0x80)
			{
		    DIG_DIN_HIGH;
			}
			else
			{
		    DIG_DIN_LOW;
			}
		  //HAL_Delay(1);
			dat <<= 1;
			DIG_CLK_HIGH;
			  //HAL_Delay(1);
	       DIG_CLK_LOW;
			  //HAL_Delay(1);
	}

	DIG_CS_HIGH;//发送结束,上升沿锁存数据
	DIG_CLK_LOW;
    DIG_DIN_LOW;
}

void DIG_Show(uint8_t something[]) {
	for (uint8_t i = 0; i < 8; ++i) {
		DIG_Write_Data(DIG_Arr[i], something[i]);
	}
}

void DIG_DisableDisplay() {
	uint8_t NullReg[] = {
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
			0x00,
	};
	DIG_Show(NullReg);
}

void DIG_ShowNull() {
	uint8_t NullReg[] = {
			0b01110110,
			0b00111110,
			0b00001110,
			0b00001110,
			0x00,
			0x00,
			0x00,
			0x00,
	};
	DIG_Show(NullReg);
}

void DIG_ShowWeight(uint32_t weight) {
	char formatWeight[9];
	sprintf(formatWeight, "%08u", weight);
	uint8_t length = 8, i = 0;
	while (i < 8) {
		if (formatWeight[i] != '0') break;
		length--;
		i++;
	}
	uint8_t thisReg[8];
	thisReg[0] = length >= 8 ? DIG_Number[formatWeight[0] - '0'] : DIG_NOTHING;
	thisReg[1] = length >= 7 ? DIG_Number[formatWeight[1] - '0'] : DIG_NOTHING;
	thisReg[2] = length >= 6 ? DIG_Number[formatWeight[2] - '0'] : DIG_NOTHING;
	thisReg[3] = length >= 5 ? DIG_Number[formatWeight[3] - '0'] : DIG_NOTHING;
	thisReg[4] = DIG_NumberPoint[formatWeight[4] - '0'];
	thisReg[5] = DIG_Number[formatWeight[5] - '0'];
	thisReg[6] = DIG_Number[formatWeight[6] - '0'];
	thisReg[7] = DIG_Number[formatWeight[7] - '0'];
	DIG_Show(thisReg);
}

uint8_t DIG_Init() {
	DIG_Write_Data(SHUTDOWN,0x01);//掉电模式：0;普通模式：1
	DIG_Write_Data(DISPLAY_TEST,0x00);//显示测试：1;测试结束，正常显示：0
    DIG_Write_Data(DECODE_MODE,0x00);//译码方式：非BCD译码
	DIG_Write_Data(SCAN_LIMIT,0x07);//扫描界限：8个数码管显示
	DIG_Write_Data(INTENSITY,0x0C);//亮度
	DIG_DisableDisplay();
	return 0;
}
