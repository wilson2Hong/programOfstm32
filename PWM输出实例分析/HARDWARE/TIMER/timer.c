#include "timer.h"
#include "led.h"
#include "usart.h"

void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设
   
}

//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		LED1=!LED1;
		}
}


void TIM3_PWM_Init(u16 arr,u16 psc,u16 CCR1_Val,u16 CCR2_Val,u16 CCR3_Val,u16 CCR4_Val)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能定时器3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB,ENABLE);//使能GPIO外设和AFIO复用功能模块时钟
	
	
	
	//设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_0|GPIO_Pin_1; //TIM_CH1 TIM_CH2 TIM_CH3 TIM_CH4
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);//初始化GPIO
 
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);//Timer3部分重映射 TIM3_CH1->PB4 TIM3_CH2->PB5 TIM3_CH0->PB0  TIM3_CH4->PB1 
	//初始化TIM3
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; //设置时钟分频系数：不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStructure.TIM_Period = arr;//定时器计数周期  0~arr
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;//设置预分频系数：psc=0 不预分频 默认TIMxClock=72MHz
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
		//初始化TIM3 Channel1 PWM模式	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//输出PWM1模式  大于TIMx_CNT值有效
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse=CCR1_Val;
	
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);//使能通道1
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
		//初始化TIM3 Channel2 PWM模式	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//PMW1  小于有效   pwm2大于有效
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse=CCR2_Val;
	
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);//使能通道3
	
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
		//初始化TIM3 Channel3 PWM模式	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse=CCR3_Val;
	
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);//使能通道3
	
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	//初始化TIM3 Channel4 PWM模式	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse=CCR4_Val;
	
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);//使能通道4
	
	/*允许更新事件到来时TIM_CCRx的值载入寄存器中 设置CCMR1的OC2PE 标志 
	0:禁止TIMx_CCR1的预装在功能，可随时写入TIMx_CCR1寄存器并且写入的数值立即起作用
	1：开芓IMx_CCR1寄存器的预装载功能，读写操作仅对与装载寄存器操作，TIMx_CCR1的预装载值在更新事件到来时被传送至当前寄存器
	*/
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);// 
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);//允许在定时器工作是重新在ARR里写入新值
	
	TIM_Cmd(TIM3,ENABLE);//使能定时器3

}
