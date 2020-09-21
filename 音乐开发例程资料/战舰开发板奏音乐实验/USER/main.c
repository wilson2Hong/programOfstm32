/**************************************
* 					开发板唱歌实验						*
* 实验环境：STM32战舰开发板					*
* 实验内容：利用TIM4_CH3输出比较模式	*
*						实现音乐演奏							*
* 建立日期：2014年08月22日						*
* 设    计：铜河											*
* 修改日期：2014年08月22日						*
**************************************/
#include "stm32f10x_tim.h"
#include "timer.h"
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "music.h"

void sound(u16 k)
{
	u16 x;
	x=music_data[k][0];			//读取音阶数据
	if(x!=0)
	{
		x=4000000/x;					//计算计数值
		TIM4->ARR = x;				//计数值写入重装载寄存器
 		GPIOB->CRH&=0XFFFFFFF0;
 		GPIOB->CRH|=0X0000000B;	//PB.8复用推挽输出
		TIM_Cmd(TIM4, ENABLE);	//开声音
	}
	else
	{
		TIM_Cmd(TIM4, DISABLE);		//关声音disenable
 		GPIOB->CRH&=0XFFFFFFF0;
 		GPIOB->CRH|=0X00000003;		//PB.8推挽输出
		PBout(8)=0;      		////停止时蜂鸣器管脚低电平
	}
}


int main(void)
{
	u8 i=0;
	TIM4_Init(1999,8);		//初始化定时器4，预分频9，计数频率8MHz

	LED_Init();
	delay_init();

  while (1)
  {
		while(music_data[i][1]!=0)	//等待音乐结束
		{
			LED0 = 0;									//每切换一个音符，LED0闪一下
			sound(i);									//播放音符
			delay_ms(50);
			LED0 = 1;
			delay_ms(music_data[i][1]-50);//音符时长
			LED1 = !LED1;							//每切换一个音符，LED1反一种状态
			i++;											//下一个音符
			TIM_Cmd(TIM4, DISABLE);		//每两个音符间停止一小会
			GPIOB->CRH&=0XFFFFFFF0;
			GPIOB->CRH|=0X00000003;		//PB.8推挽输出
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);//停止时蜂鸣器管脚低电平
			delay_ms(20);
		}
		TIM_Cmd(TIM4, DISABLE);			//音乐结束，停止播放
		delay_ms(1500);//延时后继续
		//delay_ms(1500);
		i=0; 						//从头开始
	}
}

			



