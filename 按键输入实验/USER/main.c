#include "led.h"
#include "delay.h"
#include "sys.h"
#include "beep.h"
#include "key.h"
int main(void)
{
	vu8 key=0;
	delay_init();//��ʱ������ʼ��	 
	LED_Init();
	BEEP_Init();
	KEY_Init();
	LED0=0;
	while(1)
	{
		key=KEY_Scan(0);//�õ���ֵ,�Ҳ�֧������
		if(key)
		{
			switch(key)
			{
				case WKUP_PRESS://���Ʒ�����
					BEEP=!BEEP;
				break;
				
				case KEY2_PRESS://����LED0��ת
					LED0=!LED0;
				break;
				
				case KEY1_PRESS://����LED1��ת	
					LED1=!LED1;
				break;
				
				case KEY0_PRESS://ͬʱ����LED0,LED1��ת 
					LED0=!LED0;
				  LED1=!LED1;
				break;
			}
		}else delay_ms(10); 
		
	}
}
