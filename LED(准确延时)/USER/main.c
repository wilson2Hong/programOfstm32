#include "stm32f10x.h"
#include "led.h"
#include "delay.h"

int main()
{
	LED_Init();
	Delay_Init();
	
	while(1)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		Delay_ms(500);
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		Delay_ms(500);
	}
}