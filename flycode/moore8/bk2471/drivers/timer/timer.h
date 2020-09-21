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
	/*pn:timer编号,0-1 srcsel:pwm时钟源选择 */\
	BASE_ICU_PTR->pwm[4].pwm_clk &= _BFD(3,8,2);\
	BASE_ICU_PTR->pwm[4].pwm_clk |= BFD(srcsel,9,1);\
	}

#define TIMER_Setup(pn,period) \
	{\
	BASE_TIMER_PTR->tmr[pn].endv=(period);\
	}

#define TIMER_SetupInt(pn,inte) \
	{\
	/*pn:timer编号,0-1 inte:1=中断允许 */\
	if(inte)BASE_TIMER_PTR->cfg |= BIT(1+2*(pn));\
	else BASE_TIMER_PTR->cfg &= _BIT(1+2*(pn));\
	}

#define TIMER_ClearIF(pn) \
	{\
		/*pn:timer编号,0-1 inte:1=中断允许 */\
		if((pn) == TIMER0)BASE_TIMER_PTR->timer0_int = 1;\
		if((pn) == TIMER1)BASE_TIMER_PTR->timer1_int = 1;\
	}

#define TIMER_Open(pn) \
	{\
	/*pn:timer编号,0-1*/\
	BASE_TIMER_PTR->cfg |= BIT(2*(pn));\
	}

#define TIMER_CLOSE_CLOCK(pn) \
	{\
	BASE_ICU_PTR->pwm[4].pwm_clk |= (BIT(8));\
	}

#define TIMER_CLOSE(pn) \
	{\
	/*pn:timer编号,0-1*/\
	BASE_TIMER_PTR->cfg &= _BIT(2*(pn));\
	TIMER_CLOSE_CLOCK(pn);\
	}

#define TIMER_READ(pn) \
	/*pn:timer编号,0-1*/\
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
*函数名:
*	Timer_IE
*功能:
*	使能timer系统中断
*参数:
*	1.inte：是否允许timer中断
*返回:
*	无
*/
void Timer_IE(int inte);

/*
*函数名:
*	Timer_EnInt
*功能:
*	允许指定timer中断
*参数:
*	1.inte：是否允许中断
*返回:
*	无
*/
void Timer_EnInt(int tn,int inte);

/*
*函数名:
*	Timer_Init
*功能:
*	定时器初始化
*参数:
*	1.tn:定时器名
*	2.srcclk:选择timer时钟源：TIMER_SRCCLK_32K或者TIMER_SRCCLK_16M
*	3.period:定时长度
*	4.inte：是否打开中断
*返回:
*	无
*注意:
*	1、timer的总中断需要另外打开
*/
void Timer_Init(int tn,int srcclk,uint32 period,int inte);

/*
*函数名:
*	Timer_SetTO_32K
*功能:
*	初始化定时器的时钟源为32KHz
*参数:
*	1.tn:定时器名
*	2.period:定时长度,使用TIMER_SRC32K_Nms(x)来指定定时长度
*	3.inte：是否打开中断
*返回:
*	无
*/
void Timer_SetTO_32K(int tn,uint32 period,int inte);

/*
*函数名:
*	Timer_SetTO_16M
*功能:
*	初始化定时器的时钟源为16MHz
*参数:
*	1.tn:定时器名
*	2.period:定时长度,使用TIMER_SRC16M_Nms(x)或TIMER_SRC16M_Nus(x)来指定定时长度
*	3.inte：是否打开中断
*返回:
*	无
*/
void Timer_SetTO_16M(int tn,uint32 period,int inte);

/*
*函数名:
*	Timer_Read
*功能:
*	读取指定timer的计数值
*参数:
*	1.tn:定时器名
*返回:
*	32bits的timer计数值(经软件扩展)
*/
uint32 Timer_Read(int tn);

/*
*函数名:
*	Timer_SetCbk
*功能:
*	设定指定timer溢出时的callack
*参数:
*	1.tn:定时器名
*	2.cbk:回调函数
*返回:
*	
*/
void Timer_SetCbk(int tn,CCallback cbk);

/*
*函数名:
*	Timer_GetTOCnt
*功能:
*	获取指定timer溢出次数
*参数:
*	1.tn:定时器名
*返回:
*	指定timer溢出次数
*/
uint32 Timer_GetTOCnt(int tn);

/*
*函数名:
*	Timer_SetTOCnt
*功能:
*	设定指定timer溢出次数
*参数:
*	1.tn:定时器名
*	2.c:溢出次数
*返回:
*	无
*/
void Timer_SetTOCnt(int tn,uint32 c);

/*
*函数名:
*	Timer_WaitTO
*功能:
*	等待指定计时器溢出,并关闭
*参数:
*	1.tn:定时器名
*	2.cbk:等待时执行的任务
*	3.toCbk:TO后执行的任务
*返回:
*	无
*/
void Timer_WaitTO(int tn,TCallback cbk,TCallback toCbk);

/*
*函数名:
*	Timer_Delay
*功能:
*	延迟比较精确的时间，精度<10us
*参数:
*	1.tn:定时器名
*	2.dly:延迟时间
*返回:
*	无
*/
void Timer_Delay(int tn,uint32 dly);

/*
*函数名:
*	Timer_Close
*功能:
*	关闭指定timer
*参数:
*	1.tn:定时器名
*返回:
*	
*/
void Timer_Close(int tn);

// #ifdef __cplusplus  
// }
// #endif  

#endif
