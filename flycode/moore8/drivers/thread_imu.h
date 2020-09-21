#ifndef _THREAD_IMU_H_
#define _THREAD_IMU_H_

void IMU_StartReadData(void);
void IMU_RequestStopping(void);//请求停止imu线程
void IMU_WaitStoppedStatus(void);//等待imu线程停止
extern char gyro_dataRdy;
extern char fbm320_tempRdy;
extern char fbm320_pressRdy;

#endif
