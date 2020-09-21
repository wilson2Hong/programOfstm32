#include "inlet_outlet_valve.hpp"
#include "stm32f4xx_tim.h"
#include "main.h"
#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
int open_pwm_value1=2400,open_pwm_value2=2400,close_pwm_value1=750,close_pwm_value2=750;

//��ʼ��PA1Ϊ�����.��ʹ��ʱ��		    
//���� IO��ʼ��
void FAN_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��

  //GPIOF9,F10��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);//���õͣ��̵�������

}
	 
	 
void open_valve()//�򿪽�������
{		
			TIM_SetCompare3(TIM4,open_pwm_value2);
			TIM_SetCompare4(TIM4,open_pwm_value1);
			FAN = 1;																//���ȼ̵��������պ�
			delay_nms(1000);
}
void close_valve()//�رս�����
{
			TIM_SetCompare3(TIM4,close_pwm_value2);
			TIM_SetCompare4(TIM4,close_pwm_value1);
			FAN = 0;																//���ȼ̵��������Ͽ�
			delay_nms(1000);
//			TIM_SetCompare3(TIM4,750);
//			TIM_SetCompare4(TIM4,750);
//			delay_nms(1000);
}	 

#ifdef __cplusplus
}
#endif //__cplusplus
