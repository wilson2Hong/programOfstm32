#ifndef _IWDG_H
#define _IWDG_H
#include "sys.h"

////////////////////////////////////////////////////////////////////////////////// 	
#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
void IWDG_Init(u8 prer,u16 rlr);//IWDG��ʼ��
void IWDG_Feed(void);  //ι������
	 

#ifdef __cplusplus
}
#endif //__cplusplus

#endif
