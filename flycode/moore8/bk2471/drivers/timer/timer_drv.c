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
	uint32 tmrTO[3];//�֧��268.44s��ʱ
	uint32 tmrTOCnt[3];
	CCallback tmrCbk[3];
}CLogicalTimer;


static CLogicalTimer gLTmr;
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
*������:
*	Timer_EnInt
*����:
*	����ָ��timer�ж�
*����:
*	1.inte���Ƿ������ж�
*����:
*	��
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
void Timer_SetTO_32K(int tn,uint32 period,int inte){
	Timer_Init(tn,TIMER_SRCCLK_32K,period,inte);
}

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
void Timer_SetTO_16M(int tn,uint32 period,int inte){
	Timer_Init(tn,TIMER_SRCCLK_16M,period,inte);
}

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
// #define TIMER_UNIT			0
#define TIMER_UNIT			4/*timer��ʱ�䵥λΪus*/
uint32 Timer_Read(int tn){
	CLogicalTimer*pltmr=&gLTmr;
	uint32 ct=(pltmr->tmrHigh[tn]<<16);
	uint32 ht;
	uint32 rt;
	ct=BASE_TIMER_PTR->tmr[tn].cur_v;
	ht=pltmr->tmrHigh[tn];
	rt=BASE_TIMER_PTR->tmr[tn].cur_v;
	if(rt<ct){
		return((pltmr->tmrHigh[tn]<<(16-TIMER_UNIT))+(rt>>TIMER_UNIT));//usΪ��λ
	}else{
		return((ht<<(16-TIMER_UNIT))+(ct>>TIMER_UNIT));
	}
}
/*
*������:
*	timerX_isr
*����:
*	timerX���жϷ���
*����:
*	��
*����:
*	��
*/
void timerX_isr(int tn){
	CLogicalTimer*pltmr=&gLTmr;
	HW_TIMER*tmr=BASE_TIMER_PTR;
	pltmr->tmrHigh[tn]++;
	if(pltmr->tmrTOCnt[tn]==0){
		//����TO
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
*������:
*	timerX_isr
*����:
*	timerX���жϷ���
*����:
*	��
*����:
*	��
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
void Timer_SetCbk(int tn,CCallback cbk){
	gLTmr.tmrCbk[tn]=cbk;
}

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
uint32 Timer_GetTOCnt(int tn){
	return(gLTmr.tmrHigh[tn]);
}

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
void Timer_SetTOCnt(int tn,uint32 c){
	gLTmr.tmrHigh[tn]=c;
}

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
*������:
*	Timer_Delay
*����:
*	�ӳٱȽϾ�ȷ��ʱ�䣬����<10us
*����:
*	1.tn:��ʱ����(��Ӧ��timer periodҪ��ΪFREE_RUN)
*	2.dly:�ӳ�ʱ��(us)
*����:
*	��
*/
void Timer_Delay(int tn,uint32 dly){
	uint32 tnow=Timer_Read(tn);
	while(1){
		if((Timer_Read(tn)-tnow)>=dly)break;
	}
}

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
void Timer_Close(int tn){
	HW_TIMER*tmr=BASE_TIMER_PTR;
	tmr->cfg &= _BIT(2*(tn));
}
