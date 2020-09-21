#include "timer.h"
#include "led.h"
#include "usart.h"

void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����
   
}

//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		LED1=!LED1;
		}
}


void TIM3_PWM_Init(u16 arr,u16 psc,u16 CCR1_Val,u16 CCR2_Val,u16 CCR3_Val,u16 CCR4_Val)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʹ�ܶ�ʱ��3ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB,ENABLE);//ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	
	
	
	//���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.5
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//�����������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_0|GPIO_Pin_1; //TIM_CH1 TIM_CH2 TIM_CH3 TIM_CH4
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);//��ʼ��GPIO
 
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);//Timer3������ӳ�� TIM3_CH1->PB4 TIM3_CH2->PB5 TIM3_CH0->PB0  TIM3_CH4->PB1 
	//��ʼ��TIM3
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; //����ʱ�ӷ�Ƶϵ��������Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInitStructure.TIM_Period = arr;//��ʱ����������  0~arr
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;//����Ԥ��Ƶϵ����psc=0 ��Ԥ��Ƶ Ĭ��TIMxClock=72MHz
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
		//��ʼ��TIM3 Channel1 PWMģʽ	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//���PWM1ģʽ  ����TIMx_CNTֵ��Ч
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse=CCR1_Val;
	
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);//ʹ��ͨ��1
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
		//��ʼ��TIM3 Channel2 PWMģʽ	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//PMW1  С����Ч   pwm2������Ч
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse=CCR2_Val;
	
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);//ʹ��ͨ��3
	
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
		//��ʼ��TIM3 Channel3 PWMģʽ	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse=CCR3_Val;
	
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);//ʹ��ͨ��3
	
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	//��ʼ��TIM3 Channel4 PWMģʽ	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse=CCR4_Val;
	
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);//ʹ��ͨ��4
	
	/*��������¼�����ʱTIM_CCRx��ֵ����Ĵ����� ����CCMR1��OC2PE ��־ 
	0:��ֹTIMx_CCR1��Ԥװ�ڹ��ܣ�����ʱд��TIMx_CCR1�Ĵ�������д�����ֵ����������
	1�����TIMx_CCR1�Ĵ�����Ԥװ�ع��ܣ���д����������װ�ؼĴ���������TIMx_CCR1��Ԥװ��ֵ�ڸ����¼�����ʱ����������ǰ�Ĵ���
	*/
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);// 
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);//�����ڶ�ʱ��������������ARR��д����ֵ
	
	TIM_Cmd(TIM3,ENABLE);//ʹ�ܶ�ʱ��3

}
