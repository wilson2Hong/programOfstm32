#ifndef __ADC_WATER_H
#define __ADC_WATER_H	
#include "sys.h" 
#include "stm32f4xx_adc.h" 

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
void Adc_Init(void); 								//ADCͨ����ʼ��
u16  Get_Adc(u8 ch); 								//���ĳ��ͨ��ֵ 
u16 Get_Adc_Average(u8 ch,u8 times);//�õ�ĳ��ͨ����������������ƽ��ֵ  
bool Falling_water_detection();			//��ˮ���
bool Propeller_channel_detection();	//�ƽ��������źż��
#endif 

#ifdef __cplusplus
}
#endif //__cplusplus











