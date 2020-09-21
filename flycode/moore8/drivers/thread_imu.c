#include <stdio.h>
#include <math.h>
#include <string.h>
#include "BK_Config.h"
#include "..\bk2471\includes\types.h"
#include "..\bk2471\drivers\timer\timer.h"
#include "..\bk2471\drivers\i2c\i2c0.h"
#include "..\bk2471\drivers\uart\uart.h"
#include "..\bk2471\common\common.h"
#include "BK_data_init.h"

#define MPU6050_ADDRESS         0x68
#define MPU_RA_ACCEL_XOUT_H     0x3B

uint8 sensor_raw_data[16];

char fbm_buf[6];
char fbm_cmd;
char gyro_dataRdy;
char fbm320_tempRdy;
char fbm320_pressRdy;
volatile char fb_stopThread=0;
extern int16 acc_raw[3];
extern int16 gyro_raw[3];


//在I2C读取完成后,把陀螺仪原始的byte数据,组合为short型数据
void Cbk_6050Gotten()
{
	int16* p;
	gyro_dataRdy=1;
	p = (int16*)sensor_raw_data;
 	BigEndian2Little(p,8);

	pit.accel_raw[0] =  p[1];
	rol.accel_raw[0] = -p[0];
	yaw.accel_raw[0] = -p[2];

	pit.gyro_raw[0] = p[4];
	rol.gyro_raw[0] = p[5];
	yaw.gyro_raw[0] = p[6];	
}

//定时器2ms中断回调函数,简单理解也就是2ms运行一次,任务是启动I2C读取陀螺仪数据
int Cbk_IMU_2ms()
{
	TCallback cbk = Cbk_6050Gotten;

	I2c_StartRcvBytes(MAKE_TWI_MODE(MPU6050_ADDRESS, I2C0),MPU_RA_ACCEL_XOUT_H,(char*)sensor_raw_data,14,cbk,NULL);
	
	if(fb_stopThread==1)
		fb_stopThread=0;
	return(0);
}


//设置2ms定时器中断,并启动I2C读取进程Cbk_IMU_2ms();
void IMU_StartReadData(void)
{
	gyro_dataRdy=0;
	memset(fbm_buf,0,sizeof(fbm_buf));
	memset(sensor_raw_data,0,sizeof(sensor_raw_data));

	Timer_SetTO_16M(TIMER0,TIMER_SRC16M_Nus(1999),1);	
	Timer_SetCbk(TIMER0,Cbk_IMU_2ms);
}

//发信号停止I2C进程,终止I2C进程的继续运行
void IMU_RequestStopping(void)
{
	fb_stopThread=1;
}

//等待I2C结束
void IMU_WaitStoppedStatus(void)
{
	while(fb_stopThread>0);
}
