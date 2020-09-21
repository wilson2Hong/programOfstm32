#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "adc.h"
#include "dma.h"
#include "stm32f10x.h"
#include "beep.h"

#define D0 PBout(2)
void Rain_Do_GPIO_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

extern  uint16_t ADCConvertedValue;

int main(void)
{
	float ADC_ConvertedValueLocal;
	u16 temp;

	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	LED_Init();			     //LED端口初始化
	LCD_Init();			 	
 	Adc_Init();		  		//ADC初始化
	BEEP_Init();
	
	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(60,70,200,16,16,"ADC TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2015/1/14");	
	//显示提示信息
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(60,130,200,16,16,"ADC_CH0_VAL:");	      
	LCD_ShowString(60,150,200,16,16,"ADC_CH0_VOL:0.000V");		
	
	while(1)
	{
		LCD_ShowxNum(156,130,ADCConvertedValue,4,16,0);//显示ADC的值
		
		ADC_ConvertedValueLocal=(float)ADCConvertedValue*(3.3/4096);
	  temp=ADC_ConvertedValueLocal;
		LCD_ShowxNum(156,150,temp,1,16,0);//显示整数部分电压值
		
		//显示电压值的小数部分
		ADC_ConvertedValueLocal-=temp;
		ADC_ConvertedValueLocal*=1000;		
		LCD_ShowxNum(172,150,ADC_ConvertedValueLocal,3,16,0X80);
		printf("%d\n",ADCConvertedValue);
		
		
		if(ADCConvertedValue<4095)
		{
		printf("%s\n","下雨了");
    BEEP=1;				
		}
		else
		{ 
			printf("%s\n","雨停了");
			BEEP=0;
		}
		D0=1;
		LED0=!LED0;
		delay_ms(250);
  }
	
}
