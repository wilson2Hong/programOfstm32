//#include "stm32f10x.h"
//#include "delay.h"
//#include "led.h"
//#include "beep.h"
//int main(void)
//{
//	delay_init();
//	LED_Init();
//	BEEP_Init();
//	
//   while(1)
//   {
//		 GPIO_SetBits(GPIOB,GPIO_Pin_5);
//		 GPIO_SetBits(GPIOB,GPIO_Pin_8);
//		 delay_ms(300);
//		 
//		 GPIO_ResetBits(GPIOB,GPIO_Pin_5);
//		 GPIO_ResetBits(GPIOB,GPIO_Pin_8);
//		 delay_ms(300);
//	 }
//}

#include "sys.h"
#include "delay.h"
#include "led.h"
#include "beep.h"

int main(void)
{
	delay_init();
	LED_Init();
	BEEP_Init();
	while(1)
  {
		LED0=0;
		LED1=1;
		BEEP=0;
		delay_ms(300);
		
		LED0=1;
		LED1=0;
		BEEP=1;
		delay_ms(300);
		
		
	}
}
