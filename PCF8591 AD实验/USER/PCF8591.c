
#include "PCF8591.h"
#include "delay.h"

//**********************************PCF8591操作函数****************************

//初始化IIC接口
void PCF8591_Init(void)
{
	IIC_Init();
}

void pcf8591_ad_write(u8 c)
{
  	IIC_Start();
  	IIC_Send_Byte(pcf8591_write); //发送器件地址+写指令
  	IIC_Send_Byte(c);
  	IIC_Stop();
}

u8 pcf8591_ad_read(void)
{
  	u8 dat;
  	IIC_Start();
  	IIC_Send_Byte(pcf8591_read); //发送器件地址+读指令
  	dat=IIC_Read_Byte(0);
  	IIC_Stop();
  	return(dat*2);
}

void pcf8591_da_write(u8 dat)
{
  	IIC_Start();
  	IIC_Send_Byte(pcf8591_write); //发送器件地址+写指令
  	IIC_Send_Byte(0x40);          //发送控制字节
  	IIC_Send_Byte(dat);           //发送DA数值
  	IIC_Stop();
}


