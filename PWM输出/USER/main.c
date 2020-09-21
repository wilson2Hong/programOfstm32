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
 	 u16 led0pwmval=15;
   u8	 dir=1;
   delay_init();
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	 uart_init(115200);	 //串口初始化为115200
	 LED_Init();
	//KEY_Init();
	 TIM3_PWM_Init(30,7199);
	 
	 while(1)
	 {
     delay_ms(10);
		 if(dir==1)led0pwmval++;
		 else led0pwmval--;
		 
		 if(led0pwmval>20)dir=0;
		 if(led0pwmval==10)dir=1;
		 
		TIM_SetCompare2(TIM3,led0pwmval); 	 
	 } 
 }


