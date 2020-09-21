#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "myiic.h"
#include "PCF8591.h"
int main(void)
{
	
	//u8 pcf8591_adchannel=0;
	u8 ad_temp=0,ad_result1,ad_result2,ad_result3,ad_result4;
	u16 ad_result=0;
	
	pcf8591_Init();
	uart_init(115200);
	
	while(1)
	{
		pcf8591_data_write(0x08);
//    	ad_temp= pcf8591_data_read();
//    	ad_result=(ad_temp*5000)/256;
//    	ad_result1=ad_result/1000;
//    	ad_result2=ad_result%1000/100;
//    	ad_result3=ad_result%100/10;
//    	ad_result4=ad_result%10;
//    
//		printf("%d",ad_result1);
//		printf("%d",ad_result2);
//		printf("%d",ad_result3);
//		printf("%d",ad_result4);
//		delay_ms(100);
	}
	
	
	
}

