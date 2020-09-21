#include "dma.h"
volatile uint16_t ADCConvertedValue[10][4];
void MyDMA_Init(void)//����DMA1_CHx
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMA����
	
	DMA_DeInit(DMA1_Channel1) ; //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ

	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);  //DMA�������ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;  //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //���ݴ��䷽�򣬴����跢�͵��ڴ棬�ò����涨����������Ϊ���ݴ����Ŀ�ĵػ�����Դ���˴���Ϊ��Դ
	DMA_InitStructure.DMA_BufferSize = 4*10;  //DMAͨ����DMA����Ĵ�С,��λΪ���ݵ�λ������Ҳ����ADCConvertedValue�Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  //������ѭ��ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMAͨ�� xӵ�������ȼ� 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);  //����DMA_InitStructure��ָ���Ĳ�����ʼ��DMA��ͨ��
	  	
  DMA_Cmd(DMA1_Channel1,ENABLE);//����DMAͨ��
}

