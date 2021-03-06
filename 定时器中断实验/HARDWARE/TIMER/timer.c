#include "timer.h"
#include "stm32f10x.h"
#include "led.h"
void TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision=0;//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//TIM向上计数模式
	TIM_TimeBaseInitStructure.TIM_Period=arr;//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;//设置用来作为TIMx时钟频率除数的预分频值
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//根据指定的参数初始化TIMx的时间基数单位
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //使能指定的TIM3中断,允许更新中断
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;//TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//IRQ通道被使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;//从优先级3级
	
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM3,ENABLE);

}
void TIM3_IRQHandler(void)   //TIM3中断
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)	//检查TIM3更新中断发生与否
	{
		LED1=!LED1;
		
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//清除TIMx更新中断标志 
	}
	
}
