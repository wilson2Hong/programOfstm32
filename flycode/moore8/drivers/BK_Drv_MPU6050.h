#ifndef __BK_DRV_MPU6050_H
#define	__BK_DRV_MPU6050_H

#include "board.h"


	//MPU6050 initialization, para: sample rate, low pass filter     MPU6050初始化，传入参数：采样率，低通滤波频率
void MPU6050_Init(uint16_t sample_rate, uint16_t lpf);
	//Read mpu6050 data	读取mpu6050数据，
void MPU6050_Read_Data_0(void);
void MPU6050_Read_Data_1(void*acc,void*gyro);
void MPU6050_Read_Data(void*acc,void*gyro);
#endif
