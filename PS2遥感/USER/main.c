#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "beep.h"
#include "usart.h"	 
#include "adc.h"
#include "dma.h"
#include "stm32f10x.h"
float ADC_ConvertedValueLocal[2];

extern volatile uint16_t ADCConvertedValue[2];

char *state[6]={"Home","Up","Down","Left","Right","Pressed"};

int direction()
{
	int x,y;
	int tmp;
	
	x=ADCConvertedValue[0];
	y=ADCConvertedValue[1];
	delay_ms(500);
	if(y>=0&&y<=20) tmp=1;   //Up
	if(y==4095&&x>=3000&&x<=3200)     tmp=2;   //Down
	if(x>=0&&x<=20&&y>=3000&&y<=3200) tmp=3;   //Left
  if(x==4095&&y>=3000&&y<=3200)	    tmp=4;   //Right 
	if(x>=3000&&x<=3200&&y>=3000&&y<=3200)
		tmp=0;                  //Home
	if(SW==0)
		{
			delay_ms(10);
		  tmp=5;    //Button Pressed
    }
  return tmp;
}
int main(void)
{
	int tmp;
	//int status = 0;
	
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��		 	
 	Adc_Init();		  		//ADC��ʼ��
	MyDMA_Init();
  BEEP_Init();
	while(1)
	{
		tmp = direction();
//		if(tmp!=status)
//		{
//			printf("%s\n",state[tmp]);
//			status = tmp;
//		}	
		if(tmp)
		{
			switch(tmp)
			{
				case 1:   //Up
					LED0=!LED0;
				  printf("%s\n",state[tmp]);
				  break;
				case 2:   //Down
					LED1=!LED1;
				  printf("%s\n",state[tmp]);
				  break;
				case 3:   //Left
					printf("%s\n",state[tmp]);
					LED0=!LED0;
				  LED1=!LED1;
				  break;
				case 4:    //Right
					printf("%s\n",state[tmp]);
				  break;
				case 5:   //Button Pressed
					printf("%s\n",state[tmp]);
					BEEP=!BEEP;
				  break;
			}
		}else delay_ms(10);
  }
 }

