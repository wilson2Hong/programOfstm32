#include "stm32f10x.h"
#include "delay.h"
#include "led.h"

/*ʹ�õ�Ӳ��Ϊ���ֲ���˫ɫLED��ע�����GND�ӱ���-�����ţ��������������
����ԭ�����������źŽŲ�ͬ��ѹ���ͬ�Ĺ�

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
