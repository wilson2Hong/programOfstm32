#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

#define KEY2 PEin(2)
#define KEY1 PEin(3)
#define KEY0 PEin(4)
#define WK_UP PAin(0)

//#define KEY2 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)
//#define KEY1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
//#define KEY0 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
//#define WK_UP GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)

#define KEY0_PRESS 1
#define KEY1_PRESS 2
#define KEY2_PRESS 3
#define WKUP_PRESS 4

void KEY_Init(void);

u8 KEY_Scan(u8);
#endif
