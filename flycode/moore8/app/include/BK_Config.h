#ifndef __BK_CONFIG_H
#define __BK_CONFIG_H

#include "board.h"
#include "BK_IMU.h"
#include "BK_Motor.h"
#include "BK_RC.h"

#define BK_DBG_RF_CHN			80
#define FBM320_EN 0
#define SPL0601_EN 1

extern uint8_t ARMED;
extern u16 failsafeCnt;
void Pilot_Light(void);			//Ö¸Ê¾µÆ
#endif

