#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "exti.h"
 
/************************************************
 ALIENTEK战舰STM32开发板实验9
 PWM输出实验之音乐播放
 KEY2:播放千与千寻
 KEY1:播放你离开南京，从此没人和我说话
 key0:播放生日快乐
 WK_UP:控制蜂鸣器(未实现)
 BUG:有时按键KEY0后播放生日快乐结束后，会继续播放KEY1,KEY2所对应的音乐
 问题：为什么WK_UP键不能控制音乐的播放
 休止符未解决
 ②STM32电源开关开启后会自动播放KEY2键对应音乐
 
 
 ③错误：multiply define symbol  因为在music.h中定义int music_data[]{} 错误 int music_data[]={}正确

************************************************/	
	
 int main(void)
 {		
	 delay_init();
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	 uart_init(115200);
	 BEEP_Init();  
	 LED_Init();
	 EXTIX_Init();
	 KEY_Init();
 	 LED0=0;
	 LED1=1; 
	 while(1)
	 {
		
		 printf("OK\r\n");	
		 delay_ms(1000);	 
		
   }
 }
 
