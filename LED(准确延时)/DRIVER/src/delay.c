#include "delay.h"
#include "stm32f10x.h"

static uint32_t D_us=0;//΢��ϵ��
static uint32_t D_ms=0;//����ϵ��

void Delay_Init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//SysTickΪϵͳʱ�Ӱ˷�Ƶ  ���˴�SysTick=9MHZ  ϵͳVALÿ����1��Ҫ1/9 us
	
	
	D_us=SystemCoreClock/8000000;  //72mhz   7200 0000/800 0000=9  ϵͳ�ϵ��ʱ��Ĭ��72MHZ  Systick->VAL�Ĵ���ÿ�ݼ�9�μ�Ϊ��ʱ1us 
	D_ms=D_us*1000;
}

void Delay_us(uint32_t nus)
{
	uint32_t temp;
	SysTick->CTRL=0x00;  //�ر�SysTick��ʱ��
	SysTick->LOAD=nus*D_us;//��ʱ��װ��ֵ	  	//SysTick->LOAD��һ��24λ�ļĴ���	 ��������Դ�������ֵΪ  2��24�η�/9=1864135us ��Ϊ1864ms
	SysTick->VAL=0x00;	//��ռ�����
	SysTick->CTRL|=0x01;//����SysTick��ʱ��  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));//�ȴ���ʱ����  
	SysTick->CTRL=0x00;//�ر�SysTick��ʱ��
	SysTick->VAL=0x00;//��ռ�����
}
}


void Delay_ms(uint32_t nus)
{
	uint32_t temp;
	SysTick->CTRL=0x00;//�ر�SysTick��ʱ��
	SysTick->LOAD=nus*D_ms;//��ʱ��װ��ֵ
	SysTick->VAL=0x00;//��ռ�����
	SysTick->CTRL|=0x01;//����SysTick��ʱ��  
	do
	{
		temp=SysTick-CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));//�ȴ���ʱ����  
	SysTick->CTRL=0x00;//�ر�SysTick��ʱ��
	SysTick-VAL=0x00;//��ռ�����
}