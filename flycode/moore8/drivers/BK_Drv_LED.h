#ifndef __BK_DRV_LED_H__
#define __BK_DRV_LED_H__

#include "board.h"
#include "..\bk2471\includes\types.h"
#include "..\bk2471\drivers\gpio\gpio.h"
/***************LED GPIO∂®“Â******************/
#define BK_GPIO_LED		GPIO0
#define BK_Pin_LEDA			BIT(7)
#define BK_Pin_LEDB			BIT(7)

// #define BK_GPIO_LED		GPIO3
// #define BK_Pin_LEDA			BIT(0)
// #define BK_Pin_LEDB			BIT(1)

#define DBG_PORT			GPIO0
#define DBG_PIN_0			2
#define DBG_PIN_1			3
#define DBG_PIN_2			4
#define DBG_PIN_3			5
#define DBG_PIN_4			6
#define DBG_PIN_5			7

void Led_Init(void);

void Led_ON(void);

void Led_OFF(void);

#endif

