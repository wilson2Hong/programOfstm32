#include "debug.h"
#include "BK_data_init.h"
#include "BK_RC.h"

int hhh = 0;
char tx_buf[32];

enum {
    NO_DEBUG = 0,
	DEBUG_RC,
	DEBUG_VC,
	DEBUG_QUATERNION,
};

#define DEBUG_MODE DEBUG_VC

void debug_send(void)
{
	static unsigned int index=0;
	union{
		float f[8];
		int16 i16[16];
		unsigned int u32[8];
		unsigned char u8[32];
	}q2pc;
	index++;

	if(DEBUG_MODE==NO_DEBUG)
	{
		q2pc.u8[0]=0x36;
		RF_StartTX_ACK(BK_DBG_RF_CHN,(char*)q2pc.u8,1);
	}
	
	if(DEBUG_MODE==DEBUG_RC)
	{
		sprintf(tx_buf,"\r\n%5d\t%5d\t%5d\t%5d\t%2x%2x\t",rawData[0],rawData[1],rawData[2],rawData[3],rawData[4],rawData[5]);
		RF_StartTX_ACK(BK_DBG_RF_CHN,tx_buf,31);
	}

	if(DEBUG_MODE==DEBUG_VC)
	{
		q2pc.u8[0] = 0x13;
		q2pc.u8[1] = 0x00;
		q2pc.u8[2] = 0x00;
		q2pc.u8[3] = 0x09;
		
		
		q2pc.i16[2] = rol.gyro_raw[0];
		q2pc.i16[3] = pit.gyro_raw[0];		
		q2pc.i16[4] = -yaw.gyro_raw[0];
		
		q2pc.i16[5] = -pit.accel_raw[0];
		q2pc.i16[6] = rol.accel_raw[0];
		q2pc.i16[7] = -yaw.accel_raw[0];
		
		RF_StartTX_ACK(BK_DBG_RF_CHN,(char*)q2pc.u8,32);
	}
	
	if(DEBUG_MODE==DEBUG_QUATERNION)	
	{
// 		q2pc.f[0]=Q.w;
// 		q2pc.f[1]=Q.x;
// 		q2pc.f[2]=Q.y;
// 		q2pc.f[3]=Q.z;

		q2pc.u8[16] = 0xAA;
		q2pc.u8[17] = 0xBB;
		q2pc.u8[18] = index&0xff;

		RF_StartTX_ACK(BK_DBG_RF_CHN,(char*)q2pc.u8,32);
	}
}
