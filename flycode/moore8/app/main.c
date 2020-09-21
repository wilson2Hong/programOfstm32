
#include "BK_data_init.h"
#include "BK_RC.h"
#include "BK_adc.h"
#include "debug.h"


#include "..\drivers\BK_Drv_Nrf24l01.h"
#include "..\drivers\thread_imu.h"
#include "..\bk2471\drivers\timer\timer.h"

void Control(void);


int 	pit_offset 		= 0;		//	重力偏差值
int 	rol_offset  	= 0;		//	重力偏差值
int		THROTTLE_display;			//	油门输出值
float	THROTTLE_1G  	= 2000;		//	悬停时PWM输出值
float 	i_angle,fangun_angle;		//	翻滚角度变量和角度积分变量


t_AXIS pit, rol, yaw;	//三个轴的数据定义
int reset_flag=1;
int NoMove_f=1;


void app_imu_task(void)
{
	if(gyro_dataRdy==0)		return;	

	gyro_dataRdy=0;
	
	Control();	
	debug_send();				//无线调试输出函数	
	Pilot_Light();				//LED指示灯控制	
	Failsafe_Check();			//RF失联检测
}


void app_rx_task(void)
{
	if(bk2401_dataRdy==0)return;
	bk2401_dataRdy=0;

	Cal_Command();				//遥控数据处理
	check_sticks();				//摇杆位置检查
}



int FAST_CALL entry0_main(void)
{
	BK2471_Init();				//初始化MCU硬件设置
	IMU_Init();					//初始化IMU芯片寄存器（惯性测量单元）


//	Gyro_CALIBRATED=1;			//使能陀螺仪数据校正
	
	IMU_StartReadData();		//启动I2C数据读取进程
	
//	Gyro_CALIBRATED = 0;
	pit.gyro_bias = 0;
	rol.gyro_bias = 0;
	yaw.gyro_bias = 0;
	
	
	////////////////////////  凑代码长度适应无线烧录器,不然它会罢工 //////////////////////////
	pit.gyro_raw[0] = 1;
	pit.gyro_raw[1] = 1;
	pit.gyro_raw[2] = 1;
	pit.gyro_raw[3] = 1;
	pit.gyro_raw[4] = 1;
	pit.gyro_raw[5] = 1;
	pit.gyro_raw[6] = 1;
	pit.gyro_raw[7] = 1;
	pit.gyro_raw[8] = 1;
	pit.gyro_raw[9] = 1;
	pit.gyro_raw[10] = 1;
	pit.gyro_raw[11] = 1;
	pit.gyro_raw[12] = 1;
	pit.gyro_raw[13] = 1;
	pit.gyro_raw[14] = 1;
	pit.gyro_raw[15] = 1;
	pit.gyro_raw[16] = 1;
	pit.gyro_raw[17] = 1;
	pit.gyro_raw[18] = 1;
	pit.gyro_raw[19] = 1;
	
	////////////////////////  凑代码长度 //////////////////////////

	while(1)
	{
		app_imu_task();
		app_rx_task();
	}
}

int FAST_ENTRY0 main(void)
{
	__asm volatile
	{
		bl entry0_main
	};
	return 0;
}
