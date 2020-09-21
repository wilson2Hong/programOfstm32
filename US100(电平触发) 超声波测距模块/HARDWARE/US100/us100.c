#include "us100.h"
#include "stm32f10x.h"
#include "delay.h"

/*��¼��ʱ������Ĵ���*/
uint overcount=0;

/*�����ж����ȼ�*/

void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	
	NVIC_Init(&NVIC_InitStructure);
}

/*��ʼ��ģ���GPIO�Լ���ʼ����ʱ��TIM2*/
void 	us100_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	/*trig�����ź�*/
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//�������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	
	/*echo�����ź�*/
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//��������
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
  GPIO_Init(GPIOB, & GPIO_InitStructure);
	
	
	/*��ʱ��TIM2��ʼ��*/
	TIM_DeInit(TIM2);
	TIM_TimeBaseInitStructure.TIM_Period=999;//��ʱ����Ϊ1000
	TIM_TimeBaseInitStructure.TIM_Prescaler=71;//��Ƶϵ��72
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//���������ж�
	NVIC_Config();
	TIM_Cmd(TIM2,DISABLE);//�رն�ʱ��ʹ��
}

float Senor_Using(void)
{
	float length=0,sum=0;
	u16 tim;
	uint i=0;
	
	/*��5�����ݼ���һ��ƽ��ֵ*/
	while(i!=5)
	{
		PBout(3)=1;//�����źţ���Ϊ�����ź�
		delay_us(20);//�����źű���Ϊ10us����
		PBout(3)=0;
		
		/*�ȴ������ź�*/
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==RESET);
		TIM_Cmd(TIM2,ENABLE);//�����źŵĵ�����������ʱ������
		
		i+=1;//ÿ�յ�һ�λ����ź�+1���յ�5�ξͼ����ֵ
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==SET);//�����ź���ʧ
		TIM_Cmd(TIM2,DISABLE);//�رն�ʱ��
		
		tim=TIM_GetCounter(TIM2);//��ȡTIM2�����Ĵ����еļ���ֵ���Ա��������ź�ʱ��
		
    length=(tim+overcount*1000)/58.0;//ͨ�������źż������(us/58=���� ���� us/148=Ӣ�� ���� ����=�ߵ�ƽʱ��*����(340m/s)/2

		sum=length+sum;
		
		TIM2->CNT=0;//��TIM2�����Ĵ����ļ���ֵ����
    overcount=0;
    
    delay_ms(100);		
	}
	 length=sum/5;
		return length;//������Ϊ��������ֵ
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//����жϱ�־
		overcount++;
	}
}
































