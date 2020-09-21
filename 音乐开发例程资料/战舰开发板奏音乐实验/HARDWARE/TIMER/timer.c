#include "timer.h"

//TIM2 PWM????? 
//PWM?????
//arr:?????
//psc:??????
void TIM4_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;						//��һ��IO����
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	//��һ����ʱ������
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ��TIM2
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//ʹ��PWM����˿�
 
  //����PWM����˿ڣ�TIM4 CH3 PWM  GPIOB.8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM2_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);		//����
// 	
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //����
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);		//����
// //	GPIO_ResetBits(GPIOA,GPIO_Pin_2);					//��ʼ��Ϊ�ͣ�ʹ����Ƶ
// 	GPIO_SetBits(GPIOA,GPIO_Pin_2);
//  
  //����TIM4
	TIM_TimeBaseStructure.TIM_Period = arr; //��������
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //��Ƶϵ��
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM2���ϼ���
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //��������
	 
	//???TIM4 Channel3 PWM??	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;	//TIM_OCMode_PWM2; //TIM_OCMode_Toggle�ڱȽϳɹ���ת��Ӧ����ܽŵĵ�ƽ
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //??????
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //????:TIM???????
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //??T??????????TIM2 OC4

	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //??TIM3?CCR2????????
 
//	TIM_Cmd(TIM4, ENABLE);  //??TIM2
}


