/******************** (C) COPYRIGHT 2013 CEPARK�๦�ܿ���ѧϰ��********************
 * �ļ���  ��lcd1602.c
 * ����    ��lcd1602 Ӧ�ú�����
 *          
 * ʵ��ƽ̨��CEPARK�๦�ܿ���ѧϰ��
																				 
**********************************************************************************/

#include "lcd1602.h"	 
#include "delay.h"	


void LCD1602_GPIO_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
	
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/******************************************************************************
�������ƣ�LCD1602_WriteInformation
�������ܣ���LCD1602Һ��д�����ݻ�������
��ڲ�����ucData-Ҫд������ݻ����������
		  bComOrData-Ϊ0ʱд���ʱ���Ϊ1ʱд���ʱ����
����ֵ����
��ע����
*******************************************************************************/
void LCD1602_WriteInformation(u8 ucData,u8 bComOrData)	 
{
	DATAOUT(ucData);
	delay_us(20);
	if(bComOrData)
		RS_Set();
	else
		RS_Clr();
	delay_us(20);
	RW_Clr();
	delay_us(20);
	EN_Set();
	delay_us(20);
	EN_Clr();
	delay_us(200);
}

/******************************************************************************
�������ƣ�LCD1602_Init
�������ܣ�Һ����ʼ������
��ڲ�������
����ֵ����
��ע����
*******************************************************************************/
void LCD1602_Init(void)		 
{
	LCD1602_WriteInformation(0x38,0);
	delay_us(1000);
	LCD1602_WriteInformation(0x38,0);
	delay_us(1000);
	LCD1602_WriteInformation(0x38,0);
	delay_us(1000);
	LCD1602_WriteInformation(0x38,0); 	//д�����5x7��������ʽ��8λ���ݽӿ�
	delay_us(1000);
	LCD1602_WriteInformation(0x0c,0);	//��ʾ���ã�����ʾ����겻��ʾ������˸
	delay_us(1000);
	LCD1602_WriteInformation(0x01,0);	//����ָ��
	delay_us(1000);
}

/******************************************************************************
�������ƣ�LCD1602_MoveToPosition
�������ܣ���Һ���Ĺ���ƶ���ָ����λ��
��ڲ�����x-Һ����ʾ����������Χ0-1
			x = 0:��Һ���ĵ�һ��
			x = 1:��Һ���ĵڶ���
		  y-Һ����ʾ����������Χ0-15
		    y = 0:��Һ���ĵ�һ��
			y = 1:��Һ���ĵڶ���
			......
			y = 15:��Һ���ĵ�ʮ����
����ֵ����
��ע��ͨ��ָ��x,y��ֵ���Խ�Һ���Ĺ���ƶ���ָ����λ��
*******************************************************************************/
void LCD1602_MoveToPosition(u8 x,u8 y)	
{
	if(0 == x)
		LCD1602_WriteInformation((0x80 | y),0);	   //��궨λ����һ�е�y��
	if(1 == x)
		LCD1602_WriteInformation((0xC0 | y),0);	   //��궨�嵽�ڶ��е�y��
}

/******************************************************************************
�������ƣ�LCD1602_DisplayOneCharOnAddr
�������ܣ���ָ����λ������ʾָ�����ַ�
��ڲ�����x-Һ����ʾ����������Χ0-1
			x = 0:��Һ���ĵ�һ��
			x = 1:��Һ���ĵڶ���
		  y-Һ����ʾ����������Χ0-15
		    y = 0:��Һ���ĵ�һ��
			y = 1:��Һ���ĵڶ���
			......
			y = 15:��Һ���ĵ�ʮ����
		  ucData-Ҫ��ʾ���ַ�����
����ֵ����
��ע��ȷ��x,y��ȡֵҪ��ָ���ķ�Χ��
*******************************************************************************/
void LCD1602_DisplayOneCharOnAddr(u8 x,u8 y,u8 ucData)
{
	LCD1602_MoveToPosition(x,y);   //���λ��
	LCD1602_WriteInformation(ucData,1);	  //д������
}

/******************************************************************************
�������ƣ�LCD1602_DisplayString
�������ܣ���ʾ�ַ���
��ڲ�����ucStr-�ַ������׵�ַ
����ֵ����
��ע����
*******************************************************************************/
void LCD1602_DisplayString(u8 *ucStr)	
{
	while(*ucStr != '\0')	   //�ַ�������֮ǰ��ѭ����ʾ
	{
		 LCD1602_WriteInformation(*ucStr,1);	 //����д��ÿһ���ַ�
		 ucStr++;								 //ָ������
	}
}

























