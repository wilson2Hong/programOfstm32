#include "delay.h"
#include "stm32f10x.h"

static uint32_t D_us=0;//微妙系数
static uint32_t D_ms=0;//毫秒系数

void Delay_Init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//SysTick为系统时钟八分频  即此处SysTick=9MHZ  系统VAL每减少1需要1/9 us
	
	
	D_us=SystemCoreClock/8000000;  //72mhz   7200 0000/800 0000=9  系统上电后时钟默认72MHZ  Systick->VAL寄存器每递减9次即为延时1us 
	D_ms=D_us*1000;
}

void Delay_us(uint32_t nus)
{
	uint32_t temp;
	SysTick->CTRL=0x00;  //关闭SysTick定时器
	SysTick->LOAD=nus*D_us;//延时重装载值	  	//SysTick->LOAD是一个24位的寄存器	 因此他可以存入的最大值为  2的24次方/9=1864135us 即为1864ms
	SysTick->VAL=0x00;	//清空计数器
	SysTick->CTRL|=0x01;//启动SysTick定时器  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));//等待延时结束  
	SysTick->CTRL=0x00;//关闭SysTick定时器
	SysTick->VAL=0x00;//清空计数器
}
}


void Delay_ms(uint32_t nus)
{
	uint32_t temp;
	SysTick->CTRL=0x00;//关闭SysTick定时器
	SysTick->LOAD=nus*D_ms;//延时重装载值
	SysTick->VAL=0x00;//清空计数器
	SysTick->CTRL|=0x01;//启动SysTick定时器  
	do
	{
		temp=SysTick-CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));//等待延时结束  
	SysTick->CTRL=0x00;//关闭SysTick定时器
	SysTick-VAL=0x00;//清空计数器
}