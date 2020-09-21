#ifndef _ESC_CONTROL_H
#define _ESC_CONTROL_H
#include "stm32f4xx.h"
#include "sys.h"
#include "esc_control.hpp"
#include "led.hpp"
#include "stm32f4xx_tim.h"



#endif
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
void TIM3_CH1_Cap_Init(u32 arr,u16 psc);	
void TIM3_CH2_Cap_Init(u32 arr,u16 psc);	
void TIM3_CH3_Cap_Init(u32 arr,u16 psc);	
void TIM3_CH4_Cap_Init(u32 arr,u16 psc);
void TIM4_PWM_Init(u32 arr,u32 psc);

void esc_control();
bool channel_7_capture();
bool channel_8_capture();
#ifdef __cplusplus
}
#endif //__cplusplus
