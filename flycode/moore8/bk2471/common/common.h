#ifndef _COMMON_H_
#define _COMMON_H_
#include <stdio.h>
#define _DEBUG_
#ifndef _DEBUG_
#define PRINT	\

#else
#define PRINT	\
	printf
#endif

#define FC_MAIN_CLK		(48000000)

#define MAKE_DLY_ms(n)	\
	((FC_MAIN_CLK/1000*(n)-3)/6)

#define MAKE_DLY_us(n)	\
	((FC_MAIN_CLK/1000000*(n)-3)/6)

#define MAKE_DLY_ins(n)	\
	(((n)-3)/6)

// #ifdef __cplusplus  
// extern "C" {  
// #endif  

void Delay_ms(unsigned int ms);
void Delay(int dly);

// #ifdef __cplusplus  
// }
// #endif  

/*
 *函数名:
 *	BigEndian2Little
 *功能:
 *	对数据进行大小端（16bits）转换
 *参数:
 *	1.buf，rpt：将要操作的数据缓冲指针和大小
 *返回:
 *	无
 *特殊:
 *	1.改变:
 *	2.stack:
*/
void BigEndian2Little(void*buf,int rpt);

// void _memcpy(void*dst,void*src,int rpt);
// void _memset(void*dst,int val,int rpt);

#endif
