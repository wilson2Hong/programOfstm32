#ifndef __LED_H
#define __LED_H
#include "sys.h" 
#include "stm32f4xx_adc.h" 

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
//LED端口定义
#define LED0 PAout(6)	// D2
#define LED1 PAout(7)	// D3	 
#define BEEP PAout(0)	// D3	 
	 
void LED_Init(void);//初始化	
void Beep_Init(void);//初始化	
#ifdef __cplusplus
}
#endif //__cplusplus
	 				    
#endif

