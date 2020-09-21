#ifndef __LCD1602_H
#define __LCD1602_H			


#include "stm32f10x.h"
		    						  
//-----------------OLED端口定义----------------  					   

#define RS_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_8)
#define RS_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_8)

#define RW_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_9)
#define RW_Set() GPIO_SetBits(GPIOA,GPIO_Pin_9)

#define EN_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_10)
#define EN_Set() GPIO_SetBits(GPIOA,GPIO_Pin_10)


//PA0~7,作为数据线
#define DATAOUT(x)  GPIO_Write(GPIOA,x);//输出  



void LCD1602_GPIO_Init(void);
void LCD1602_WriteInformation(u8 ucData,u8 bComOrData);
void LCD1602_Init(void);
void LCD1602_MoveToPosition(u8 x,u8 y);
void LCD1602_DisplayOneCharOnAddr(u8 x,u8 y,u8 ucData);
void LCD1602_DisplayString(u8 *ucStr);


#endif  
	 



