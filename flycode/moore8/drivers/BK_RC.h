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

//参数初始化
void RC_Init(void);
//遥控通道数据处理
void Cal_Command(void);
//摇杆位置检测
void check_sticks(void);
//数据解包
void Data_Receive_Anl(u8 *data_buf,u8 num);
//失控保护检查
void Failsafe_Check(void);

#endif
