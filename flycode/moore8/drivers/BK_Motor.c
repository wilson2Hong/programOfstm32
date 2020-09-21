#include "BK_Motor.h"

//const uint8 tblPwmChn[]={PWM2,PWM1,PWM3,PWM0};//本特利x模式

#ifdef GYRO_MPU6050
#if 1
const uint8 tblPwmChn[]={PWM5,PWM4,PWM0,PWM3};//本特利x模式
//const uint8 tblPwmChn[]={PWM10,PWM11,PWM3,PWM0};//abe
#else
const uint8 tblPwmChn[]={PWM0,PWM5,PWM3,PWM4};// 90°
//const uint8 tblPwmChn[]={PWM5,PWM3,PWM0,PWM4};//本特利x模式
#endif
#endif

//const uint8 tblPwmChn[]={PWM5,PWM4,PWM3,PWM0};//ST
#ifdef GYRO_LSM6DS33
const uint8 tblPwmChn[]={PWM3,PWM0,PWM4,PWM5};//ST new
#endif
int16 pwmCoef=0;
void Pwm_out_Init(uint16_t hz)
{
	int i,j;
	for(i=0;i<sizeof(tblPwmChn);i++)
	{
		j=tblPwmChn[i];		
		PWM_SetupIOL(BIT(j));				//将pwm使用的io脚第二功能打开		
		PWM_OPEN_CLOCK(j,PWM_CLKSEL_DPLL);	//PWM_OPEN_CLOCK(j,PWM_CLKSEL_16M);//打开pwm 时钟源		
		PWM_Setup(j, 1, 4000+i*6, 0);			//配置pwm参数		
		PWM_Open(j);						//打开pwm
	}
}

void Pwm_SetPwm(uint32_t pwm[MAXMOTORS])
{
	int i,j;
	int t;
	for(i=0;i<sizeof(tblPwmChn);i++)
	{
		j=tblPwmChn[i];
		t=pwm[i];
		if(t>=4000)t=3999;
		if(t<0)t=0;
		PWM_SET_DUTY(j,1,t);
	}
}

long constrain_int32(long amt, long low, long high)
{
	return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

// BK_Motor motor;
uint32_t motorPWM[MAXMOTORS];
uint32_t motorAdj=0;

extern int hhh;
void writeMotor(uint32_t throttle, int32_t pidTermRoll, int32_t pidTermPitch, int32_t pidTermYaw)
{
//	throttle+=motorAdj;
//	hhh = throttle;
	
	throttle = throttle+4000;

	motorPWM[MOTOR_YH] = throttle - pidTermRoll + pidTermPitch - pidTermYaw; //后右
	motorPWM[MOTOR_YQ] = throttle - pidTermRoll - pidTermPitch + pidTermYaw; //前右
	motorPWM[MOTOR_ZH] = throttle + pidTermRoll + pidTermPitch + pidTermYaw; //后左
	motorPWM[MOTOR_ZQ] = throttle + pidTermRoll - pidTermPitch - pidTermYaw; //前左

	int32_t maxMotor = motorPWM[0];
	for (u8 i = 1; i < MAXMOTORS; i++)
		if (motorPWM[i] > maxMotor)		maxMotor = motorPWM[i];

	for (u8 i = 0; i < MAXMOTORS; i++)
	{
		if (maxMotor > MAXTHROTTLE)			motorPWM[i] -= maxMotor - MAXTHROTTLE;
		
		motorPWM[i] = constrain_int32(motorPWM[i], MINTHROTTLE, MAXTHROTTLE);	//限制电机PWM的最小和最大值
		motorPWM[i] -=4000; 
	}

	if(!ARMED || rawData[3] < 10)		//如果未解锁，则将电机输出设置为最低
	{
		motorPWM[0] = 0;
		motorPWM[1] = 0;
		motorPWM[2] = 0;
		motorPWM[3] = 0;
	}
	Pwm_SetPwm(motorPWM);						//写入电机PWM
}
