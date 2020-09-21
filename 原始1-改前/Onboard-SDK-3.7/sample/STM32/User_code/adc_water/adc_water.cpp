#include "adc_water.hpp"	 
#include <sys.h>	
#include "stm32f4xx_adc.h"
#include "timer.h"
#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

//��ʼ��ADC															   
void  Adc_Init(void)
{    
  GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOBʱ��
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOCʱ��
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //ʹ��ADC1ʱ��

  //�ȳ�ʼ��ADC1ͨ��5 IO��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;//PA4 PA5  ADC1_IN4 ADC1_IN5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��������
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��  
 
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;//PB0 PB1  ADC1_IN8 ADC1_IN9
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
//  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ�� 
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;//PC0 PC1  ADC1_IN10 ADC1_IN11
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
//  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ�� 
//	
//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1��λ
//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//��λ����	 
// 
//	
//  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
//  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ��
//  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMAʧ��
//  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz 
//  ADC_CommonInit(&ADC_CommonInitStructure);//��ʼ��
//	
//  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
//  ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ	
//  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//�ر�����ת��
//  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
//  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
//  ADC_InitStructure.ADC_NbrOfConversion = 1;//1��ת���ڹ��������� Ҳ����ֻת����������1 
//  ADC_Init(ADC1, &ADC_InitStructure);//ADC��ʼ��
//	
// 
//	ADC_Cmd(ADC1, ENABLE);//����ADת����	

}				  
//���ADCֵ
//ch: @ref ADC_channels 
//ͨ��ֵ 0~16ȡֵ��ΧΪ��ADC_Channel_0~ADC_Channel_16
//����ֵ:ת�����
//u16 Get_Adc(u8 ch)   
//{
//	  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
//	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
//  
//	ADC_SoftwareStartConv(ADC1);		//ʹ��ָ����ADC1�����ת����������	
//	 
//	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

//	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
//}
//��ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
//ch:ͨ�����
//times:��ȡ����
//����ֵ:ͨ��ch��times��ת�����ƽ��ֵ
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

bool Falling_water_detection()//��ˮ��� ��ֵ����2000ʱˮλ������һ������ˮ��
{
		Water_sensor_1=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4);
//	Water_sensor_2=Get_Adc_Average(ADC_Channel_5,5);
//	Water_sensor_3=Get_Adc_Average(ADC_Channel_8,5);
//	Water_sensor_4=Get_Adc_Average(ADC_Channel_9,5);
//	Water_sensor_5=Get_Adc_Average(ADC_Channel_10,5);
//	Water_sensor_6=Get_Adc_Average(ADC_Channel_11,5);
	
		
		
	if(Water_sensor_1 == 1)
	{
		printf(" �ɻ�:��ˮ ");
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
		printf(" �ɻ�:δ��ˮ ");
		return false;
		}
	
}


#ifdef __cplusplus
}
#endif //__cplusplus


//		adcx=Get_Adc_Average(ADC_Channel_4,20);//��ȡͨ��5��ת��ֵ��20��ȡƽ��
//		temp=(float)adcx*(3.3/4096);          //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111//		




