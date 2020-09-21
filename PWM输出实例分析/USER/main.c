#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
 
/************************************************
 ALIENTEK战舰STM32开发板实验9
 PWM输出实验  
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
 
 
 
0.5ms--------------0度;
1.0ms------------45度;
1.5ms------------90度;
2.0ms-----------135度;
2.5ms-----------180度;
************************************************/

	
 int main(void)
 {		
 TIM3_PWM_Init(1000,0,500,375,250,125);//arr=1000; 预分频系数psc=0；
	 while(1)
	 {
	 }
 }


