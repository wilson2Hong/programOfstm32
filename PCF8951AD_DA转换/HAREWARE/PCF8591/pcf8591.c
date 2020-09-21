#include "pcf8591.h"
#include "delay.h"

//��ʼ��IIC�ӿ�
void pcf8591_Init(void)
{
	IIC_Init();
}

void pcf8591_addr_write(u8 addr)
{
  IIC_Start();
	IIC_Send_Byte(pcf8591_write);
	IIC_Send_Byte(addr);
	IIC_Stop();
}

u8 pcf8591_addr_read(void)
{
	u8 data;
	IIC_Start();
	IIC_Send_Byte(pcf8591_read); //����������ַ+��ָ��
  	data=IIC_Read_Byte(0);
  	IIC_Stop();
  	return(data*2);
	
}

void pcf8591_data_write(u8 data)
{
	IIC_Start();
  	IIC_Send_Byte(pcf8591_write); //����������ַ+дָ�� ���һλΪ0��ʾ��һ���ֽ���������д
  	IIC_Send_Byte(0x40);          //���Ϳ����ֽ�
  	IIC_Send_Byte(data);           //����DA��ֵ
  	IIC_Stop();
}

u8 pcf8591_data_read(void)
{
	u8 receive;
	IIC_Start();
  IIC_Send_Byte(pcf8591_read);//����������ַ+��ָ��   �����ΪΪ1��ʾ��һ���ֽڴ������϶� 	
	receive = IIC_Read_Byte(0);
	IIC_Stop();
	 return receive;
	                             	
}
