
#include "BK_data_init.h"
#include "BK_RC.h"
#include "BK_adc.h"
#include "debug.h"


#include "..\drivers\BK_Drv_Nrf24l01.h"
#include "..\drivers\thread_imu.h"
#include "..\bk2471\drivers\timer\timer.h"

void Control(void);


int 	pit_offset 		= 0;		//	����ƫ��ֵ
int 	rol_offset  	= 0;		//	����ƫ��ֵ
int		THROTTLE_display;			//	�������ֵ
float	THROTTLE_1G  	= 2000;		//	��ͣʱPWM���ֵ
float 	i_angle,fangun_angle;		//	�����Ƕȱ����ͽǶȻ��ֱ���


t_AXIS pit, rol, yaw;	//����������ݶ���
int reset_flag=1;
int NoMove_f=1;


void app_imu_task(void)
{
	if(gyro_dataRdy==0)		return;	

	gyro_dataRdy=0;
	
	Control();	
	debug_send();				//���ߵ����������	
	Pilot_Light();				//LEDָʾ�ƿ���	
	Failsafe_Check();			//RFʧ�����
}


void app_rx_task(void)
{
	if(bk2401_dataRdy==0)return;
	bk2401_dataRdy=0;

	Cal_Command();				//ң�����ݴ���
	check_sticks();				//ҡ��λ�ü��
}



int FAST_CALL entry0_main(void)
{
	BK2471_Init();				//��ʼ��MCUӲ������
	IMU_Init();					//��ʼ��IMUоƬ�Ĵ��������Բ�����Ԫ��


//	Gyro_CALIBRATED=1;			//ʹ������������У��
	
	IMU_StartReadData();		//����I2C���ݶ�ȡ����
	
//	Gyro_CALIBRATED = 0;
	pit.gyro_bias = 0;
	rol.gyro_bias = 0;
	yaw.gyro_bias = 0;
	
	
	////////////////////////  �մ��볤����Ӧ������¼��,��Ȼ����չ� //////////////////////////
	pit.gyro_raw[0] = 1;
	pit.gyro_raw[1] = 1;
	pit.gyro_raw[2] = 1;
	pit.gyro_raw[3] = 1;
	pit.gyro_raw[4] = 1;
	pit.gyro_raw[5] = 1;
	pit.gyro_raw[6] = 1;
	pit.gyro_raw[7] = 1;
	pit.gyro_raw[8] = 1;
	pit.gyro_raw[9] = 1;
	pit.gyro_raw[10] = 1;
	pit.gyro_raw[11] = 1;
	pit.gyro_raw[12] = 1;
	pit.gyro_raw[13] = 1;
	pit.gyro_raw[14] = 1;
	pit.gyro_raw[15] = 1;
	pit.gyro_raw[16] = 1;
	pit.gyro_raw[17] = 1;
	pit.gyro_raw[18] = 1;
	pit.gyro_raw[19] = 1;
	
	////////////////////////  �մ��볤�� //////////////////////////

	while(1)
	{
		app_imu_task();
		app_rx_task();
	}
}

int FAST_ENTRY0 main(void)
{
	__asm volatile
	{
		bl entry0_main
	};
	return 0;
}
