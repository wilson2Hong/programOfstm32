#include<stdio.h>
#include "BK_RC.h"
#include "BK_data_init.h"
//#include "..\bk2471\drivers\uart\uart.h"
#include "debug.h"
#include "..\drivers\thread_imu.h"


uint8 rawData[16];
float remote_THROTTLE;

uint8 keyold_R[6];
uint8 keyold_L[6];

uint8 key_L[6];
uint8 key_R[6];
#define STEP_OFFSET 1	//1大约0.1°



float remote_cal(unsigned char raw)
{
	float tmp;
	tmp = raw - RC_MID;
	if(tmp>15)
	{
		tmp -= 15;		
	}
	else if(tmp<-15)
	{
		tmp += 15;
	}
	else
	{
		tmp = 0;
	}

	return tmp;
}


extern void HwSoftReset(void);
void Cal_Command(void)
{
	u8 i;

	rol.remote = remote_cal(rawData[0]);
	pit.remote = remote_cal(rawData[1]);
	yaw.remote = remote_cal(rawData[2]);

//	Func_NoHeaderMode();

//	remote_THROTTLE = THROTTLE_func(rawData[3]*4);
	if(rawData[3]>10)
	{
	remote_THROTTLE = (float)rawData[3]*8+800;
	}
	else
	{
		remote_THROTTLE = 0;
	}

	for(i=0;i<6;i++)
	{
		keyold_L[i] = keyold_L[i]<<1;
		if((rawData[4]>>(i)) & 0x01)
		{
			keyold_L[i] |=0x01;
			if((keyold_L[i]&0x02)==0)	key_L[i] = 0x01;	//如果之前是0,bit0置1,检测上升沿;
		}
		
		keyold_R[i] = keyold_R[i]<<1;
		if((rawData[5]>>(i)) & 0x01)	
		{
			keyold_R[i] |= 0x01;
			if((keyold_R[i]&0x02)==0)	key_R[i] = 0x01;	//如果之前是0,bit0置1,检测上升沿;
		}
	}

	if(key_R[0]==1)
	{
		key_R[0]=0;					//清除按键标志
	}
	

	
	if(key_L[0]==1)
	{
		static int key_update = 0;
		key_L[0] = 0;
		
		key_update++;
		if(key_update>=2)
		{
			char update_flag = 0x0c;
			IMU_RequestStopping();
			IMU_WaitStoppedStatus();
			
			dFlashEn =1;
			flash_set_line_mode(1);
			Flash_Write(0x7c000, &update_flag, 1);
			dFlashEn = 0;
			HwSoftReset();
			while(1);				
		}
	}
	
	if(key_R[1]==1)
	{
		key_R[1]=0;
//		pit_offset -= STEP_OFFSET;
	}
	
	if(key_R[4]==1)
	{
		key_R[4]=0;
//		pit_offset += STEP_OFFSET;
	}
	
	if(key_R[2]==1)
	{
		key_R[2]=0;
//		rol_offset -= STEP_OFFSET;
	}
	
	if(key_R[3]==1)
	{
		key_R[3]=0;
//		rol_offset += STEP_OFFSET;
	}

	if(key_L[1]==1)
	{
		key_L[1]=0;		
	}
	
	if(key_L[4]==1)
	{
		key_L[4]=0;		
	}
	
	if(key_L[2]==1)
	{
		key_L[2]=0;		
	}	
	
	if(key_L[5]==1)
	{
		key_L[5]=0;	
	}	
	
	if(key_L[3]==1)
	{
		key_L[3]=0;

	}
}

const uint8_t stick_min_flag[4] = {1<<0,1<<2,1<<4,1<<6};
const uint8_t stick_max_flag[4] = {1<<1,1<<3,1<<5,1<<7};
#define ROL_L 0x01
#define ROL_H 0x02
#define PIT_L 0x04
#define PIT_H 0x08
#define YAW_L 0x10
#define YAW_H 0x20
#define THR_L 0x40
#define THR_H 0x80

int8 fbStartUnlock=0;
int8 fbWaitThrHigh=0;
int8 fbWaitThrLow=0;

void check_sticks(void)
{
	int i;
	static uint8_t rcDelayCommand;
	static uint8_t stick_flag = 0;

	for (i = 0; i < 4; i++)
	{
		if (rawData[i] < RC_MINCHECK)
			stick_flag |= stick_min_flag[i];  // check for MIN
		else
			stick_flag &= ~stick_min_flag[i];

		if (rawData[i] > RC_MAXCHECK)
			stick_flag |= stick_max_flag[i];  // check for MAX
		else
			stick_flag &= ~stick_max_flag[i];  // check for MAX
	}

	if(stick_flag&0xff)
	{	//如果任一摇杆在最大或最小位置
		if(rcDelayCommand < 250)
			rcDelayCommand++;
	}
	else
	{
		rcDelayCommand = 0;
		stick_flag &= 0;
	}

	if(fbStartUnlock){
		if(fbWaitThrLow){
			if((stick_flag&THR_L)==THR_L){
				fbWaitThrLow=0;
				fbStartUnlock=0;
				ARMED=1;
			}
		}
		if(fbWaitThrHigh){
			if((stick_flag&THR_H)==THR_H){
				fbWaitThrLow=1;
				fbWaitThrHigh=0;
			}
		}
	}
	if (rcDelayCommand == 100)
	{ //2s: 20ms * 100
		if (ARMED)
		{ //如果已经处于解锁状态
			if((stick_flag&(YAW_L|THR_L|ROL_L|PIT_L))==(YAW_L|THR_L|ROL_L|PIT_L))
			{
				ARMED = 0;	//上锁
			}
		}
		else
		{
			if((stick_flag & YAW_H)&&(stick_flag & THR_L))
			{//左摇杆，右下角解锁
				ARMED = 1;	//解锁
			}
			
		}
		if((stick_flag&(YAW_L|THR_H|ROL_H|PIT_L))==(YAW_L|THR_H|ROL_H|PIT_L))
		{
			Gyro_CALIBRATED=1;
		}
		stick_flag &= 0;
		rcDelayCommand = 0;
	}
}

void Data_Receive_Anl(u8 *data_buf,u8 num)
{
	u8 sum = 0;
	
	if(!(*(data_buf)==0xAA && *(data_buf+1)==0xAF))		return;		//判断帧头
	
	for(u8 i=0;i<(num-1);i++)
		sum += *(data_buf+i);	
	if(!(sum==*(data_buf+num-1)))		return;		//判断sum	
	
	failsafeCnt = 0;

	//遥控器数据，格式：AA AF 03 8*2+2 [...] chk

	rawData[2] 	= 255-(*(data_buf+2));	//yaw
	rawData[3]  = 255-(*(data_buf+3));	//throttle
	rawData[1]  = 255-(*(data_buf+4));	//pit
	rawData[0] 	= 255-(*(data_buf+5));	//roll
	rawData[4]	= *(data_buf+6);
	rawData[5] 	= *(data_buf+7);
}

void Failsafe_Check(void)
{
	if(failsafeCnt > 500)
	{
		failsafeCnt = 0;
		ARMED = 0;
	}
	failsafeCnt++;
}
