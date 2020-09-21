#include "stm32f4xx.h"
#include "sys.h"
#include "esc_control.hpp"
#include "led.hpp"
#include "stm32f4xx_tim.h"
#include "main.h"
 
int CHANNEL_1_RISE=0,CHANNEL_1_FALL=0,CHANNEL_1_PULSE_WIDE=0;
int CHANNEL_2_RISE=0,CHANNEL_2_FALL=0,CHANNEL_2_PULSE_WIDE=0;
int CHANNEL_3_RISE=0,CHANNEL_3_FALL=0,CHANNEL_3_PULSE_WIDE=0;
int CHANNEL_4_RISE=0,CHANNEL_4_FALL=0,CHANNEL_4_PULSE_WIDE=0;
int ICFLAG_1 = 1,ICFLAG_2 = 1,ICFLAG_3 = 1,ICFLAG_4 = 1;

int CHANNEL_1_ESC_WIDE=940,CHANNEL_2_ESC_WIDE=940;
//TIM4 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM4_PWM_Init(u32 arr,u32 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM4ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//ʹ��PORTDʱ��	
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); //GPIOD12����Ϊ��ʱ��4
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4); //GPIOD13����Ϊ��ʱ��4
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4); //GPIOD14����Ϊ��ʱ��4
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4); //GPIOD15����Ϊ��ʱ��4
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;           //GPIOD_12 13 14 15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOD,&GPIO_InitStructure);              //��ʼ��PD12_13_14_15
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//��ʼ����ʱ��4
	
	//��ʼ��TIM4 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե� //TIM_OCPolarity_Low //TIM_OCPolarity_High
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 OC1
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 OC2
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 OC3
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 OC4
	
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR3�ϵ�Ԥװ�ؼĴ���
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR4�ϵ�Ԥװ�ؼĴ���
 
	
  TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM4
 
	TIM_SetCompare1(TIM4,940);
	TIM_SetCompare2(TIM4,940);
	TIM_SetCompare3(TIM4,0);
	TIM_SetCompare4(TIM4,0);
						  
}  

TIM_ICInitTypeDef  TIM3_ICInitStructure;

//��ʱ��3ͨ��1���벶������
//arr���Զ���װֵ(TIM2,TIM5��32λ��!!)
//psc��ʱ��Ԥ��Ƶ��
void TIM3_CH1_Cap_Init(u32 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM3ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//ʹ��PORTCʱ��	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //GPIOC6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //����
	GPIO_Init(GPIOC,&GPIO_InitStructure); //��ʼ��PA0

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3); //PC6����λ��ʱ��3  
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	

	//��ʼ��TIM3���벶�����
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM3_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  TIM_ICInit(TIM3, &TIM3_ICInitStructure);
		
//	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�	
	
  TIM_Cmd(TIM3,ENABLE ); 	//ʹ�ܶ�ʱ��3

 
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����	
}

void TIM3_CH2_Cap_Init(u32 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM3ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//ʹ��PORTCʱ��	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //GPIOC7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //����
	GPIO_Init(GPIOC,&GPIO_InitStructure); //��ʼ��PA0

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3); //PC7����λ��ʱ��3 
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);	

	//��ʼ��TIM3���벶�����
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC2S=01 	ѡ������� IC2ӳ�䵽TI2��
  TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI2��
  TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM3_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  TIM_ICInit(TIM3, &TIM3_ICInitStructure);
		
//	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC2,ENABLE);//��������ж� ,����CC1IE�����ж�	
	
  TIM_Cmd(TIM3,ENABLE ); 	//ʹ�ܶ�ʱ��3

 
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
		
}

void TIM3_CH3_Cap_Init(u32 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM3ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//ʹ��PORTCʱ��	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //GPIOC7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //����
	GPIO_Init(GPIOC,&GPIO_InitStructure); //��ʼ��PA0

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM3); //PC87����λ��ʱ��3 
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);	

	//��ʼ��TIM3���벶�����
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC3S=01 	ѡ������� IC3ӳ�䵽TI3��
  TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI3��
  TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM3_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  TIM_ICInit(TIM3, &TIM3_ICInitStructure);
		
	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC3,ENABLE);//��������ж� ,����CC3IE�����ж�	
	
  TIM_Cmd(TIM3,ENABLE ); 	//ʹ�ܶ�ʱ��3

 
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
		
}

void TIM3_CH4_Cap_Init(u32 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM3ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//ʹ��PORTCʱ��	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //GPIOC9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //����
	GPIO_Init(GPIOC,&GPIO_InitStructure); //��ʼ��PC9

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM3); //PC9����λ��ʱ��3 
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);	

	//��ʼ��TIM3���벶�����
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC4S=01 	ѡ������� IC4ӳ�䵽TI4��
  TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI2��
  TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM3_ICInitStructure.TIM_ICFilter = 0x00;//IC4F=0000 ���������˲��� ���˲�
  TIM_ICInit(TIM3, &TIM3_ICInitStructure);
		
	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC4,ENABLE);//��������ж� ,����CC4IE�����ж�	
	
  TIM_Cmd(TIM3,ENABLE ); 	//ʹ�ܶ�ʱ��3

 
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=4;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
		
}


#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

	//��ʱ��3�жϷ������	 
void TIM3_IRQHandler(void)
{ 		    

 	if(TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)//����1���������¼�
		{	
			TIM_ClearITPendingBit(TIM3, TIM_IT_CC1); 
			if(ICFLAG_1)		//����һ��������	
			{	  			
				CHANNEL_1_RISE = TIM_GetCapture1(TIM3);
	 			TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Falling); //CC1P=0 ����Ϊ�½��ز���
				ICFLAG_1 = 0;
			}else  								//�����½���
			{
				CHANNEL_1_FALL = TIM_GetCapture1(TIM3);
	 			TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Rising);		//CC1P=1 ����Ϊ�����ز���
				TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�	
				CHANNEL_1_PULSE_WIDE = (CHANNEL_1_FALL > CHANNEL_1_RISE ? CHANNEL_1_FALL - CHANNEL_1_RISE:CHANNEL_1_FALL - CHANNEL_1_RISE + 2499);
				TIM_SetCompare1(TIM4,CHANNEL_1_PULSE_WIDE);
				ICFLAG_1 = 1;
			}		    
			
		}			     	    					   
				//����жϱ�־λ
	 	
		if(TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)//����2���������¼�
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_CC2); //����жϱ�־λ
				if(ICFLAG_2)		//����һ��������	
			{	  			
				CHANNEL_2_RISE = TIM_GetCapture2(TIM3);
	 			TIM_OC2PolarityConfig(TIM3,TIM_ICPolarity_Falling); //CC2P=0 ����Ϊ�½��ز���
				ICFLAG_2 = 0;
			}else  					
			{
				CHANNEL_2_FALL = TIM_GetCapture2(TIM3);
				//TIM_Cmd(TIM3,ENABLE ); 	//ʹ�ܶ�ʱ��3
	 			TIM_OC2PolarityConfig(TIM3,TIM_ICPolarity_Rising);		//CC2P=1 ����Ϊ�½��ز���
				TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC2,ENABLE);//��������ж� ,����CC2IE�����ж�	
				CHANNEL_2_PULSE_WIDE = (CHANNEL_2_FALL > CHANNEL_2_RISE ? CHANNEL_2_FALL - CHANNEL_2_RISE:CHANNEL_2_FALL - CHANNEL_2_RISE + 2499);
				TIM_SetCompare2(TIM4,CHANNEL_2_PULSE_WIDE);
				ICFLAG_2 = 1;
			}		    
	}
	
 	if(TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)//����3���������¼�
		{	
				TIM_ClearITPendingBit(TIM3, TIM_IT_CC3); //����жϱ�־λ
			if(ICFLAG_3)		//����һ��������	
			{	  			
				CHANNEL_3_RISE = TIM_GetCapture3(TIM3);
	 			TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Falling); //CC3P=0 ����Ϊ�½��ز���
				ICFLAG_3 = 0;
			}else  								//�����½���
			{
				CHANNEL_3_FALL = TIM_GetCapture3(TIM3);
	 			TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Rising);		//CC3P=1 ����Ϊ�����ز���
				TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC3,ENABLE);//��������ж� ,����CC3IE�����ж�
				CHANNEL_3_PULSE_WIDE = (CHANNEL_3_FALL > CHANNEL_3_RISE ? CHANNEL_3_FALL - CHANNEL_3_RISE:CHANNEL_3_FALL - CHANNEL_3_RISE + 2499);
				ICFLAG_3 = 1;
			}		    
			
		}			     	    					   
		
 	if(TIM_GetITStatus(TIM3, TIM_IT_CC4) != RESET)//����1���������¼�
		{	
				TIM_ClearITPendingBit(TIM3, TIM_IT_CC4); //����жϱ�־λ
			if(ICFLAG_4)		//����һ��������	
			{	  			
				CHANNEL_4_RISE = TIM_GetCapture4(TIM3);
	 			TIM_OC4PolarityConfig(TIM3,TIM_ICPolarity_Falling); //CC4P=0 ����Ϊ�½��ز���
				ICFLAG_4 = 0;
			}else  								//�����½���
			{
				CHANNEL_4_FALL = TIM_GetCapture4(TIM3);
	 			TIM_OC4PolarityConfig(TIM3,TIM_ICPolarity_Rising);		//CC4P=1 ����Ϊ�����ز���
				TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC4,ENABLE);//��������ж� ,����CC1IE�����ж�	
				TIM_Cmd(TIM3,ENABLE ); 	//ʹ�ܶ�ʱ��3
				CHANNEL_4_PULSE_WIDE = (CHANNEL_4_FALL > CHANNEL_4_RISE ? CHANNEL_4_FALL - CHANNEL_4_RISE:CHANNEL_4_FALL - CHANNEL_4_RISE + 2499);
				ICFLAG_4 = 1;
			}		    
			
		}			     	    					   
				TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 
}



#ifdef __cplusplus
}
#endif //__cplusplus

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
int esc_control_flag = 1;//������·�����־ 1Ϊ�ɿؿ��� ����Ϊ������ֶ�����
void esc_control()//�ɻ���ת����·�������
	{
			TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�
			TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC2,ENABLE);//��������ж� ,����CC2IE�����ж�
		if(esc_control_flag == 1)
		{
			TIM_SetCompare1(TIM4,CHANNEL_1_PULSE_WIDE);
			TIM_SetCompare2(TIM4,CHANNEL_2_PULSE_WIDE);
		}
		else
		{//������PWM�ź� ���ɿ�����·��� ���Ʒɻ���̬��ת PWM��Χ 1224 -> 1843���ɿط�Χ��
			TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,DISABLE);//��������ж� ,����CC1IE�����ж�	
			TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC2,DISABLE);//��������ж� ,����CC2IE�����ж�	
			TIM_SetCompare1(TIM4,CHANNEL_1_ESC_WIDE);//940 -> 1224 -> 1843
			TIM_SetCompare2(TIM4,CHANNEL_2_ESC_WIDE);
			delay_nms(1000);
			//esc_control_flag = 1;
		}
	}

#ifdef __cplusplus
}
#endif //__cplusplus

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
bool channel_7_capture()//�ɻ���ˮ��תͨ��7 A3-F1-D1
	{
			if(CHANNEL_3_PULSE_WIDE>1720)		// MAX=1920 ͨ��7���ز����·�
			{
				printf("channel_7 value = %d\t\r\n",CHANNEL_3_PULSE_WIDE);
				return true;
			}
			else if(CHANNEL_3_PULSE_WIDE<1420)													// MIN=1520	ͨ��7���ز����Ϸ�
				return false;
	}

bool channel_8_capture()//һ�����ͨ��8 A3-F2-D2
	{
			if(CHANNEL_4_PULSE_WIDE>1620)		// MAX=1920 ͨ��7���ز����·�
			{
				printf("channel_8 value = %d\t\r\n",CHANNEL_4_PULSE_WIDE);
				return true;
			}
			else														// MIN=1396	ͨ��8���ز����Ϸ�
				return false;
	}

#ifdef __cplusplus
}
#endif //__cplusplus




