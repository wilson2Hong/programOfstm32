#include "inlet_outlet_valve.hpp"
#include "stm32f4xx_tim.h"
#include "main.h"
#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
int open_pwm_value1=2400,open_pwm_value2=2400,close_pwm_value1=750,close_pwm_value2=750;

//初始化PA1为输出口.并使能时钟		    
//风扇 IO初始化
void FAN_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟

  //GPIOF9,F10初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);//设置低，继电器常开

}
	 
	 
void open_valve()//打开进气气阀
{		
			TIM_SetCompare3(TIM4,open_pwm_value2);
			TIM_SetCompare4(TIM4,open_pwm_value1);
			FAN = 1;																//风扇继电器常开闭合
			delay_nms(1000);
}
void close_valve()//关闭进气阀
{
			TIM_SetCompare3(TIM4,close_pwm_value2);
			TIM_SetCompare4(TIM4,close_pwm_value1);
			FAN = 0;																//风扇继电器常开断开
			delay_nms(1000);
//			TIM_SetCompare3(TIM4,750);
//			TIM_SetCompare4(TIM4,750);
//			delay_nms(1000);
}	 

#ifdef __cplusplus
}
#endif //__cplusplus
