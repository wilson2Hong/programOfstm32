#ifndef __BK_RC_H
#define __BK_RC_H

#include "BK_Config.h"

#define RC_MID  		128                     
#define RC_MINCHECK		70                      
#define RC_MAXCHECK  	180

extern uint8 rawData[16];
extern float remote_THROTTLE;
extern uint8 key_L[6];
extern uint8 key_R[6];

//������ʼ��
void RC_Init(void);
//ң��ͨ�����ݴ���
void Cal_Command(void);
//ҡ��λ�ü��
void check_sticks(void);
//���ݽ��
void Data_Receive_Anl(u8 *data_buf,u8 num);
//ʧ�ر������
void Failsafe_Check(void);

#endif
