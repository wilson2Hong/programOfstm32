#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
 
/************************************************
 ALIENTEKս��STM32������ʵ��9
 PWM���ʵ��  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
 
 
 
0.5ms--------------0��;
1.0ms------------45��;
1.5ms------------90��;
2.0ms-----------135��;
2.5ms-----------180��;
************************************************/

	
 int main(void)
 {		
 	 u16 led0pwmval=15;
   u8	 dir=1;
   delay_init();
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	 uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	 LED_Init();
	//KEY_Init();
	 TIM3_PWM_Init(30,7199);
	 
	 while(1)
	 {
     delay_ms(10);
		 if(dir==1)led0pwmval++;
		 else led0pwmval--;
		 
		 if(led0pwmval>20)dir=0;
		 if(led0pwmval==10)dir=1;
		 
		TIM_SetCompare2(TIM3,led0pwmval); 	 
	 } 
 }


