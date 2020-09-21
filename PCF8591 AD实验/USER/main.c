/******************** (C) COPYRIGHT 2013 CEPARK多功能开发学习板********************
 * 文件名  ：main.c
 * 描述    ：CPU不断地读取PCF8591转换后的AD值，并将结果显示在LCD1602上，单位为mv，通
 			 过调节可调电阻，LCD1602上将显示不同的电压值。
 * 实验平台：CEPARK多功能开发学习板
 * 库版本  ：ST3.5.0
 * 硬件连接：----------------------
 * 单片机IO | PA8  - JP31 - RS     | LCD1602模块
 *          | PA9  - JP31 - RW     |
 *          | PA10 - JP31 - EN     |
 *           ----------------------
 * 硬件连接：----------------------
 * 单片机IO |  PA0 - JP33 - D0	   | LCD1602模块
						|  PA1 - JP33 - D1	   |
						|  PA2 - JP33 - D2	   |
						|  PA3 - JP33 - D3	   |
						|  PA4 - JP33 - D4	   |
						|  PA5 - JP33 - D5	   |
						|  PA6 - JP33 - D6	   |
						|  PA7 - JP33 - D7	   |
 *           ----------------------
 * 硬件连接：------------------------
 * 单片机IO |  PB10 - JP68 - SCL	   | AD/DA转换模块
						|  PB11 - JP68 - SDA	   |
 *           ------------------------
 * 硬件连接：JP66短接，用于AD显示；JP63，I0短接（上下），调节RT2，LCD上显示不同的值
 * 硬件连接：J3上端连接到核心板的J7（3.3V）
**********************************************************************************/

#include "stm32f10x.h"
#include "PCF8591.h"
#include "delay.h"
#include "iic.h"
#include "lcd1602.h"


/* 
 * 函数名：main
 * 描述  : 主函数
 * 输入  ：无
 * 输出  : 无
 */
int main(void)
{  			    
	u8 pcf8591_adchannel=0;
	u8 ad_temp=0,ad_result1,ad_result2,ad_result3,ad_result4;
	u16 ad_result=0;
	
	/* 设置系统时钟为72M */
  	SystemInit();
	
  	LCD1602_GPIO_Init();
	
	LCD1602_Init();
	
  	PCF8591_Init();			//IIC初始化 

	LCD1602_MoveToPosition(0,0);                 
  	LCD1602_DisplayString("PCF8591 AD TEST");  
  	 
  	LCD1602_MoveToPosition(1,0);
	LCD1602_DisplayString("AD Result:    mv");

	
										   
	while(1)
	{
		pcf8591_ad_write(0x40+pcf8591_adchannel);
    	ad_temp=pcf8591_ad_read();
    	ad_result=(ad_temp*5000)/256;
    	ad_result1=ad_result/1000;
    	ad_result2=ad_result%1000/100;
    	ad_result3=ad_result%100/10;
    	ad_result4=ad_result%10;
    	
    	LCD1602_DisplayOneCharOnAddr(1,10,ad_result1+0x30);
    	LCD1602_DisplayOneCharOnAddr(1,11,ad_result2+0x30);
    	LCD1602_DisplayOneCharOnAddr(1,12,ad_result3+0x30);
    	LCD1602_DisplayOneCharOnAddr(1,13,ad_result4+0x30);	
    	
	}
}




/******************* (C) COPYRIGHT 2013 CEPARK多功能开发学习板*****END OF FILE****/
