/**************************************
* 					�����峪��ʵ��						*
* ʵ�黷����STM32ս��������					*
* ʵ�����ݣ�����TIM4_CH3����Ƚ�ģʽ	*
*						ʵ����������							*
* �������ڣ�2014��08��22��						*
* ��    �ƣ�ͭ��											*
* �޸����ڣ�2014��08��22��						*
**************************************/
#include "stm32f10x_tim.h"
#include "timer.h"
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "music.h"

void sound(u16 k)
{
	u16 x;
	x=music_data[k][0];			//��ȡ��������
	if(x!=0)
	{
		x=4000000/x;					//�������ֵ
		TIM4->ARR = x;				//����ֵд����װ�ؼĴ���
 		GPIOB->CRH&=0XFFFFFFF0;
 		GPIOB->CRH|=0X0000000B;	//PB.8�����������
		TIM_Cmd(TIM4, ENABLE);	//������
	}
	else
	{
		TIM_Cmd(TIM4, DISABLE);		//������disenable
 		GPIOB->CRH&=0XFFFFFFF0;
 		GPIOB->CRH|=0X00000003;		//PB.8�������
		PBout(8)=0;      		////ֹͣʱ�������ܽŵ͵�ƽ
	}
}


int main(void)
{
	u8 i=0;
	TIM4_Init(1999,8);		//��ʼ����ʱ��4��Ԥ��Ƶ9������Ƶ��8MHz

	LED_Init();
	delay_init();

  while (1)
  {
		while(music_data[i][1]!=0)	//�ȴ����ֽ���
		{
			LED0 = 0;									//ÿ�л�һ��������LED0��һ��
			sound(i);									//��������
			delay_ms(50);
			LED0 = 1;
			delay_ms(music_data[i][1]-50);//����ʱ��
			LED1 = !LED1;							//ÿ�л�һ��������LED1��һ��״̬
			i++;											//��һ������
			TIM_Cmd(TIM4, DISABLE);		//ÿ����������ֹͣһС��
			GPIOB->CRH&=0XFFFFFFF0;
			GPIOB->CRH|=0X00000003;		//PB.8�������
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);//ֹͣʱ�������ܽŵ͵�ƽ
			delay_ms(20);
		}
		TIM_Cmd(TIM4, DISABLE);			//���ֽ�����ֹͣ����
		delay_ms(1500);//��ʱ�����
		//delay_ms(1500);
		i=0; 						//��ͷ��ʼ
	}
}

			



