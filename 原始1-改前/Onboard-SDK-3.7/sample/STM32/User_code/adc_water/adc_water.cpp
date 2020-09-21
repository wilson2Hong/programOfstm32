#include "adc_water.hpp"	 
#include <sys.h>	
#include "stm32f4xx_adc.h"
#include "timer.h"
#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

//初始化ADC															   
void  Adc_Init(void)
{    
  GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOB时钟
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOC时钟
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //使能ADC1时钟

  //先初始化ADC1通道5 IO口
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;//PA4 PA5  ADC1_IN4 ADC1_IN5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//数字输入
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//下拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化  
 
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;//PB0 PB1  ADC1_IN8 ADC1_IN9
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
//  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化 
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;//PC0 PC1  ADC1_IN10 ADC1_IN11
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
//  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化 
//	
//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1复位
//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//复位结束	 
// 
//	
//  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
//  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
//  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA失能
//  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
//  ADC_CommonInit(&ADC_CommonInitStructure);//初始化
//	
//  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12位模式
//  ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式	
//  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//关闭连续转换
//  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
//  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
//  ADC_InitStructure.ADC_NbrOfConversion = 1;//1个转换在规则序列中 也就是只转换规则序列1 
//  ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化
//	
// 
//	ADC_Cmd(ADC1, ENABLE);//开启AD转换器	

}				  
//获得ADC值
//ch: @ref ADC_channels 
//通道值 0~16取值范围为：ADC_Channel_0~ADC_Channel_16
//返回值:转换结果
//u16 Get_Adc(u8 ch)   
//{
//	  	//设置指定ADC的规则组通道，一个序列，采样时间
//	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
//  
//	ADC_SoftwareStartConv(ADC1);		//使能指定的ADC1的软件转换启动功能	
//	 
//	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

//	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
//}
//获取通道ch的转换值，取times次,然后平均 
//ch:通道编号
//times:获取次数
//返回值:通道ch的times次转换结果平均值
//u16 Get_Adc_Average(u8 ch,u8 times)
//{
//	u32 temp_val=0;
//	u8 t;
//	for(t=0;t<times;t++)
//	{
//		temp_val+=Get_Adc(ch);
//	//	delay_nms(1);
//	}
//	return temp_val/times;
//} 

u16 Water_sensor_1;//PA4 -> ADC1_IN4
u16 Water_sensor_2;//PA5 -> ADC1_IN5
u16 Water_sensor_3;//PB0 -> ADC1_IN8
u16 Water_sensor_4;//PB1 -> ADC1_IN9
u16 Water_sensor_5;//PC0 -> ADC1_IN10
u16 Water_sensor_6;//PC1 -> ADC1_IN11

bool Falling_water_detection()//落水检测 数值大于2000时水位传感器一定落在水中
{
		Water_sensor_1=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4);
//	Water_sensor_2=Get_Adc_Average(ADC_Channel_5,5);
//	Water_sensor_3=Get_Adc_Average(ADC_Channel_8,5);
//	Water_sensor_4=Get_Adc_Average(ADC_Channel_9,5);
//	Water_sensor_5=Get_Adc_Average(ADC_Channel_10,5);
//	Water_sensor_6=Get_Adc_Average(ADC_Channel_11,5);
	
		
		
	if(Water_sensor_1 == 1)
	{
		printf(" 飞机:落水 ");
		return true;
	}
//	else if(Water_sensor_2>2000)
//	{
//		return true;
//	}
//	else if(Water_sensor_3>2000)
//	{
//		return true;
//	}
//	else if(Water_sensor_4>2000)
//	{
//		return true;
//	}
//	else if(Water_sensor_5>2000)
//	{
//		return true;
//	}
//	else if(Water_sensor_6>2000)
//	{
//		return true;
//	}
	else
		{
		printf(" 飞机:未落水 ");
		return false;
		}
	
}


#ifdef __cplusplus
}
#endif //__cplusplus


//		adcx=Get_Adc_Average(ADC_Channel_4,20);//获取通道5的转换值，20次取平均
//		temp=(float)adcx*(3.3/4096);          //获取计算后的带小数的实际电压值，比如3.1111//		




