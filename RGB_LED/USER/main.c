#include "stm32f10x.h"
#include "delay.h"
#include "led.h"

/*
����ԭ��������Ӧ��RGB��ɫ�ĵ�  ����RGB��ԭɫ��ϲ�����������ɫ

*/


int main(void)
{
	delay_init();
	LED_Init();
	while(1)
	{
		//��
		LEDR=1;
		LEDG=0;
		LEDB=0;
		delay_ms(1000);
		
		//����
		LEDR=0;
		LEDG=1;
		LEDB=1;
		delay_ms(1000);
		
		//��
		LEDR=1;
		LEDG=1;
		LEDB=0;
		delay_ms(1000);
		
		//��
		LEDR=0;
		LEDG=1;
		LEDB=0;
		delay_ms(1000);
		
		//��
		LEDR=0;
		LEDG=0;
		LEDB=1;
		delay_ms(1000);
		
		//��
		LEDR=1;
		LEDG=1;
		LEDB=1;
		delay_ms(1000);
		
		//��
		LEDR=1;
		LEDG=0;
		LEDB=1;
		delay_ms(1000);
		
	}
	
	
}
