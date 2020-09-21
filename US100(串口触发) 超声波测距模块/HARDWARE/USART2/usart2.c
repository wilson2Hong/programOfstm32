#include "usart2.h"
#include "sys.h"

void uart2_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//开启分时复用时钟
	
	//PA2   USART2_TX
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//PA3   USART2_RX
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//USART2 配置
	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//无硬流控制
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//收发模式
	USART_InitStructure.USART_Parity=USART_Parity_No;//无奇偶校验
	USART_InitStructure.USART_StopBits=USART_StopBits_1;//一位停止位
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;//八位字长
	
	USART_Init(USART2,&USART_InitStructure);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//接收中断
	USART_ClearFlag(USART2,USART_FLAG_TC);//发送完成时 清除标志位
	
	//USART2 中断配置
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;//选择USART2_IRQn中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//使能中断接收通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_Init(&NVIC_InitStructure);
	
}

void USART2_send_byte(char data)
{

}
