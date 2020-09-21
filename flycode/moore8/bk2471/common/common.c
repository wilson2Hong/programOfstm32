#include "..\includes\types.h"
#include <string.h>
/*
 *������:
 *	Delay_ms
 *����:
 *	��msΪ��λ��ʱ
 *����:
 *	1.ms����ʱms��
 *����:
 *	��
 *����:
 *	1.�ı�:
 *	2.stack:
*/
void Delay_ms(unsigned int ms){
	volatile int i, j;

	for(i=0; i<ms; i++)
		for(j=0; j<1500; j++);

}

/*
 *������:
 *	Delay
 *����:
 *	��ʱ
 *����:
 *	1.dly����ʱ��
 *����:
 *	��
 *����:
 *	1.�ı�:
 *	2.stack:
*/
void Delay(int dly){
	while(dly--);
}

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

