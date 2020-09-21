
#ifndef __BK_data_init_h_
#define __BK_data_init_h_

extern long time3,time4,time5,time6,time7;

extern float Kcinvy;

#define DATA_LEN	32
//���ݽṹ����
struct t_axis{
	int gyro_raw[DATA_LEN];		//gyroԭʼ����
	float gyro_fir[1];			//gyro�˲������
	
	float gyro_bias;			//gyroƫ��ֵ
	float angle_i;				//����У��������

	float acc_err;
	
	int accel_raw[DATA_LEN];	//accelԭʼ����
	float accel_fir[2];			//accel�˲������
	float lpf_acc[4];
	float accel_bias;
	
	float omiga;				
	float deta_angle;			//��Ԫ�������õĽǶ�����
	float crb_angle;			//��Ԫ�������õĽǶ�����

	float remote;				//ң������

	float control[1];			//�����˲������
	float lpf[7];
	float out;				//���������
	float out_i;
	
	float angleErr;				//�Ƕȿ������
	float angleErr_i;			//�Ƕȿ���������
	float anglerateErr;			//���ٶȿ������
	
	short g_axis;
};
typedef struct t_axis  t_AXIS;

extern t_AXIS pit, rol, yaw;

struct t_high{
	float s[6];		//λ��
	float v[2];		//�ٶ�
	float a[2];		//���ٶ�
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
