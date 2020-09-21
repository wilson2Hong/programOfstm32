/******************** (C) COPYRIGHT 2013 CEPARK多功能开发学习板********************
 * 文件名  ：lcd1602.c
 * 描述    ：lcd1602 应用函数库
 *          
 * 实验平台：CEPARK多功能开发学习板
																				 
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
函数名称：LCD1602_WriteInformation
函数功能：向LCD1602液晶写入数据或者命令
入口参数：ucData-要写入的数据或者命令参数
		  bComOrData-为0时写入的时命令，为1时写入的时数据
返回值：无
备注：无
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
函数名称：LCD1602_Init
函数功能：液晶初始化函数
入口参数：无
返回值：无
备注：无
*******************************************************************************/
void LCD1602_Init(void)		 
{
	LCD1602_WriteInformation(0x38,0);
	delay_us(1000);
	LCD1602_WriteInformation(0x38,0);
	delay_us(1000);
	LCD1602_WriteInformation(0x38,0);
	delay_us(1000);
	LCD1602_WriteInformation(0x38,0); 	//写入命令，5x7点阵工作方式，8位数据接口
	delay_us(1000);
	LCD1602_WriteInformation(0x0c,0);	//显示设置，开显示，光标不显示，不闪烁
	delay_us(1000);
	LCD1602_WriteInformation(0x01,0);	//清屏指令
	delay_us(1000);
}

/******************************************************************************
函数名称：LCD1602_MoveToPosition
函数功能：将液晶的光标移动到指定的位置
入口参数：x-液晶显示的行数，范围0-1
			x = 0:在液晶的第一行
			x = 1:在液晶的第二行
		  y-液晶显示的列数，范围0-15
		    y = 0:在液晶的第一列
			y = 1:在液晶的第二列
			......
			y = 15:在液晶的第十六列
返回值：无
备注：通过指定x,y的值可以将液晶的光标移动到指定的位置
*******************************************************************************/
void LCD1602_MoveToPosition(u8 x,u8 y)	
{
	if(0 == x)
		LCD1602_WriteInformation((0x80 | y),0);	   //光标定位到第一行的y列
	if(1 == x)
		LCD1602_WriteInformation((0xC0 | y),0);	   //光标定义到第二行的y列
}

/******************************************************************************
函数名称：LCD1602_DisplayOneCharOnAddr
函数功能：在指定的位置上显示指定的字符
入口参数：x-液晶显示的行数，范围0-1
			x = 0:在液晶的第一行
			x = 1:在液晶的第二行
		  y-液晶显示的列数，范围0-15
		    y = 0:在液晶的第一列
			y = 1:在液晶的第二列
			......
			y = 15:在液晶的第十六列
		  ucData-要显示的字符数据
返回值：无
备注：确保x,y的取值要在指定的范围内
*******************************************************************************/
void LCD1602_DisplayOneCharOnAddr(u8 x,u8 y,u8 ucData)
{
	LCD1602_MoveToPosition(x,y);   //光标位置
	LCD1602_WriteInformation(ucData,1);	  //写入数据
}

/******************************************************************************
函数名称：LCD1602_DisplayString
函数功能：显示字符串
入口参数：ucStr-字符串的首地址
返回值：无
备注：无
*******************************************************************************/
void LCD1602_DisplayString(u8 *ucStr)	
{
	while(*ucStr != '\0')	   //字符串结束之前，循环显示
	{
		 LCD1602_WriteInformation(*ucStr,1);	 //依次写入每一个字符
		 ucStr++;								 //指针增加
	}
}

























