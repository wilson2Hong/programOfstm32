
#ifdef GYRO_MPU6050

#include <string.h>
#include <stdio.h>

#include "..\bk2471\includes\types.h"
#include "..\bk2471\common\common.h"
#include "..\bk2471\drivers\i2c\i2c0.h"

#include "BK_data_init.h"

#include "BK_Drv_MPU6050.h"
// MPU6050, HW I2C addr : 0x68(0xD0, AD0=Low),  0x69(0xD2, AD0=High)硬件I2c地址 0x68，模拟i2c地址0xD0   AD0高电平时地址为0x69 模拟IIC地址0xD2
#define MPU6050_ADDRESS         0x68
#define MPU60x0_Addr			MPU6050_ADDRESS
//0xD0	//

#define DMP_MEM_START_ADDR 0x6E
#define DMP_MEM_R_W 0x6F

#define MPU_RA_XG_OFFS_TC       0x00    //[7] PWR_MODE, [6:1] XG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU_RA_YG_OFFS_TC       0x01    //[7] PWR_MODE, [6:1] YG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU_RA_ZG_OFFS_TC       0x02    //[7] PWR_MODE, [6:1] ZG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU_RA_X_FINE_GAIN      0x03    //[7:0] X_FINE_GAIN
#define MPU_RA_Y_FINE_GAIN      0x04    //[7:0] Y_FINE_GAIN
#define MPU_RA_Z_FINE_GAIN      0x05    //[7:0] Z_FINE_GAIN
#define MPU_RA_XA_OFFS_H        0x06    //[15:0] XA_OFFS
#define MPU_RA_XA_OFFS_L_TC     0x07
#define MPU_RA_YA_OFFS_H        0x08    //[15:0] YA_OFFS
#define MPU_RA_YA_OFFS_L_TC     0x09
#define MPU_RA_ZA_OFFS_H        0x0A    //[15:0] ZA_OFFS
#define MPU_RA_ZA_OFFS_L_TC     0x0B
#define MPU_RA_PRODUCT_ID       0x0C    // Product ID Register
#define MPU_RA_XG_OFFS_USRH     0x13    //[15:0] XG_OFFS_USR
#define MPU_RA_XG_OFFS_USRL     0x14
#define MPU_RA_YG_OFFS_USRH     0x15    //[15:0] YG_OFFS_USR
#define MPU_RA_YG_OFFS_USRL     0x16
#define MPU_RA_ZG_OFFS_USRH     0x17    //[15:0] ZG_OFFS_USR
#define MPU_RA_ZG_OFFS_USRL     0x18
#define MPU_RA_SMPLRT_DIV       0x19
#define MPU_RA_CONFIG           0x1A
#define MPU_RA_GYRO_CONFIG      0x1B
#define MPU_RA_ACCEL_CONFIG     0x1C
#define MPU_RA_FF_THR           0x1D
#define MPU_RA_FF_DUR           0x1E
#define MPU_RA_MOT_THR          0x1F
#define MPU_RA_MOT_DUR          0x20
#define MPU_RA_ZRMOT_THR        0x21
#define MPU_RA_ZRMOT_DUR        0x22
#define MPU_RA_FIFO_EN          0x23
#define MPU_RA_I2C_MST_CTRL     0x24
#define MPU_RA_I2C_SLV0_ADDR    0x25
#define MPU_RA_I2C_SLV0_REG     0x26
#define MPU_RA_I2C_SLV0_CTRL    0x27
#define MPU_RA_I2C_SLV1_ADDR    0x28
#define MPU_RA_I2C_SLV1_REG     0x29
#define MPU_RA_I2C_SLV1_CTRL    0x2A
#define MPU_RA_I2C_SLV2_ADDR    0x2B
#define MPU_RA_I2C_SLV2_REG     0x2C
#define MPU_RA_I2C_SLV2_CTRL    0x2D
#define MPU_RA_I2C_SLV3_ADDR    0x2E
#define MPU_RA_I2C_SLV3_REG     0x2F
#define MPU_RA_I2C_SLV3_CTRL    0x30
#define MPU_RA_I2C_SLV4_ADDR    0x31
#define MPU_RA_I2C_SLV4_REG     0x32
#define MPU_RA_I2C_SLV4_DO      0x33
#define MPU_RA_I2C_SLV4_CTRL    0x34
#define MPU_RA_I2C_SLV4_DI      0x35
#define MPU_RA_I2C_MST_STATUS   0x36
#define MPU_RA_INT_PIN_CFG      0x37
#define MPU_RA_INT_ENABLE       0x38
#define MPU_RA_DMP_INT_STATUS   0x39
#define MPU_RA_INT_STATUS       0x3A
#define MPU_RA_ACCEL_XOUT_H     0x3B
#define MPU_RA_ACCEL_XOUT_L     0x3C
#define MPU_RA_ACCEL_YOUT_H     0x3D
#define MPU_RA_ACCEL_YOUT_L     0x3E
#define MPU_RA_ACCEL_ZOUT_H     0x3F
#define MPU_RA_ACCEL_ZOUT_L     0x40
#define MPU_RA_TEMP_OUT_H       0x41
#define MPU_RA_TEMP_OUT_L       0x42
#define MPU_RA_GYRO_XOUT_H      0x43
#define MPU_RA_GYRO_XOUT_L      0x44
#define MPU_RA_GYRO_YOUT_H      0x45
#define MPU_RA_GYRO_YOUT_L      0x46
#define MPU_RA_GYRO_ZOUT_H      0x47
#define MPU_RA_GYRO_ZOUT_L      0x48
#define MPU_RA_EXT_SENS_DATA_00 0x49
#define MPU_RA_MOT_DETECT_STATUS    0x61
#define MPU_RA_I2C_SLV0_DO      0x63
#define MPU_RA_I2C_SLV1_DO      0x64
#define MPU_RA_I2C_SLV2_DO      0x65
#define MPU_RA_I2C_SLV3_DO      0x66
#define MPU_RA_I2C_MST_DELAY_CTRL   0x67
#define MPU_RA_SIGNAL_PATH_RESET    0x68
#define MPU_RA_MOT_DETECT_CTRL      0x69
#define MPU_RA_USER_CTRL        0x6A
#define MPU_RA_PWR_MGMT_1       0x6B
#define MPU_RA_PWR_MGMT_2       0x6C
#define MPU_RA_BANK_SEL         0x6D
#define MPU_RA_MEM_START_ADDR   0x6E
#define MPU_RA_MEM_R_W          0x6F
#define MPU_RA_DMP_CFG_1        0x70
#define MPU_RA_DMP_CFG_2        0x71
#define MPU_RA_FIFO_COUNTH      0x72
#define MPU_RA_FIFO_COUNTL      0x73
#define MPU_RA_FIFO_R_W         0x74
#define MPU_RA_WHO_AM_I         0x75

#define MPU6050_SMPLRT_DIV      0       // 8000Hz

#define MPU6050_LPF_256HZ       0		// 0.98ms
#define MPU6050_LPF_188HZ       1		// 1.9ms
#define MPU6050_LPF_98HZ        2		// 2.8ms
#define MPU6050_LPF_42HZ        3		// 4.8ms
#define MPU6050_LPF_20HZ        4		// 8.3ms
#define MPU6050_LPF_10HZ        5		//13.4ms
#define MPU6050_LPF_5HZ         6		//18.6ms

#define MPU6050A_2mg                ((float)0.00006103f)  // 0.00006250 g/LSB
#define MPU6050A_4mg                ((float)0.00012207f)  // 0.00012500 g/LSB
#define MPU6050A_8mg                ((float)0.00024414f)  // 0.00025000 g/LSB

#define MPU6050G_s250dps            ((float)0.0076335f)  // 0.0087500 dps/LSB
#define MPU6050G_s500dps            ((float)0.0152671f)  // 0.0175000 dps/LSB
#define MPU6050G_s2000dps           ((float)0.0609756f)  // 0.0700000 dps/LSB

void delayms(uint16_t ms){
	uint16_t i = 20000;
	for(uint16_t j=0;j<ms;j++)
	{
		i = 20000;
		while(i--);
	}
}

int MPU60x0_ReadReg(int regAddr,void*buf,int rpt)
{
	int t=1;
	Delay((10));
	HwTwiRecieveData(MAKE_TWI_MODE(MPU60x0_Addr, I2C0),	regAddr,(char*)buf,rpt);
	return(t);
}

int MPU60x0_WriteReg(int regAddr,void*buf,int rpt)
{
	int t=1;
	Delay((10));
	HwTwiSendData(MAKE_TWI_MODE(MPU60x0_Addr, I2C0),regAddr,(char*)buf,rpt);
	return(t);
}

//MPU6050 initialization, para: sample rate, low pass filter 初始化，传入参数：采样率，低通滤波频率
void MPU6050_Init(uint16_t sample_rate, uint16_t lpf)
{
	uint8_t default_filter;

	default_filter = MPU6050_LPF_20HZ;
	
	delayms(500);
	

	uint8 t[4];
//	ICU_SetSysclk96M(2);
	//Device Reset
	//I2C_Single_Write(MPU6050_ADDRESS,MPU_RA_PWR_MGMT_1, 0x80);
	t[0]=0x80;
	MPU60x0_WriteReg(MPU_RA_PWR_MGMT_1,&t,1);
	delayms(500);

		t[0]=0x03;
	MPU60x0_WriteReg(MPU_RA_PWR_MGMT_1,&t,1);
	delayms(50);
	//Gyro Sample Rate, 0x00(1000Hz),  = Gyro output rate / (1+SMPLRT_DIV)    陀螺仪采样率，0x00(1000Hz)   采样率 = 陀螺仪的输出率 / (1 + SMPLRT_DIV)
	//I2C_Single_Write(MPU6050_ADDRESS,MPU_RA_SMPLRT_DIV, (1000/sample_rate - 1));
	t[0]=(1000/sample_rate - 1);
	MPU60x0_WriteReg(MPU_RA_SMPLRT_DIV,&t,1);
	delayms(50);
	//Setting device clock source, Gyro Z axis	设置设备时钟源，陀螺仪Z轴
	//I2C_Single_Write(MPU6050_ADDRESS, MPU_RA_PWR_MGMT_1, 0x03);

	//i2c旁路模式
	//I2C_Single_Write(MPU6050_ADDRESS, MPU_RA_INT_PIN_CFG, 0 << 7 | 0 << 6 | 0 << 5 | 0 << 4 | 0 << 3 | 0 << 2 | 1 << 1 | 0 << 0);
	// INT_PIN_CFG   -- INT_LEVEL_HIGH, INT_OPEN_DIS, LATCH_INT_DIS, INT_RD_CLEAR_DIS, FSYNC_INT_LEVEL_HIGH, FSYNC_INT_DIS, I2C_BYPASS_EN, CLOCK_DIS
	//Low pass filter, 0x03(42Hz)			低通滤波频率，0x03(42Hz)
	//I2C_Single_Write(MPU6050_ADDRESS,MPU_RA_CONFIG, default_filter);
	t[0]=default_filter;
	MPU60x0_WriteReg(MPU_RA_CONFIG,&t,1);
	delayms(50);
	 //Gyro self test and Measure Range, typical:0x18(No Self test, 2000deg/S)	陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
	//I2C_Single_Write(MPU6050_ADDRESS, MPU_RA_GYRO_CONFIG, 0x18);
	t[0]=0x18;
	MPU60x0_WriteReg(MPU_RA_GYRO_CONFIG,&t,1);
	delayms(50);
	//Accelerometer Self test and measure range(No Self test, +-8G)		加速计自检、测量范围(不自检，+-8G)
	//I2C_Single_Write(MPU6050_ADDRESS,MPU_RA_ACCEL_CONFIG, 2 << 3);
	t[0]=2 << 3;
	MPU60x0_WriteReg(MPU_RA_ACCEL_CONFIG,&t,1);
	delayms(50);
	t[0]=0x05;

	t[0]=0x01;
	MPU60x0_WriteReg(MPU_RA_INT_ENABLE,&t,1);
//	ICU_SetSysclk96M(1);
}


uint8 Gyro_CALIBRATED;

uint8 Sensor_temp[16];			////Backup Sensor Data

//IMU初始化
void IMU_Init(void)
{
	MPU6050_Init(500,256);		//初始化MPU6050，1Khz采样率
}

#endif
