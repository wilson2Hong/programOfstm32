#include "stm32f10x.h"
#include "delay.h"
#include "led.h"

/*
工作原理：点亮对应的RGB颜色的灯  利用RGB三原色混合产生其他与颜色

*/


int main(void)
{
	delay_init();
	LED_Init();
	while(1)
	{
		//红
		LEDR=1;
		LEDG=0;
		LEDB=0;
		delay_ms(1000);
		
		//青蓝
		LEDR=0;
		LEDG=1;
		LEDB=1;
		delay_ms(1000);
		
		//黄
		LEDR=1;
		LEDG=1;
		LEDB=0;
		delay_ms(1000);
		
		//绿
		LEDR=0;
		LEDG=1;
		LEDB=0;
		delay_ms(1000);
		
		//蓝
		LEDR=0;
		LEDG=0;
		LEDB=1;
		delay_ms(1000);
		
		//白
		LEDR=1;
		LEDG=1;
		LEDB=1;
		delay_ms(1000);
		
		//紫
		LEDR=1;
		LEDG=0;
		LEDB=1;
		delay_ms(1000);
		
	}
	
	
}
