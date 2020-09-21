#ifndef __BK_DRV_PWM_H__
#define __BK_DRV_PWM_H__

//#include "board.h"
#include "..\bk2471\includes\types.h"
#include "..\bk2471\drivers\pwm\pwm.h"
#define MAXMOTORS 4

enum{
	PWM_LF=PWM3,
	PWM_LB=PWM2,
	PWM_RF=PWM1,
	PWM_RB=PWM0,

	PWM_ZQ=PWM3,
	PWM_ZH=PWM2,
	PWM_YQ=PWM1,
	PWM_YH=PWM0,

};

void Pwm_out_Init(uint16_t hz);

void Pwm_SetPwm(uint32_t pwm[MAXMOTORS]);
extern const uint8 tblPwmChn[];
extern int16 pwmCoef;

#endif

