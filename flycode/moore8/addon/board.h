
#ifndef __BOARD_H__
#define __BOARD_H__

// #include "string.h"

#define ARMAPI extern "C"



#include "BK_Config.h"
#include "BK_Drv_LED.h"
#include "BK_Drv_MPU6050.h"
#include "BK_Drv_Nrf24l01.h"
#include "BK_Drv_PWM.h"
#include "BK_Drv_EEPROM.h"

void BK2471_Init(void);
int SysTick_IRQ(void);
uint32_t GetSysTime_us(void);

#define BOARD_x_MODE		BIT(8)
#define BOARD_10_MODE		0
#define BOARD_Benteli		1
#define BOARD_ABE			2
#define BOARD_TYPE			(BOARD_x_MODE|BOARD_Benteli)

#endif /* __BOARD_H__ */

// 




