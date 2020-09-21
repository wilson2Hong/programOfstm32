
#ifndef __BK_data_init_h_
#define __BK_data_init_h_

extern long time3,time4,time5,time6,time7;

extern float Kcinvy;

#define DATA_LEN	32
//数据结构定义
struct t_axis{
	int gyro_raw[DATA_LEN];		//gyro原始数据
	float gyro_fir[1];			//gyro滤波器输出
	
	float gyro_bias;			//gyro偏移值
	float angle_i;				//重力校正误差积分

	float acc_err;
	
	int accel_raw[DATA_LEN];	//accel原始数据
	float accel_fir[2];			//accel滤波器输出
	float lpf_acc[4];
	float accel_bias;
	
	float omiga;				
	float deta_angle;			//四元数更新用的角度增量
	float crb_angle;			//四元数更新用的角度误差补偿

	float remote;				//遥控数据

	float control[1];			//控制滤波器输出
	float lpf[7];
	float out;				//控制器输出
	float out_i;
	
	float angleErr;				//角度控制误差
	float angleErr_i;			//角度控制误差积分
	float anglerateErr;			//角速度控制误差
	
	short g_axis;
};
typedef struct t_axis  t_AXIS;

extern t_AXIS pit, rol, yaw;

struct t_high{
	float s[6];		//位移
	float v[2];		//速度
	float a[2];		//加速度
	float bias;
	float err;
	float err_v;
	float sd;
};
typedef struct t_high  t_HIGH;

extern t_HIGH pos_a;
extern float Gz;

void shift_data(void);
void data_update(void);
void data_init(void);
void pos_init(void);

#endif
