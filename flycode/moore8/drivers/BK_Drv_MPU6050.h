#ifndef __BK_DRV_MPU6050_H
#define	__BK_DRV_MPU6050_H

#include "board.h"


	//MPU6050 initialization, para: sample rate, low pass filter     MPU6050��ʼ������������������ʣ���ͨ�˲�Ƶ��
void MPU6050_Init(uint16_t sample_rate, uint16_t lpf);
	//Read mpu6050 data	��ȡmpu6050���ݣ�
void MPU6050_Read_Data_0(void);
void MPU6050_Read_Data_1(void*acc,void*gyro);
void MPU6050_Read_Data(void*acc,void*gyro);
#endif
