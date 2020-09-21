#include "led.h"
#include "key.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"

int main(void)
{
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();
	KEY_Init();
	TIM3_Init(4999,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms
	while(1)
	{
		LED0=!LED0;
		delay_ms(200);
	}

}

