#include "..\includes\types.h"
#include <string.h>
/*
 *函数名:
 *	Delay_ms
 *功能:
 *	按ms为单位延时
 *参数:
 *	1.ms：延时ms数
 *返回:
 *	无
 *特殊:
 *	1.改变:
 *	2.stack:
*/
void Delay_ms(unsigned int ms){
	volatile int i, j;

	for(i=0; i<ms; i++)
		for(j=0; j<1500; j++);

}

/*
 *函数名:
 *	Delay
 *功能:
 *	延时
 *参数:
 *	1.dly：延时数
 *返回:
 *	无
 *特殊:
 *	1.改变:
 *	2.stack:
*/
void Delay(int dly){
	while(dly--);
}

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
void BigEndian2Little(void*buf,int rpt){
	UI16 *ptr=(UI16*)buf;
	UI32 tmp;
	while(rpt>0){
		tmp=(*ptr);
		//tmp=__rev16(tmp);
		tmp=B2L_16(tmp);
		*ptr++=tmp;
		rpt--;
	}
}

