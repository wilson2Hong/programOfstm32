#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr,u16 psc,u16 CCR1_Val,u16 CCR2_Val,u16 CCR3_Val,u16 CCR4_Val);
#endif
