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
//TIM4 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM4_PWM_Init(u32 arr,u32 psc)
{		 					 
	//此部分需手动修改IO口设置
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM4时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//使能PORTD时钟	
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); //GPIOD12复用为定时器4
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4); //GPIOD13复用为定时器4
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4); //GPIOD14复用为定时器4
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4); //GPIOD15复用为定时器4
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;           //GPIOD_12 13 14 15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOD,&GPIO_InitStructure);              //初始化PD12_13_14_15
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//初始化定时器4
	
	//初始化TIM4 Channel1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低 //TIM_OCPolarity_Low //TIM_OCPolarity_High
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC1
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC2
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC3
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC4
	
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR1上的预装载寄存器
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR2上的预装载寄存器
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR3上的预装载寄存器
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR4上的预装载寄存器
 
	
  TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPE使能 
	
	TIM_Cmd(TIM4, ENABLE);  //使能TIM4
 
	TIM_SetCompare1(TIM4,940);
	TIM_SetCompare2(TIM4,940);
	TIM_SetCompare3(TIM4,0);
	TIM_SetCompare4(TIM4,0);
						  
}  

TIM_ICInitTypeDef  TIM3_ICInitStructure;

//定时器3通道1输入捕获配置
//arr：自动重装值(TIM2,TIM5是32位的!!)
//psc：时钟预分频数
void TIM3_CH1_Cap_Init(u32 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM3时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//使能PORTC时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //GPIOC6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //下拉
	GPIO_Init(GPIOC,&GPIO_InitStructure); //初始化PA0

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3); //PC6复用位定时器3  
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	

	//初始化TIM3输入捕获参数
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
  TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  TIM3_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  TIM_ICInit(TIM3, &TIM3_ICInitStructure);
		
//	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	
  TIM_Cmd(TIM3,ENABLE ); 	//使能定时器3

 
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、	
}

void TIM3_CH2_Cap_Init(u32 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM3时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//使能PORTC时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //GPIOC7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //下拉
	GPIO_Init(GPIOC,&GPIO_InitStructure); //初始化PA0

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3); //PC7复用位定时器3 
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);	

	//初始化TIM3输入捕获参数
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC2S=01 	选择输入端 IC2映射到TI2上
  TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI2上
  TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  TIM3_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  TIM_ICInit(TIM3, &TIM3_ICInitStructure);
		
//	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC2,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	
  TIM_Cmd(TIM3,ENABLE ); 	//使能定时器3

 
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
		
}

void TIM3_CH3_Cap_Init(u32 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM3时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//使能PORTC时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //GPIOC7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //下拉
	GPIO_Init(GPIOC,&GPIO_InitStructure); //初始化PA0

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM3); //PC87复用位定时器3 
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);	

	//初始化TIM3输入捕获参数
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC3S=01 	选择输入端 IC3映射到TI3上
  TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI3上
  TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  TIM3_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  TIM_ICInit(TIM3, &TIM3_ICInitStructure);
		
	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC3,ENABLE);//允许更新中断 ,允许CC3IE捕获中断	
	
  TIM_Cmd(TIM3,ENABLE ); 	//使能定时器3

 
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
		
}

void TIM3_CH4_Cap_Init(u32 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM3时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//使能PORTC时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //GPIOC9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //下拉
	GPIO_Init(GPIOC,&GPIO_InitStructure); //初始化PC9

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM3); //PC9复用位定时器3 
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);	

	//初始化TIM3输入捕获参数
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC4S=01 	选择输入端 IC4映射到TI4上
  TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI2上
  TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  TIM3_ICInitStructure.TIM_ICFilter = 0x00;//IC4F=0000 配置输入滤波器 不滤波
  TIM_ICInit(TIM3, &TIM3_ICInitStructure);
		
	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC4,ENABLE);//允许更新中断 ,允许CC4IE捕获中断	
	
  TIM_Cmd(TIM3,ENABLE ); 	//使能定时器3

 
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=4;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
		
}


#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

	//定时器3中断服务程序	 
void TIM3_IRQHandler(void)
{ 		    

 	if(TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			TIM_ClearITPendingBit(TIM3, TIM_IT_CC1); 
			if(ICFLAG_1)		//捕获到一个上升沿	
			{	  			
				CHANNEL_1_RISE = TIM_GetCapture1(TIM3);
	 			TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Falling); //CC1P=0 设置为下降沿捕获
				ICFLAG_1 = 0;
			}else  								//捕获下降沿
			{
				CHANNEL_1_FALL = TIM_GetCapture1(TIM3);
	 			TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Rising);		//CC1P=1 设置为上升沿捕获
				TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
				CHANNEL_1_PULSE_WIDE = (CHANNEL_1_FALL > CHANNEL_1_RISE ? CHANNEL_1_FALL - CHANNEL_1_RISE:CHANNEL_1_FALL - CHANNEL_1_RISE + 2499);
				TIM_SetCompare1(TIM4,CHANNEL_1_PULSE_WIDE);
				ICFLAG_1 = 1;
			}		    
			
		}			     	    					   
				//清除中断标志位
	 	
		if(TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)//捕获2发生捕获事件
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_CC2); //清除中断标志位
				if(ICFLAG_2)		//捕获到一个上升沿	
			{	  			
				CHANNEL_2_RISE = TIM_GetCapture2(TIM3);
	 			TIM_OC2PolarityConfig(TIM3,TIM_ICPolarity_Falling); //CC2P=0 设置为下降沿捕获
				ICFLAG_2 = 0;
			}else  					
			{
				CHANNEL_2_FALL = TIM_GetCapture2(TIM3);
				//TIM_Cmd(TIM3,ENABLE ); 	//使能定时器3
	 			TIM_OC2PolarityConfig(TIM3,TIM_ICPolarity_Rising);		//CC2P=1 设置为下降沿捕获
				TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC2,ENABLE);//允许更新中断 ,允许CC2IE捕获中断	
				CHANNEL_2_PULSE_WIDE = (CHANNEL_2_FALL > CHANNEL_2_RISE ? CHANNEL_2_FALL - CHANNEL_2_RISE:CHANNEL_2_FALL - CHANNEL_2_RISE + 2499);
				TIM_SetCompare2(TIM4,CHANNEL_2_PULSE_WIDE);
				ICFLAG_2 = 1;
			}		    
	}
	
 	if(TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)//捕获3发生捕获事件
		{	
				TIM_ClearITPendingBit(TIM3, TIM_IT_CC3); //清除中断标志位
			if(ICFLAG_3)		//捕获到一个上升沿	
			{	  			
				CHANNEL_3_RISE = TIM_GetCapture3(TIM3);
	 			TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Falling); //CC3P=0 设置为下降沿捕获
				ICFLAG_3 = 0;
			}else  								//捕获下降沿
			{
				CHANNEL_3_FALL = TIM_GetCapture3(TIM3);
	 			TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Rising);		//CC3P=1 设置为上升沿捕获
				TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC3,ENABLE);//允许更新中断 ,允许CC3IE捕获中断
				CHANNEL_3_PULSE_WIDE = (CHANNEL_3_FALL > CHANNEL_3_RISE ? CHANNEL_3_FALL - CHANNEL_3_RISE:CHANNEL_3_FALL - CHANNEL_3_RISE + 2499);
				ICFLAG_3 = 1;
			}		    
			
		}			     	    					   
		
 	if(TIM_GetITStatus(TIM3, TIM_IT_CC4) != RESET)//捕获1发生捕获事件
		{	
				TIM_ClearITPendingBit(TIM3, TIM_IT_CC4); //清除中断标志位
			if(ICFLAG_4)		//捕获到一个上升沿	
			{	  			
				CHANNEL_4_RISE = TIM_GetCapture4(TIM3);
	 			TIM_OC4PolarityConfig(TIM3,TIM_ICPolarity_Falling); //CC4P=0 设置为下降沿捕获
				ICFLAG_4 = 0;
			}else  								//捕获下降沿
			{
				CHANNEL_4_FALL = TIM_GetCapture4(TIM3);
	 			TIM_OC4PolarityConfig(TIM3,TIM_ICPolarity_Rising);		//CC4P=1 设置为上升沿捕获
				TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC4,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
				TIM_Cmd(TIM3,ENABLE ); 	//使能定时器3
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
int esc_control_flag = 1;//控制两路电调标志 1为飞控控制 否则为程序或手动控制
void esc_control()//飞机翻转的两路电调控制
	{
			TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断
			TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC2,ENABLE);//允许更新中断 ,允许CC2IE捕获中断
		if(esc_control_flag == 1)
		{
			TIM_SetCompare1(TIM4,CHANNEL_1_PULSE_WIDE);
			TIM_SetCompare2(TIM4,CHANNEL_2_PULSE_WIDE);
		}
		else
		{//给入电调PWM信号 即可控制两路电机 控制飞机姿态翻转 PWM范围 1224 -> 1843（飞控范围）
			TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,DISABLE);//允许更新中断 ,允许CC1IE捕获中断	
			TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC2,DISABLE);//允许更新中断 ,允许CC2IE捕获中断	
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
bool channel_7_capture()//飞机落水翻转通道7 A3-F1-D1
	{
			if(CHANNEL_3_PULSE_WIDE>1720)		// MAX=1920 通道7开关拨向下方
			{
				printf("channel_7 value = %d\t\r\n",CHANNEL_3_PULSE_WIDE);
				return true;
			}
			else if(CHANNEL_3_PULSE_WIDE<1420)													// MIN=1520	通道7开关拨向上方
				return false;
	}

bool channel_8_capture()//一键起飞通道8 A3-F2-D2
	{
			if(CHANNEL_4_PULSE_WIDE>1620)		// MAX=1920 通道7开关拨向下方
			{
				printf("channel_8 value = %d\t\r\n",CHANNEL_4_PULSE_WIDE);
				return true;
			}
			else														// MIN=1396	通道8开关拨向上方
				return false;
	}

#ifdef __cplusplus
}
#endif //__cplusplus




