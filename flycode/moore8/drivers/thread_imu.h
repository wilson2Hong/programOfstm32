#ifndef _THREAD_IMU_H_
#define _THREAD_IMU_H_

void IMU_StartReadData(void);
void IMU_RequestStopping(void);//����ֹͣimu�߳�
void IMU_WaitStoppedStatus(void);//�ȴ�imu�߳�ֹͣ
extern char gyro_dataRdy;
extern char fbm320_tempRdy;
extern char fbm320_pressRdy;

#endif
