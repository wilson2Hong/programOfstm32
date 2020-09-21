#include "pcf8591.h"
#include "delay.h"

//初始化IIC接口
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
	IIC_Send_Byte(pcf8591_read); //发送器件地址+读指令
  	data=IIC_Read_Byte(0);
  	IIC_Stop();
  	return(data*2);
	
}

void pcf8591_data_write(u8 data)
{
	IIC_Start();
  	IIC_Send_Byte(pcf8591_write); //发送器件地址+写指令 最后一位为0表示下一个字节往总线上写
  	IIC_Send_Byte(0x40);          //发送控制字节
  	IIC_Send_Byte(data);           //发送DA数值
  	IIC_Stop();
}

u8 pcf8591_data_read(void)
{
	u8 receive;
	IIC_Start();
  IIC_Send_Byte(pcf8591_read);//发送器件地址+读指令   最后以为为1表示下一个字节从总线上读 	
	receive = IIC_Read_Byte(0);
	IIC_Stop();
	 return receive;
	                             	
}
