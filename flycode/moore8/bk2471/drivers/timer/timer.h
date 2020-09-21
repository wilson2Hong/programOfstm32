#ifndef _TIMER_H_
#define _TIMER_H_
#include "..\..\includes\types.h"
#include "..\icu\icu.h"
#define	BASE_TIMER_PTR	\
		((HW_TIMER*)0x00f00a00)
// 16bit Timer
#define REG_APB_TIMER_CTRL     (*( (volatile unsigned long *)   (APB_TIMER_BASE + (0x0*4)) ))

#define bit_PT0_MODE		BIT_0
#define bit_PT0_INT_ENABLE	BIT_1
#define bit_PT1_MODE		BIT_2
#define bit_PT1_INT_ENABLE	BIT_3
#define bit_PT2_MODE		BIT_4
#define bit_PT2_INT_ENABLE	BIT_5


#define REG_APB_TIMER_INTR     (*( (volatile unsigned long *)   (APB_TIMER_BASE + (0x1*4)) ))

#define bit_PT0_INT_FLAG	BIT_0
#define bit_PT1_INT_FLAG	BIT_1
#define bit_PT2_INT_FLAG	BIT_2


#define REG_APB_TIMER0_TIMETO  (*( (volatile unsigned long *)   (APB_TIMER_BASE + (0x2*4)) ))
#define REG_APB_TIMER0_RDBACK  (*( (volatile unsigned long *)   (APB_TIMER_BASE + (0x3*4)) ))
#define REG_APB_TIMER1_TIMETO  (*( (volatile unsigned long *)   (APB_TIMER_BASE + (0x4*4)) ))
#define REG_APB_TIMER1_RDBACK  (*( (volatile unsigned long *)   (APB_TIMER_BASE + (0x5*4)) ))
#define REG_APB_TIMER2_TIMETO  (*( (volatile unsigned long *)   (APB_TIMER_BASE + (0x6*4)) ))
#define REG_APB_TIMER2_RDBACK  (*( (volatile unsigned long *)   (APB_TIMER_BASE + (0x7*4)) ))
//=====================================================================================

typedef struct HW_TIMER{
	union{
		uint32 cfg;
		struct{
			uint32 t0_cnt_en:1;
			//Timer0 counter enable;0-Disable;1-Enable
			uint32 t0_int_en:1;
			//Timer0 interrupt enable;0-Disable;1-Enable
			uint32 t1_cnt_en:1;
			//Timer1 counter enable;0-Disable;1-Enable
			uint32 t1_int_en:1;
			//Timer1 interrupt enable;0-Disable;1-Enable
			uint32 :28;
		};
	};
	union{
		uint32 intf;
		struct{
			uint32 timer0_int:1;
			//Timer0 Interrupt Status. ;Write 1 to clear.
			uint32 timer1_int:1;
			//Timer1 Interrupt Status. ;Write 1 to clear.
			uint32 :30;
		};
	};
	struct  
	{
		union{
			uint32 endv;
			struct{
				uint32 timeto:16;
				//Timer0 counter time-to-value
				uint32 :16;
			};
		};
		union{
			uint32 cur_v;
			struct{
				uint32 rdback:16;
				//Timer0 counter current value. Read-Only.
				uint32 :16;
			};
		};
	}tmr[2];
}HW_TIMER;
#define TIMER0		0
#define TIMER1		1
#define TIMER2		2
#define TIMER_SRCCLK_32K		0
#define TIMER_SRCCLK_16M		1
#define FREQ_TIMER_SRCCLK_32K	32000
#define FREQ_TIMER_SRCCLK_16M	16000000

#define TIMER_OPEN_CLOCK(pn,srcsel) \
	{\
	/*pn:timer���,0-1 srcsel:pwmʱ��Դѡ�� */\
	BASE_ICU_PTR->pwm[4].pwm_clk &= _BFD(3,8,2);\
	BASE_ICU_PTR->pwm[4].pwm_clk |= BFD(srcsel,9,1);\
	}

#define TIMER_Setup(pn,period) \
	{\
	BASE_TIMER_PTR->tmr[pn].endv=(period);\
	}

#define TIMER_SetupInt(pn,inte) \
	{\
	/*pn:timer���,0-1 inte:1=�ж����� */\
	if(inte)BASE_TIMER_PTR->cfg |= BIT(1+2*(pn));\
	else BASE_TIMER_PTR->cfg &= _BIT(1+2*(pn));\
	}

#define TIMER_ClearIF(pn) \
	{\
		/*pn:timer���,0-1 inte:1=�ж����� */\
		if((pn) == TIMER0)BASE_TIMER_PTR->timer0_int = 1;\
		if((pn) == TIMER1)BASE_TIMER_PTR->timer1_int = 1;\
	}

#define TIMER_Open(pn) \
	{\
	/*pn:timer���,0-1*/\
	BASE_TIMER_PTR->cfg |= BIT(2*(pn));\
	}

#define TIMER_CLOSE_CLOCK(pn) \
	{\
	BASE_ICU_PTR->pwm[4].pwm_clk |= (BIT(8));\
	}

#define TIMER_CLOSE(pn) \
	{\
	/*pn:timer���,0-1*/\
	BASE_TIMER_PTR->cfg &= _BIT(2*(pn));\
	TIMER_CLOSE_CLOCK(pn);\
	}

#define TIMER_READ(pn) \
	/*pn:timer���,0-1*/\
	(BASE_TIMER_PTR->tmr[pn].cur_v & 0xffff)

#define TIMER_SRC16M_1us		16
#define TIMER_SRC16M_1ms		TIMER_SRC16M_1us*1000
#define TIMER_SRC16M_Nms(n)		((n)*TIMER_SRC16M_1ms)
#define TIMER_SRC16M_Nus(n)		((n)*TIMER_SRC16M_1us)

#define TIMER_SRC32K_1ms		32
#define TIMER_SRC32K_Nms(n)		((n)*TIMER_SRC32K_1ms)
#define TIMER_FREE_RUN			0xffff
#define TIMER0_1us			TIMER_SRC16M_1us
#define TIMER0_1ms			TIMER_SRC16M_1ms
#define TIMER0_Nms(n)		((n)*TIMER0_1ms)
#define TIMER0_Nus(n)		((n)*TIMER0_1us)

// #ifdef __cplusplus  
// extern "C" {  
// #endif  

/*
*������:
*	Timer_IE
*����:
*	ʹ��timerϵͳ�ж�
*����:
*	1.inte���Ƿ�����timer�ж�
*����:
*	��
*/
void Timer_IE(int inte);

/*
*������:
*	Timer_EnInt
*����:
*	����ָ��timer�ж�
*����:
*	1.inte���Ƿ������ж�
*����:
*	��
*/
void Timer_EnInt(int tn,int inte);

/*
*������:
*	Timer_Init
*����:
*	��ʱ����ʼ��
*����:
*	1.tn:��ʱ����
*	2.srcclk:ѡ��timerʱ��Դ��TIMER_SRCCLK_32K����TIMER_SRCCLK_16M
*	3.period:��ʱ����
*	4.inte���Ƿ���ж�
*����:
*	��
*ע��:
*	1��timer�����ж���Ҫ�����
*/
void Timer_Init(int tn,int srcclk,uint32 period,int inte);

/*
*������:
*	Timer_SetTO_32K
*����:
*	��ʼ����ʱ����ʱ��ԴΪ32KHz
*����:
*	1.tn:��ʱ����
*	2.period:��ʱ����,ʹ��TIMER_SRC32K_Nms(x)��ָ����ʱ����
*	3.inte���Ƿ���ж�
*����:
*	��
*/
void Timer_SetTO_32K(int tn,uint32 period,int inte);

/*
*������:
*	Timer_SetTO_16M
*����:
*	��ʼ����ʱ����ʱ��ԴΪ16MHz
*����:
*	1.tn:��ʱ����
*	2.period:��ʱ����,ʹ��TIMER_SRC16M_Nms(x)��TIMER_SRC16M_Nus(x)��ָ����ʱ����
*	3.inte���Ƿ���ж�
*����:
*	��
*/
void Timer_SetTO_16M(int tn,uint32 period,int inte);

/*
*������:
*	Timer_Read
*����:
*	��ȡָ��timer�ļ���ֵ
*����:
*	1.tn:��ʱ����
*����:
*	32bits��timer����ֵ(�������չ)
*/
uint32 Timer_Read(int tn);

/*
*������:
*	Timer_SetCbk
*����:
*	�趨ָ��timer���ʱ��callack
*����:
*	1.tn:��ʱ����
*	2.cbk:�ص�����
*����:
*	
*/
void Timer_SetCbk(int tn,CCallback cbk);

/*
*������:
*	Timer_GetTOCnt
*����:
*	��ȡָ��timer�������
*����:
*	1.tn:��ʱ����
*����:
*	ָ��timer�������
*/
uint32 Timer_GetTOCnt(int tn);

/*
*������:
*	Timer_SetTOCnt
*����:
*	�趨ָ��timer�������
*����:
*	1.tn:��ʱ����
*	2.c:�������
*����:
*	��
*/
void Timer_SetTOCnt(int tn,uint32 c);

/*
*������:
*	Timer_WaitTO
*����:
*	�ȴ�ָ����ʱ�����,���ر�
*����:
*	1.tn:��ʱ����
*	2.cbk:�ȴ�ʱִ�е�����
*	3.toCbk:TO��ִ�е�����
*����:
*	��
*/
void Timer_WaitTO(int tn,TCallback cbk,TCallback toCbk);

/*
*������:
*	Timer_Delay
*����:
*	�ӳٱȽϾ�ȷ��ʱ�䣬����<10us
*����:
*	1.tn:��ʱ����
*	2.dly:�ӳ�ʱ��
*����:
*	��
*/
void Timer_Delay(int tn,uint32 dly);

/*
*������:
*	Timer_Close
*����:
*	�ر�ָ��timer
*����:
*	1.tn:��ʱ����
*����:
*	
*/
void Timer_Close(int tn);

// #ifdef __cplusplus  
// }
// #endif  

#endif
