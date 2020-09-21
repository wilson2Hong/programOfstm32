#ifndef __BK_MOTOR_H
#define __BK_MOTOR_H

#include "BK_Config.h"

#define MINTHROTTLE 4100
#define MAXTHROTTLE 8000
enum{
	MOTOR_YH=0,
	MOTOR_YQ=1,
	MOTOR_ZH=2,
	MOTOR_ZQ=3,
//	MOTOR_YH=2,
//	MOTOR_YQ=1,
//	MOTOR_ZH=0,
//	MOTOR_ZQ=3,
};
void writeMotor(uint32_t throttle, int32_t pidTermRoll, int32_t pidTermPitch, int32_t pidTermYaw);

void getPWM(uint16_t* pwm);

extern uint32_t motorPWM[4];
extern uint32_t motorAdj;
#endif





