#ifndef _IWDG_H
#define _IWDG_H
#include "sys.h"

////////////////////////////////////////////////////////////////////////////////// 	
#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
void IWDG_Init(u8 prer,u16 rlr);//IWDG³õÊ¼»¯
void IWDG_Feed(void);  //Î¹¹·º¯Êý
	 

#ifdef __cplusplus
}
#endif //__cplusplus

#endif
