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
		LED0=1;
		delay_ms(1000);
		
		LED0=0;	
		delay_ms(1000);
	}
	
	
}
