#include <stdio.h>

#include "..\icu\icu.h"
#include "..\timer\timer.h"
#include "..\gpio\gpio.h"
#define PRINT \

	//printf

#define PRN_NAME_VAL(name,fmt)	\
	""#name##"="##fmt##"\r\n",name
typedef struct CLogicalTimer{
	uint32 tmrHigh[3];
	uint32 tmrTO[3];//最长支持268.44s定时
	uint32 tmrTOCnt[3];
	CCallback tmrCbk[3];
}CLogicalTimer;


static CLogicalTimer gLTmr;
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
void Timer_IE(int inte){
//	HW_TIMER*tmr=BASE_TIMER_PTR;
	HW_ICU *icu=BASE_ICU_PTR;
	if(inte){
		icu->timer_int_en = 1;
		icu->timer_wakeup_en = 1;
	}else {
		icu->timer_int_en = 0;
		icu->timer_wakeup_en = 0;
	}
}

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
void Timer_EnInt(int tn,int inte){
	HW_TIMER*tmr=BASE_TIMER_PTR;
	if(inte){
		tmr->cfg |= BIT(1+2*(tn));
	}else {
		tmr->cfg &= _BIT(1+2*(tn));
	}
}

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
void Timer_Init(int tn,int srcclk,uint32 period,int inte){
	HW_TIMER*tmr=BASE_TIMER_PTR;
	HW_ICU *icu=BASE_ICU_PTR;
	CLogicalTimer *pltmr=&gLTmr;
	icu->pwm[4].pwm_clk &= _BFD(3,8,2);
	icu->pwm[4].pwm_clk |= BFD(srcclk,9,1);
	pltmr->tmrTOCnt[tn]=0;
	pltmr->tmrTO[tn]=period;
	//gTmrTO[tn]=0;
	if(period>=0x10000){
		tmr->tmr[tn].endv = TIMER_FREE_RUN;
		pltmr->tmrTOCnt[tn]=period-0x10000;
	}else{
		tmr->tmr[tn].endv = period;
	}
	
	Timer_EnInt(tn,inte);
	pltmr->tmrCbk[tn]=0;
	pltmr->tmrHigh[tn]=0;
	tmr->cfg |= BIT(2*(tn));
}

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
void Timer_SetTO_32K(int tn,uint32 period,int inte){
	Timer_Init(tn,TIMER_SRCCLK_32K,period,inte);
}

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
void Timer_SetTO_16M(int tn,uint32 period,int inte){
	Timer_Init(tn,TIMER_SRCCLK_16M,period,inte);
}

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
// #define TIMER_UNIT			0
#define TIMER_UNIT			4/*timer的时间单位为us*/
uint32 Timer_Read(int tn){
	CLogicalTimer*pltmr=&gLTmr;
	uint32 ct=(pltmr->tmrHigh[tn]<<16);
	uint32 ht;
	uint32 rt;
	ct=BASE_TIMER_PTR->tmr[tn].cur_v;
	ht=pltmr->tmrHigh[tn];
	rt=BASE_TIMER_PTR->tmr[tn].cur_v;
	if(rt<ct){
		return((pltmr->tmrHigh[tn]<<(16-TIMER_UNIT))+(rt>>TIMER_UNIT));//us为单位
	}else{
		return((ht<<(16-TIMER_UNIT))+(ct>>TIMER_UNIT));
	}
}
/*
*函数名:
*	timerX_isr
*功能:
*	timerX的中断服务
*参数:
*	无
*返回:
*	无
*/
void timerX_isr(int tn){
	CLogicalTimer*pltmr=&gLTmr;
	HW_TIMER*tmr=BASE_TIMER_PTR;
	pltmr->tmrHigh[tn]++;
	if(pltmr->tmrTOCnt[tn]==0){
		//重载TO
		if(pltmr->tmrTO[tn]>=0x10000){
			tmr->tmr[tn].endv = TIMER_FREE_RUN;
			pltmr->tmrTOCnt[tn]=pltmr->tmrTO[tn]-0x10000;
		}else{
			tmr->tmr[tn].endv = pltmr->tmrTO[tn];
			pltmr->tmrTOCnt[tn]=0;
		}
		
		if(pltmr->tmrCbk[tn]){
			pltmr->tmrCbk[tn]();
		}
	}else{
		if(pltmr->tmrTOCnt[tn]>0x10000){
			pltmr->tmrTOCnt[tn]-=0x10000;
		}else{
			tmr->tmr[tn].endv=pltmr->tmrTOCnt[tn];
			pltmr->tmrTOCnt[tn]=0;
		}
	}
}
/*
*函数名:
*	timerX_isr
*功能:
*	timerX的中断服务
*参数:
*	无
*返回:
*	无
*/
void timer0_isr(){
	timerX_isr(TIMER0);
}

void timer1_isr(){
	timerX_isr(TIMER1);
}

void timer2_isr(){
	timerX_isr(TIMER2);
}

void timer_isr(){
	HW_TIMER*tmr=BASE_TIMER_PTR;
	uint32 f=tmr->intf;
	if(f&BIT(TIMER0)){
		timer0_isr();
	}
	if(f&BIT(TIMER1)){
		timer1_isr();
	}
	if(f&BIT(TIMER2)){
		timer2_isr();
	}
	tmr->intf=f;
}

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
void Timer_SetCbk(int tn,CCallback cbk){
	gLTmr.tmrCbk[tn]=cbk;
}

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
uint32 Timer_GetTOCnt(int tn){
	return(gLTmr.tmrHigh[tn]);
}

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
void Timer_SetTOCnt(int tn,uint32 c){
	gLTmr.tmrHigh[tn]=c;
}

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
void Timer_WaitTO(int tn,TCallback cbk,TCallback toCbk){
	HW_TIMER*tmr=BASE_TIMER_PTR;
	while((tmr->intf&BIT(tn))==0){
		if(cbk)	cbk();
	}
	tmr->intf |= BIT(tn);
	Timer_Close(tn);
	if(toCbk)toCbk();
}

/*
*函数名:
*	Timer_Delay
*功能:
*	延迟比较精确的时间，精度<10us
*参数:
*	1.tn:定时器名(对应的timer period要设为FREE_RUN)
*	2.dly:延迟时间(us)
*返回:
*	无
*/
void Timer_Delay(int tn,uint32 dly){
	uint32 tnow=Timer_Read(tn);
	while(1){
		if((Timer_Read(tn)-tnow)>=dly)break;
	}
}

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
void Timer_Close(int tn){
	HW_TIMER*tmr=BASE_TIMER_PTR;
	tmr->cfg &= _BIT(2*(tn));
}
