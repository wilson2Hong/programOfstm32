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
 TIM3_PWM_Init(1000,0,500,375,250,125);//arr=1000; Ԥ��Ƶϵ��psc=0��
	 while(1)
	 {
	 }
 }


