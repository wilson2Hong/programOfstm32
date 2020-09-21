#ifndef _GPIO_H_
#define _GPIO_H_
#include "..\..\includes\types.h"
#define	BASE_GPIO_PTR	\
		((HW_GPIO*)0x00f00500)

#define NUM_GPIO_PORT	\
		5

#define	ADDR_GPIO_PTR	\
	0x00f00500
//=====================================================================================
// GPIO
//=====================================================================================
#define BK2471_GPIO_CONFIG(gpio)		(*((volatile unsigned long *)	(APB_GPIO_BASE+8*(gpio)) ))
#define BK2471_GPIO_DATA(gpio)			(*((volatile unsigned long *)	(APB_GPIO_BASE+8*(gpio)+4) ))

#define REG_APB5_GPIOA_CFG              (*((volatile unsigned long *)   (APB_GPIO_BASE + 0x00) ))
#define REG_APB5_GPIOA_DATA             (*((volatile unsigned long *)   (APB_GPIO_BASE + 0x04) ))
#define REG_APB5_GPIOB_CFG              (*((volatile unsigned long *)   (APB_GPIO_BASE + 0x08) ))
#define REG_APB5_GPIOB_DATA             (*((volatile unsigned long *)   (APB_GPIO_BASE + 0x0C) ))
#define REG_APB5_GPIOC_CFG              (*((volatile unsigned long *)   (APB_GPIO_BASE + 0x10) ))
#define REG_APB5_GPIOC_DATA             (*((volatile unsigned long *)   (APB_GPIO_BASE + 0x14) ))
#define REG_APB5_GPIOD_CFG              (*((volatile unsigned long *)   (APB_GPIO_BASE + 0x18) ))
#define REG_APB5_GPIOD_DATA             (*((volatile unsigned long *)   (APB_GPIO_BASE + 0x1C) ))
#define REG_APB5_GPIOE_CFG              (*((volatile unsigned long *)   (APB_GPIO_BASE + 0x20) ))
#define REG_APB5_GPIOE_DATA             (*((volatile unsigned long *)   (APB_GPIO_BASE + 0x24) ))

#define REG_APB5_GPIO_WUATOD_TYPE       (*((volatile unsigned long *)   (APB_GPIO_BASE + 0x40) ))
#define REG_APB5_GPIO_WUE_TYPE          (*((volatile unsigned long *)   (APB_GPIO_BASE + 0x44) ))
#define REG_APB5_GPIO_WUATOD_ENABLE     (*((volatile unsigned long *)   (APB_GPIO_BASE + 0x48) ))
#define REG_APB5_GPIO_WUE_ENABLE        (*((volatile unsigned long *)   (APB_GPIO_BASE + 0x4C) ))
#define REG_APB5_GPIO_WUATOD_STAT       (*((volatile unsigned long *)   (APB_GPIO_BASE + 0x50) ))
#define REG_APB5_GPIO_WUE_STAT          (*((volatile unsigned long *)   (APB_GPIO_BASE + 0x54) ))

// GPIO config[7:0] are peripheral function enable low active. 0-Peri Function enable. 1-Normal GPIO.
#define BIT_GPIO_NORMAL                 0
#define BIT_GPIO_OUT_EN_N               8
#define BIT_GPIO_PULL_UP                16
#define BIT_GPIO_PULL_DOWN              24
#define BIT_GPIO_OUT_BUFFER             0
#define BIT_GPIO_IN_BUFFER              8
#define BIT_GPIO_INPUT_EN               16

#define BIT_GPIOA_WU_TYPE               0
#define BIT_GPIOB_WU_TYPE               8
#define BIT_GPIOC_WU_TYPE               16
#define BIT_GPIOD_WU_TYPE               24
#define BIT_GPIOE_WU_TYPE               0

#define GPIOA					0
#define GPIOB					1
#define GPIOC					2
#define GPIOD					3
#define GPIOE					4
#define GPIO0					0
#define GPIO1					1
#define GPIO2					2
#define GPIO3					3
#define GPIO4					4
#pragma anon_unions

typedef struct HW_GPIOU{
	union{
		uint32 REG_0x0;
		struct{
			uint32 normal:8;
			//0��GPIO����ڶ����ܣ�1����ͨGPIO
			uint32 oe_n:8;
			//��Ӧ��GPIO�����ʹ�ܣ�0-��Ϊ�����1-�������
			uint32 pu:8;
			//��Ӧ��GPIO������ʹ�ܣ�0-������������������1-������
			uint32 pd:8;
			//��Ӧ��GPIO������ʹ�ܣ�0-����������3-������
		};
	};
	union{
		uint32 REG_0x1;
		struct{
			uint32 od:8;
			//GPIOA[7:0]����Ĵ���ֵ
			uint32 id:8;
			//GPIOA[7:0]��������ֵ
			uint32 ie:8;
			//��Ӧ��GPIO������ʹ�ܣ�0-�������룬2-��Ϊ����
		};
	};
}HW_GPIOU;

#pragma anon_unions
typedef struct HW_GPIO{
	HW_GPIOU gpio[NUM_GPIO_PORT];
	uint32 rsv[6];
	union{
		uint32 REG_0xA[2];
		uint32 wu_type[2];
		struct{
			uint32 wu_type_0:8;
			uint32 wu_type_1:8;
			uint32 wu_type_2:8;
			uint32 wu_type_3:8;
			uint32 wu_type_4:8;
			uint32 wu_type_5:8;
			uint32 wu_type_6:8;
			uint32 wu_type_7:8;
			//GPIO�������ͣ�1-�����ػ��ѣ�0-�½��ػ��ѡ�
		};
	};
	union{
		uint32 REG_0xC[2];
		uint32 wu_en[2];
		struct{
			uint32 wu_e_0:8;
			uint32 wu_e_1:8;
			uint32 wu_e_2:8;
			uint32 wu_e_3:8;
			uint32 wu_e_4:8;
			//GPIO����ʹ�ܣ�1-�жϻ��ѣ�0-��ʹ�ܡ�
			uint32 wu_e_5:8;
			uint32 wu_e_6:8;
			uint32 wu_e_7:8;
		};
	};
	union{
		uint32 REG_0xE[2];
		uint32 wu_stat[2];
		struct{
			uint32 wu_stat_0:8;
			uint32 wu_stat_1:8;
			uint32 wu_stat_2:8;
			uint32 wu_stat_3:8;
			uint32 wu_stat_4:8;
			uint32 wu_stat_5:8;
			uint32 wu_stat_6:8;
			uint32 wu_stat_7:8;
			//GPIO�ж�״̬λ��1-�жϲ�����0-û���жϡ�д1����ж�
		};
	};
}HW_GPIO;
#define GPIO_BFD_BS_NORMAL			0
#define GPIO_BFD_BL_NORMAL			8
#define GPIO_BFD_BS_OE_N			8
#define GPIO_BFD_BL_OE_N			8
#define GPIO_BFD_BS_PU				16
#define GPIO_BFD_BL_PU				8
#define GPIO_BFD_BS_PD				24
#define GPIO_BFD_BL_PD				8

#define GPIO_BFD_BS_OD				0
#define GPIO_BFD_BL_OD				8
#define GPIO_BFD_BS_ID				8
#define GPIO_BFD_BL_ID				8
#define GPIO_BFD_BS_IE				16
#define GPIO_BFD_BL_IE				8

#define GPIO_OutputLow(pn,pl)	\
	/*����:ָ���˿�ָ����λ���0*/\
	/*pn:�˿ں�;pl:��Ҫ���0�Ĺܽ��б�*/\
	{BK2471_GPIO_DATA(pn) &= _BFD(pl,GPIO_BFD_BS_OD,GPIO_BFD_BL_OD);}
	

#define GPIO_OutputHigh(pn,pl)	\
	/*����:ָ���˿�ָ����λ���1*/\
	/*pn:�˿ں�;pl:��Ҫ���1�Ĺܽ��б�*/\
	{BK2471_GPIO_DATA(pn) |= BFD(pl,GPIO_BFD_BS_OD,GPIO_BFD_BL_OD);}

#define GPIO_OutputNeg(pn,pl)	\
	/*����:ָ���˿�ָ����λ�����ƽ��ת*/\
	/*pn:�˿ں�;pl:��Ҫ�����Ĺܽ��б�*/\
	{BK2471_GPIO_DATA(pn) ^= BFD(pl,GPIO_BFD_BS_OD,GPIO_BFD_BL_OD);}

#define GPIO_Input(pn)	\
	/*����:��ȡָ���˿ڵ�ƽ״̬*/\
	/*pn:�˿ں�;*/\
	(GET_BFD(BK2471_GPIO_DATA(pn),GPIO_BFD_BS_ID,GPIO_BFD_BL_ID))

#define GPIO_SetSF(pn,sfl)	\
	/*����:ָ���˿����ó����⹦�ܽ�*/\
	/*pn:�˿ں�;sfl:��Ҫ��Ϊ���⹦�ܵĹܽ��б�*/\
	{\
	BK2471_GPIO_CONFIG(pn) &= (_BFD(sfl,GPIO_BFD_BS_NORMAL,GPIO_BFD_BL_NORMAL)&\
		_BFD(sfl,GPIO_BFD_BS_PU,GPIO_BFD_BL_PU)&\
		_BFD(sfl,GPIO_BFD_BS_PD,GPIO_BFD_BL_PD));\
	}

#define GPIO_InputSetup(pn,i,pullup,pulldw) \
	/*����:��ָ���˿ڽ������������趨*/\
	/*pn:�˿ں�;i��pu��pd:��Ҫ��Ϊ���롢ʹ��������ʹ�������Ĺܽ��б�*/\
	{\
	BK2471_GPIO_CONFIG(pn) |= (BFD(i,GPIO_BFD_BS_OE_N,GPIO_BFD_BL_OE_N)|\
										BFD(i,GPIO_BFD_BS_NORMAL,GPIO_BFD_BL_NORMAL)|\
										BFD(pullup,GPIO_BFD_BS_PU,GPIO_BFD_BL_PU)|\
										BFD(pulldw,GPIO_BFD_BS_PD,GPIO_BFD_BL_PD));\
	BK2471_GPIO_DATA(pn) |= (BFD(i,GPIO_BFD_BS_IE,GPIO_BFD_BL_IE));\
	}

#define GPIO_DiablePU(pn,pul) \
	{\
	/*����:����ָ���˿�������������*/\
	/*pn:�˿ں�;pu:��Ҫ��ֹ�����Ĺܽ��б�*/\
	BK2471_GPIO_CONFIG(pn) &= (_BFD(pul,GPIO_BFD_BS_PU,GPIO_BFD_BL_PU));\
	}

#define GPIO_DiablePD(pn,pdl) \
	{\
	/*����:����ָ���˿�������������*/\
	/*pn:�˿ں�;pd:��Ҫ��ֹ�����Ĺܽ��б�*/\
	BK2471_GPIO_CONFIG(pn) &= (_BFD(pdl,GPIO_BFD_BS_PD,GPIO_BFD_BL_PD));\
	}

#define GPIO_EnablePU(pn,pul) \
	{\
	/*����:����ָ���˿�������������*/\
	/*pn:�˿ں�;pu:��Ҫ��ֹ�����Ĺܽ��б�*/\
	BK2471_GPIO_CONFIG(pn) |= (BFD(pul,GPIO_BFD_BS_PU,GPIO_BFD_BL_PU));\
}

#define GPIO_EnablePD(pn,pdl) \
	{\
	/*����:����ָ���˿�������������*/\
	/*pn:�˿ں�;pd:��Ҫ��ֹ�����Ĺܽ��б�*/\
	BK2471_GPIO_CONFIG(pn) |= (BFD(pdl,GPIO_BFD_BS_PD,GPIO_BFD_BL_PD));\
	}

#define GPIO_OutputSetup(pn,oe) \
	/*����:��ָ���˿ڽ�����������趨*/\
	/*pn:�˿ں�;oe:��Ҫ��Ϊ����Ĺܽ��б�*/\
	{\
	BK2471_GPIO_CONFIG(pn) |= (BFD(oe,GPIO_BFD_BS_NORMAL,GPIO_BFD_BL_NORMAL));\
	BK2471_GPIO_CONFIG(pn) &= (_BFD(oe,GPIO_BFD_BS_OE_N,GPIO_BFD_BL_OE_N));\
	BK2471_GPIO_DATA(pn) &= (_BFD(oe,GPIO_BFD_BS_IE,GPIO_BFD_BL_IE));\
	}

#define GPIO_HiZ(pn,pl) \
	/*����:��ָ���˿���Ϊ����̬:�����롢���������������������*/\
	/*pn:�˿ں�;pl:��Ҫ��ΪHiZ�Ĺܽ��б�*/\
	{\
	BK2471_GPIO_CONFIG(pn) |= (BFD(pl,GPIO_BFD_BS_NORMAL,GPIO_BFD_BL_NORMAL)|\
								BFD(pl,GPIO_BFD_BS_OE_N,GPIO_BFD_BL_OE_N));\
	BK2471_GPIO_CONFIG(pn) &= ~(BFD(pl,GPIO_BFD_BS_PU,GPIO_BFD_BL_PU)|\
							BFD(pl,GPIO_BFD_BS_PD,GPIO_BFD_BL_PD));\
	BK2471_GPIO_DATA(pn) &= (_BFD(pl,GPIO_BFD_BS_IE,GPIO_BFD_BL_IE));\
	}

#define GPIO_InterruptSetup(pn,enl,f_el,r_el) \
	/*����:��ָ���˿��ж��趨*/\
	/*pn:�˿ں�;enl��r_el��f_el:��Ҫ��Ϊ�ܹ��жϡ��������жϡ��½����жϵĹܽ��б�*/\
	{\
	if(pn<4){\
		if(f_el&enl)/*BASE_GPIO_PTR->wu_type[pn>>2]*/REG32(GET_REG_ADDR(REG_APB5_GPIO_WUATOD_TYPE)+(pn>>2)*4) |= (BFD(f_el&enl,pn*8,8));\
		if(r_el&enl)/*BASE_GPIO_PTR->wu_type[pn>>2]*/REG32(GET_REG_ADDR(REG_APB5_GPIO_WUATOD_TYPE)+(pn>>2)*4) &= (_BFD(r_el&enl,pn*8,8));\
		/*BASE_GPIO_PTR->wu_en[pn>>2]*/REG32(GET_REG_ADDR(REG_APB5_GPIO_WUATOD_ENABLE)+(pn>>2)*4) |= (BFD(enl,pn*8,8));\
	}else {\
		if(f_el&enl)/*BASE_GPIO_PTR->wu_type[pn>>2]*/REG32(GET_REG_ADDR(REG_APB5_GPIO_WUATOD_TYPE)+(pn>>2)*4) |= (BFD(f_el&enl,(pn-4)*8,8));\
		if(r_el&enl)/*BASE_GPIO_PTR->wu_type[pn>>2]*/REG32(GET_REG_ADDR(REG_APB5_GPIO_WUATOD_TYPE)+(pn>>2)*4) &= (_BFD(r_el&enl,(pn-4)*8,8));\
		/*BASE_GPIO_PTR->wu_en[pn>>2]*/REG32(GET_REG_ADDR(REG_APB5_GPIO_WUATOD_ENABLE)+(pn>>2)*4) |= (BFD(enl,(pn-4)*8,8));\
	}\
	}


#define GPIO_WakeupSetup(pn,enl,f_el,r_el) \
	/*����:��ָ���˿ڽ��л��ѹ����趨*/\
	/*pn:�˿ں�;enl��r_el��f_el:��Ҫ��Ϊ�ܹ����ѡ������ػ��ѡ��½��ػ��ѵĹܽ��б�*/\
	{\
	GPIO_InterruptSetup(pn,enl,f_el,r_el);\
	}

#define GPIO_InterruptEnable(pn,en) \
	/*����:��ָ���˿��ж��趨*/\
	/*pn:�˿ں�;en:ʹ��*/\
	{\
	BASE_ICU_PTR->INT_FLAG|=BIT(PID_GPIO);\
	BASE_ICU_PTR->INT_EN|=BIT(PID_GPIO);\
	if((en)==0){\
		if(pn<4)/*BASE_GPIO_PTR->wu_en[pn>>2]*/REG32(GET_REG_ADDR(REG_APB5_GPIO_WUATOD_ENABLE)+(pn>>2)*4) &= _BFD(0xff,pn*8,8);\
		else /*BASE_GPIO_PTR->wu_en[pn>>2]*/REG32(GET_REG_ADDR(REG_APB5_GPIO_WUATOD_ENABLE)+(pn>>2)*4) &= _BFD(0xff,(pn-4)*8,8);\
	}\
	}

#define GPIO_ClearIF(pn,enl) \
	/*����:��ָ���˿��ж��趨*/\
	/*pn:�˿ں�;en:ʹ��*/\
	{\
	/*BASE_GPIO_PTR->REG_0xE[0]*/REG32(GET_REG_ADDR(REG_APB5_GPIO_WUATOD_STAT)) = 0xffffffff;\
	/*BASE_GPIO_PTR->REG_0xE[1]*/ REG32(GET_REG_ADDR(REG_APB5_GPIO_WUATOD_STAT)+4)= 0xff;\
	}

#if 0
#define GPIO_Output(pn)	\
	/*����:ָ���˿����*/\
	/*pn:�˿ں�;*/\
	(*(volatile uint8 *)(ADDR_GPIO_PTR+(8*pn)+5))/*BASE_GPIO_PTR->gpio[pn].od*/

#define GPIO_OutputLow(pn,pl)	\
	/*����:ָ���˿�ָ����λ���0*/\
	/*pn:�˿ں�;pl:��Ҫ���0�Ĺܽ��б�*/\
	GPIO_Output(pn)&=(~(pl))

#define GPIO_OutputHigh(pn,pl)	\
	/*����:ָ���˿�ָ����λ���1*/\
	/*pn:�˿ں�;pl:��Ҫ���1�Ĺܽ��б�*/\
	GPIO_Output(pn)|=((pl))

#define GPIO_OutputNeg(pn,pl)	\
	/*����:ָ���˿�ָ����λ�����ƽ��ת*/\
	/*pn:�˿ں�;pl:��Ҫ�����Ĺܽ��б�*/\
	GPIO_Output(pn)^=((pl))

#define GPIO_Input(pn)	\
	/*����:��ȡָ���˿ڵ�ƽ״̬*/\
	/*pn:�˿ں�;*/\
	BASE_GPIO_PTR->gpio[pn].id

#define GPIO_SetSF(pn,sfl)	\
	/*����:ָ���˿����ó����⹦�ܽ�*/\
	/*pn:�˿ں�;sfl:��Ҫ��Ϊ���⹦�ܵĹܽ��б�*/\
	{\
	BASE_GPIO_PTR->gpio[pn].normal &= (~(sfl));\
	BASE_GPIO_PTR->gpio[pn].pu &= (~(sfl));\
	BASE_GPIO_PTR->gpio[pn].pd &= (~(sfl));\
	}

#define GPIO_InputSetup(pn,i,pullup,pulldw) \
	/*����:��ָ���˿ڽ������������趨*/\
	/*pn:�˿ں�;i��pu��pd:��Ҫ��Ϊ���롢ʹ��������ʹ�������Ĺܽ��б�*/\
	{\
	BASE_GPIO_PTR->gpio[pn].normal |= (i);\
	BASE_GPIO_PTR->gpio[pn].ie |= ((i));\
	BASE_GPIO_PTR->gpio[pn].oe_n |= ((i));\
	if(pullup){BASE_GPIO_PTR->gpio[pn].pu |= ((pullup));}\
	if(pulldw){BASE_GPIO_PTR->gpio[pn].pd |= ((pulldw));}\
	}

#define GPIO_DiablePU(pn,pul) \
	{\
	/*����:����ָ���˿�������������*/\
	/*pn:�˿ں�;pu:��Ҫ��ֹ�����Ĺܽ��б�*/\
	if(pul){BASE_GPIO_PTR->gpio[pn].pu &= (~(pul));}\
	}

#define GPIO_DiablePD(pn,pdl) \
	{\
	/*����:����ָ���˿�������������*/\
	/*pn:�˿ں�;pd:��Ҫ��ֹ�����Ĺܽ��б�*/\
	if(pdl)BASE_GPIO_PTR->gpio[pn].pd  &= (~(pdl));\
	}


#define GPIO_OutputSetup(pn,oe) \
	/*����:��ָ���˿ڽ�����������趨*/\
	/*pn:�˿ں�;oe:��Ҫ��Ϊ����Ĺܽ��б�*/\
	{\
	BASE_GPIO_PTR->gpio[pn].normal |= (oe);\
	BASE_GPIO_PTR->gpio[pn].ie &= (~(oe));\
	BASE_GPIO_PTR->gpio[pn].oe_n &= (~(oe));\
	}

#define GPIO_OutputSetup(pn,oe) \
	/*����:��ָ���˿ڽ�����������趨*/\
	/*pn:�˿ں�;oe:��Ҫ��Ϊ����Ĺܽ��б�*/\
	{\
	BASE_GPIO_PTR->gpio[pn].REG_0x0 |= (BFD(oe,0,8));\
	BASE_GPIO_PTR->gpio[pn].REG_0x0 &= (_BFD(oe,8,8));\
	BASE_GPIO_PTR->gpio[pn].REG_0x1 &= (_BFD(oe,16,8));\
	}

#define GPIO_WakeupSetup(pn,enl,modl,modh) \
	/*����:��ָ���˿ڽ��л��ѹ����趨*/\
	/*pn:�˿ں�;enl��modl��modh:��Ҫ��Ϊ�ܹ����ѡ��͵�ƽ���ѡ��ߵ�ƽ���ѵĹܽ��б�*/\
	{\
	if(enl)BASE_GPIO_PTR->wu_en[pn] |= ((enl));\
	if(modh&enl)BASE_GPIO_PTR->wu_type[pn] |= ((modh));\
	if(modl&enl)BASE_GPIO_PTR->wu_type[pn] &= (~(modl));\
	}

#define GPIO_InterruptSetup(pn,enl,f_el,r_el) \
	/*����:��ָ���˿��ж��趨*/\
	/*pn:�˿ں�;enl��r_el��f_el:��Ҫ��Ϊ�ܹ��жϡ��������жϡ��½����жϵĹܽ��б�*/\
	{\
	if(((f_el)&(enl)))BASE_GPIO_PTR->wu_type[pn] |= ((f_el));\
	if(((r_el)&(enl)))BASE_GPIO_PTR->wu_type[pn] &= (~(r_el));\
	if(enl)BASE_GPIO_PTR->wu_en[pn] = ((enl));\
	}

#define GPIO_InterruptEnable(pn,en) \
	/*����:��ָ���˿��ж��趨*/\
	/*pn:�˿ں�;en:ʹ��*/\
	{\
	BASE_ICU_PTR->gpio_if = 1;\
	BASE_ICU_PTR->gpio_int_en = en;\
	/*BASE_ICU_PTR->gpio_wakeup_en = en;*/\
	if((en)==0){\
		BASE_GPIO_PTR->wu_en[pn] = 0;\
	}\
	}

#define GPIO_ClearIF(pn,enl) \
	/*����:��ָ���˿��ж��趨*/\
	/*pn:�˿ں�;en:ʹ��*/\
	{\
	BASE_GPIO_PTR->REG_0xE[0] = 0xffffffff;\
	BASE_GPIO_PTR->REG_0xE[1] = 0xff;\
	}
#endif

#endif
