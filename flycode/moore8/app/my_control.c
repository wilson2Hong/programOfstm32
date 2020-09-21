
#include "BK_RC.h"
#include "BK_Motor.h"
#include "BK_data_init.h"

#include <math.h>

#define DT 0.002f	//����ʱ��
void Control(void)
{
	//����ң�����ý��ٶȵ�Ŀ��ֵ
	int dist_rol = 0;
	int dist_pit = 0;
	int dist_yaw = 0;
	
	if(rol.remote>30)	dist_rol =  200;
	if(rol.remote<-30)	dist_rol = -200;
	
	if(pit.remote>30)	dist_pit =  200;
	if(pit.remote<-30)	dist_pit = -200;
	
	if(yaw.remote>30)	dist_yaw =  500;
	if(yaw.remote<-30)	dist_yaw = -500;
	
	
	
		

// 	//ʹ�����Ӳ�������п���
// 	rol.out = rol.gyro_raw[0] + (rol.gyro_raw[0] - rol.gyro_raw[5])*3;
// 	pit.out = pit.gyro_raw[0] + (pit.gyro_raw[0] - pit.gyro_raw[5])*3;
// 	yaw.out = yaw.gyro_raw[0] + (yaw.gyro_raw[0] - yaw.gyro_raw[5])*3;

// 	//�������
// 	writeMotor(remote_THROTTLE, dist_pit - pit.out  , dist_rol - rol.out, dist_yaw + yaw.out);		//ע��,yaw�Ҹ㷴��

	//һ�д���㶨�ɿؾ�����������
	writeMotor(remote_THROTTLE, dist_pit - (pit.gyro_raw[0]*4 - pit.gyro_raw[5]*3)  , dist_rol - (rol.gyro_raw[0]*4 - rol.gyro_raw[5]*3), dist_yaw + yaw.gyro_raw[0]*4 - yaw.gyro_raw[5]*3);	

	//���������
	rol.gyro_raw[5] = rol.gyro_raw[4];
	rol.gyro_raw[4] = rol.gyro_raw[3];
	rol.gyro_raw[3] = rol.gyro_raw[2];
	rol.gyro_raw[2] = rol.gyro_raw[1];
	rol.gyro_raw[1] = rol.gyro_raw[0];
	
	pit.gyro_raw[5] = pit.gyro_raw[4];
	pit.gyro_raw[4] = pit.gyro_raw[3];
	pit.gyro_raw[3] = pit.gyro_raw[2];
	pit.gyro_raw[2] = pit.gyro_raw[1];
	pit.gyro_raw[1] = pit.gyro_raw[0];
	
	yaw.gyro_raw[5] = yaw.gyro_raw[4];
	yaw.gyro_raw[4] = yaw.gyro_raw[3];
	yaw.gyro_raw[3] = yaw.gyro_raw[2];
	yaw.gyro_raw[2] = yaw.gyro_raw[1];
	yaw.gyro_raw[1] = yaw.gyro_raw[0];
}
