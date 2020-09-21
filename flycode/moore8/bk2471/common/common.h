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
 *������:
 *	BigEndian2Little
 *����:
 *	�����ݽ��д�С�ˣ�16bits��ת��
 *����:
 *	1.buf��rpt����Ҫ���������ݻ���ָ��ʹ�С
 *����:
 *	��
 *����:
 *	1.�ı�:
 *	2.stack:
*/
void BigEndian2Little(void*buf,int rpt);

// void _memcpy(void*dst,void*src,int rpt);
// void _memset(void*dst,int val,int rpt);

#endif
