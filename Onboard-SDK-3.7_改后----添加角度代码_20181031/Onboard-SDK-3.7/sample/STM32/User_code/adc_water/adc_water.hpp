#ifndef __ADC_WATER_H
#define __ADC_WATER_H	
#include "sys.h" 
#include "stm32f4xx_adc.h" 

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
void Adc_Init(void); 								//ADC通道初始化
u16  Get_Adc(u8 ch); 								//获得某个通道值 
u16 Get_Adc_Average(u8 ch,u8 times);//得到某个通道给定次数采样的平均值  
bool Falling_water_detection();			//落水检测
bool Propeller_channel_detection();	//推进器控制信号检测
#endif 

#ifdef __cplusplus
}
#endif //__cplusplus











