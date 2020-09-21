#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "exti.h"
 
/************************************************
 ALIENTEKս��STM32������ʵ��9
 PWM���ʵ��֮���ֲ���
 KEY2:����ǧ��ǧѰ
 KEY1:�������뿪�Ͼ����Ӵ�û�˺���˵��
 key0:�������տ���
 WK_UP:���Ʒ�����(δʵ��)
 BUG:��ʱ����KEY0�󲥷����տ��ֽ����󣬻��������KEY1,KEY2����Ӧ������
 ���⣺ΪʲôWK_UP�����ܿ������ֵĲ���
 ��ֹ��δ���
 ��STM32��Դ���ؿ�������Զ�����KEY2����Ӧ����
 
 
 �۴���multiply define symbol  ��Ϊ��music.h�ж���int music_data[]{} ���� int music_data[]={}��ȷ

************************************************/	
	
 int main(void)
 {		
	 delay_init();
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	 uart_init(115200);
	 BEEP_Init();  
	 LED_Init();
	 EXTIX_Init();
	 KEY_Init();
 	 LED0=0;
	 LED1=1; 
	 while(1)
	 {
		
		 printf("OK\r\n");	
		 delay_ms(1000);	 
		
   }
 }
 
