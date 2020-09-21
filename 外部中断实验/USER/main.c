#include "led.h"
#include "delay.h"
#include "sys.h"
#include "beep.h"
#include "exti.h"
#include "usart.h"
#include "key.h"
#include "stm32f10x.h"
int main(void)
{
	delay_init();//延时函数初始化	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);
	LED_Init();
	BEEP_Init();
	EXTIX_Init();
	KEY_Init();
	LED0=0;
	BEEP=0;
	while(1)
	{
		//printf("OK\r\n");
		delay_ms(1000);
	}
}
