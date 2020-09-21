#include "timer.h"
#include "stm32f10x.h"
#include "led.h"
void TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision=0;//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//TIM���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_Period=arr;//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //ʹ��ָ����TIM3�ж�,��������ж�
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;//TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//IRQͨ����ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;//�����ȼ�3��
	
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM3,ENABLE);

}
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)	//���TIM3�����жϷ������
	{
		LED1=!LED1;
		
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//���TIMx�����жϱ�־ 
	}
	
}
