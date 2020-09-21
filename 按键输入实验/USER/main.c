#include "led.h"
#include "delay.h"
#include "sys.h"
#include "beep.h"
#include "key.h"
int main(void)
{
	vu8 key=0;
	delay_init();//延时函数初始化	 
	LED_Init();
	BEEP_Init();
	KEY_Init();
	LED0=0;
	while(1)
	{
		key=KEY_Scan(0);//得到键值,且不支持连按
		if(key)
		{
			switch(key)
			{
				case WKUP_PRESS://控制蜂鸣器
					BEEP=!BEEP;
				break;
				
				case KEY2_PRESS://控制LED0翻转
					LED0=!LED0;
				break;
				
				case KEY1_PRESS://控制LED1翻转	
					LED1=!LED1;
				break;
				
				case KEY0_PRESS://同时控制LED0,LED1翻转 
					LED0=!LED0;
				  LED1=!LED1;
				break;
			}
		}else delay_ms(10); 
		
	}
}
