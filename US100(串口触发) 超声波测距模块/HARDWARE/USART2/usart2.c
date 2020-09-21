#include "usart2.h"
#include "sys.h"

void uart2_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//������ʱ����ʱ��
	
	//PA2   USART2_TX
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//�����������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//PA3   USART2_RX
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//��������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//USART2 ����
	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//��Ӳ������
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//�շ�ģʽ
	USART_InitStructure.USART_Parity=USART_Parity_No;//����żУ��
	USART_InitStructure.USART_StopBits=USART_StopBits_1;//һλֹͣλ
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;//��λ�ֳ�
	
	USART_Init(USART2,&USART_InitStructure);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//�����ж�
	USART_ClearFlag(USART2,USART_FLAG_TC);//�������ʱ �����־λ
	
	//USART2 �ж�����
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;//ѡ��USART2_IRQn�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//ʹ���жϽ���ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_Init(&NVIC_InitStructure);
	
}

void USART2_send_byte(char data)
{

}
