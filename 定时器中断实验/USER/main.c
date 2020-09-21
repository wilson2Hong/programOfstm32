#include "led.h"
#include "key.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"

int main(void)
{
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	LED_Init();
	KEY_Init();
	TIM3_Init(4999,7199);//10Khz的计数频率，计数到5000为500ms
	while(1)
	{
		LED0=!LED0;
		delay_ms(200);
	}

}

