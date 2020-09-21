#include"stm32f10x.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct; //����GPIO�ṹ�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2_GPIOC,ENABLE);//ʹ��GPIOC��ʱ��
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_13;//����GPIO��13����
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;//����GPIOΪͨ���������
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz; //����GPIO����
	GPIO_Init(GIOC,&GPIO_InitStruct);//GPIO��ʼ������
	
	GPIO_SetBits(GPIOC,GPIO_Pin_13); //PC13������λ���൱�ڸߵ�ƽ������ʼ����Ϩ��
}