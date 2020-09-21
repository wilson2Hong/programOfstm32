#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "stm32f10x.h"
#include "i2c_ee.h"

#define  EEP_Firstpage      0x00
u8 I2c_Buf_Write[256];
u8 I2c_Buf_Read[256];

void I2C_Test(void);

float ADC_ConvertedValueLocal;

extern uint16_t ADCConvertedValue;

int main(void)
{
	
	//float ADC_ConvertedValueLocal;

	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();			     //LED端口初始化
	//LCD_Init();
  Adc_Init();	
 	
	/* I2C 外设初(AT24C02)始化 */
	I2C_EE_Init();
	
	printf( "\r\n 这是一个I2C外设(AT24C02)读写测试例程 \r\n");
	printf("\r\n ("__DATE__ " - " __TIME__ ") \r\n");
	
	I2C_Test();
	
//	POINT_COLOR=RED;//设置字体为红色 
//	LCD_ShowString(60,50,200,16,16,"WarShip STM32");	
//	LCD_ShowString(60,70,200,16,16,"ADC TEST");	
//	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
//	LCD_ShowString(60,110,200,16,16,"2015/1/14");	
//	//显示提示信息
//	POINT_COLOR=BLUE;//设置字体为蓝色
//	LCD_ShowString(60,130,200,16,16,"ADC_CH0_VAL:");	      
//	LCD_ShowString(60,150,200,16,16,"ADC_CH0_VOL:0.000V");		
	
	while(1)
	{
//		LCD_ShowxNum(156,130,ADCConvertedValue,4,16,0);//显示ADC的值
//		
//		LCD_ShowxNum(156,150,ADCConvertedValue,1,16,0);//显示电压值
//		
//		//显示电压值的小数部分		
//		LED0=!LED0;
//		delay_ms(250);
		
		
  }	
}



void I2C_Test(void)
{
	u16 i;

	printf("写入的数据\n\r");
    
	for ( i=0; i<=255; i++ ) //填充缓冲
  {   
    I2c_Buf_Write[i] = ADCConvertedValue;

    printf("0x%02X ", I2c_Buf_Write[i]);
    if(i%16 == 15)    
        printf("\n\r");    
   }

  //将I2c_Buf_Write中顺序递增的数据写入EERPOM中 
	I2C_EE_BufferWrite( I2c_Buf_Write, EEP_Firstpage, 256);	 
  
  printf("\n\r读出的数据\n\r");
  //将EEPROM读出数据顺序保持到I2c_Buf_Read中 
	I2C_EE_BufferRead(I2c_Buf_Read, EEP_Firstpage, 256); 

  //将I2c_Buf_Read中的数据通过串口打印
	for (i=0; i<256; i++)
	{	
		if(I2c_Buf_Read[i] != I2c_Buf_Write[i])
		{
			printf("0x%02X ", I2c_Buf_Read[i]);
			printf("错误:I2C EEPROM写入与读出的数据不一致\n\r");
			return;
		}
    printf("0x%02X ", I2c_Buf_Read[i]);
    if(i%16 == 15)    
        printf("\n\r");
    
	}
  printf("I2C(AT24C02)读写测试成功\n\r");
}
