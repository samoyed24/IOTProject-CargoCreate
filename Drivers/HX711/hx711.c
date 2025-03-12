/************************************************************************************

*************************************************************************************/
#include "HX711.h"

uint32_t HX711_Buffer;
uint32_t Weight_Maopi;
uint32_t Weight_Shiwu;
uint32_t Flag_Error = 0;


//卡尔曼滤波
float KalmanFilter(float inData)
{
		static float prevData = 0;                                 //先前数值
		static float p = 10, q = 0.001, r = 0.001, kGain = 0;      // q控制误差  r控制响应速度

		p = p + q;
		kGain = p / ( p + r );                                     //计算卡尔曼增益
		inData = prevData + ( kGain * ( inData - prevData ) );     //计算本次滤波估计值
		p = ( 1 - kGain ) * p;                                     //更新测量方差
		prevData = inData;
		return inData;                                             //返回滤波值
}


//校准参数
//因为不同的传感器特性曲线不是很一致，因此，每一个传感器需要矫正这里这个参数才能使测量值很准确。
//当发现测试出来的重量偏大时，增加该数值。
//如果测试出来的重量偏小时，减小改数值。
//该值可以为小数
#define GapValue 410




//****************************************************
//读取HX711
//****************************************************
uint32_t HX711_Read(uint8_t pulse)	//增益128  PULSE 脉冲
{
	uint32_t count =0;
	uint8_t i;
  HX720_CLK_L();

  if(HAL_GPIO_ReadPin(DAT_GPIO_Port, DAT_Pin)==0)
	{
		  for(i=0;i<24;i++)
			{
					HX720_CLK_H();
//					HAL_Delay(1);
					count=count<<1;
					HX720_CLK_L();
//					HAL_Delay(1);
					if(HAL_GPIO_ReadPin(DAT_GPIO_Port,DAT_Pin)==1)
					{
						count++;
					}

			}
			for(i=0;i<pulse-24;i++)
			{
				HX720_CLK_H();
//				HAL_Delay(1);
				HX720_CLK_L();
//				HAL_Delay(1);
			}

		count=count^0x800000;//第25个脉冲下降沿来时，转换数据

	}
//		HX720_CLK_H();
//    count=count^0x800000;//第25个脉冲下降沿来时，转换数据
//	delay_us(1);
//	HX720_CLK_H();
	return(count);
}

//****************************************************
//获取毛皮重量
//****************************************************
void Get_Maopi(void)
{
	HAL_Delay(500);
	Weight_Maopi = HX711_Read(25);
//	Weight_Maopi=KalmanFilter(Weight_Maopi);
}

//****************************************************
//称重
//****************************************************
void Get_Weight(void)
{
	HX711_Buffer = HX711_Read(25);
	if(HX711_Buffer > Weight_Maopi)
	{
		Weight_Shiwu = HX711_Buffer;
		Weight_Shiwu = Weight_Shiwu - Weight_Maopi;				//获取实物的AD采样数值。

		Weight_Shiwu = ((float)Weight_Shiwu/GapValue); 	//计算实物的实际重量
																		//因为不同的传感器特性曲线不一样，因此，每一个传感器需要矫正这里的GapValue这个除数。
																		//当发现测试出来的重量偏大时，增加该数值。
																		//如果测试出来的重量偏小时，减小改数值。
//		Weight_Shiwu=KalmanFilter(Weight_Shiwu);
	} else if (HX711_Buffer > 0) {
		Weight_Shiwu = 0;
	}

}
