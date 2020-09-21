#include "timer.h"

//TIM2 PWM????? 
//PWM?????
//arr:?????
//psc:??????
void TIM4_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;						//设一个IO变量
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	//设一个定时器变量
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能TIM2
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//使能PWM输出端口
 
  //配置PWM输出端口：TIM4 CH3 PWM  GPIOB.8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM2_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);		//置入
// 	
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);		//置入
// //	GPIO_ResetBits(GPIOA,GPIO_Pin_2);					//初始化为低，使能音频
// 	GPIO_SetBits(GPIOA,GPIO_Pin_2);
//  
  //配置TIM4
	TIM_TimeBaseStructure.TIM_Period = arr; //计数上限
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM2向上计数
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //配置数据
	 
	//???TIM4 Channel3 PWM??	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;	//TIM_OCMode_PWM2; //TIM_OCMode_Toggle在比较成功后翻转对应输出管脚的电平
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //??????
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //????:TIM???????
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //??T??????????TIM2 OC4

	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //??TIM3?CCR2????????
 
//	TIM_Cmd(TIM4, ENABLE);  //??TIM2
}


