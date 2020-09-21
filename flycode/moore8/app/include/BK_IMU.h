#ifndef __BK_IMU_H
#define __BK_IMU_H
#include "..\bk2471\includes\types.h"

extern uint8 Gyro_CALIBRATED;

extern int16 Acc_Offset[3];
extern int16 Gyro_Offset[3];

extern uint8 Sensor_temp[16];

//IMU初始化
void IMU_Init(void);

//更新传感器数据
void IMU_updateSensor(void);
void IMU_ReadSensor_0(void);

//陀螺仪零偏矫正
void IMU_CalOffset_Gyro(void);

#endif

