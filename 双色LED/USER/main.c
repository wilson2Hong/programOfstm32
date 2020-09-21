#include "stm32f10x.h"
#include "delay.h"
#include "led.h"

/*使用的硬件为创乐博的双色LED灯注意接线GND接标有-的引脚，其余两根线随便
工作原理：利用两个信号脚不同的压差发不同的光

*/


int main(void)
{
	delay_init();
	LED_Init();
	while(1)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);
		delay_ms(1000);
		
		GPIO_SetBits(GPIOE,GPIO_Pin_5);
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		delay_ms(1000);
		
		
	}
	
	
}
