#include "us100.h"
#include "stm32f10x.h"
#include "delay.h"

/*记录定时器溢出的次数*/
uint overcount=0;

/*设置中断优先级*/

void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	
	NVIC_Init(&NVIC_InitStructure);
}

/*初始化模块的GPIO以及初始化定时器TIM2*/
void 	us100_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	/*trig触发信号*/
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	
	/*echo回响信号*/
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
  GPIO_Init(GPIOB, & GPIO_InitStructure);
	
	
	/*定时器TIM2初始化*/
	TIM_DeInit(TIM2);
	TIM_TimeBaseInitStructure.TIM_Period=999;//定时周期为1000
	TIM_TimeBaseInitStructure.TIM_Prescaler=71;//分频系数72
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//不分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//开启更新中断
	NVIC_Config();
	TIM_Cmd(TIM2,DISABLE);//关闭定时器使能
}

float Senor_Using(void)
{
	float length=0,sum=0;
	u16 tim;
	uint i=0;
	
	/*测5次数据计算一次平均值*/
	while(i!=5)
	{
		PBout(3)=1;//拉高信号，作为触发信号
		delay_us(20);//触发信号必须为10us以上
		PBout(3)=0;
		
		/*等待回响信号*/
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==RESET);
		TIM_Cmd(TIM2,ENABLE);//回响信号的到来，开启定时器计数
		
		i+=1;//每收到一次回响信号+1，收到5次就计算均值
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==SET);//回响信号消失
		TIM_Cmd(TIM2,DISABLE);//关闭定时器
		
		tim=TIM_GetCounter(TIM2);//获取TIM2计数寄存器中的计数值，以便计算回响信号时间
		
    length=(tim+overcount*1000)/58.0;//通过回响信号计算距离(us/58=厘米 或者 us/148=英寸 或者 距离=高电平时间*声速(340m/s)/2

		sum=length+sum;
		
		TIM2->CNT=0;//将TIM2计数寄存器的计数值清零
    overcount=0;
    
    delay_ms(100);		
	}
	 length=sum/5;
		return length;//距离作为函数返回值
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除中断标志
		overcount++;
	}
}
































