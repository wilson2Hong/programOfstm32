#include "adc.h"
#include "delay.h"
#include "lcd.h"	
#include "led.h"
#include "stm32f10x.h"
uint16_t ADCConvertedValue;
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	//PA1 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //��λADC1 

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_239Cycles5);//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	
	
  ADC_ITConfig(ADC1,ADC_IT_EOC,ENABLE);//ʹ��ADC1��ADC_IT_EOC��־λ
  
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼   
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	ADC_StartCalibration(ADC1);	 //����ADУ׼
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE); //�������ADCת��
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel=ADC1_2_IRQn;//????ADCI��ADC2���ж�
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	
	NVIC_Init(&NVIC_InitStructure);

}				  


//��һ�� ADCת��������ADC�����жϣ���ȡADC_DR�Ĵ����е�ֵ��������жϱ�־λ��
void ADC1_2_IRQHandler(void)
{
	if(ADC_GetITStatus(ADC1,ADC_IT_EOC)==SET)
	{
	   
	  ADCConvertedValue=ADC_GetConversionValue(ADC1);
		ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
  }
	
	//delay_ms(250);��ʵ����Ļ���ŵ�Ч��
	//��ȡADCת����ֵ
	ADC_SoftwareStartConvCmd(ADC1,ENABLE); //�������ADCת��
} 

