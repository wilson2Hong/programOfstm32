#ifndef _PWM_H_
#define _PWM_H_

#include "..\..\includes\types.h"
#include "..\gpio\gpio.h"
#include "..\icu\icu.h"
#include "..\bt_3ds\bt_3ds.h"

#define	BASE_PWM_PTR	\
		((HW_PWM*)0x00f00100)

//=====================================================================================
// 16bit PWM & Timer
//=====================================================================================
#define REG_APB_BK_PWM_CTRL    (*( (volatile unsigned long *)   (APB_PWM_BASE + (0x0*4)) ))
#define bit_PWM0_EN				BIT_0
#define bit_PWM0_INT_ENABLE		BIT_1
#define bit_PWM0_MODE			2

#define bit_PWM1_EN				BIT_4
#define bit_PWM1_INT_ENABLE		BIT_5
#define bit_PWM1_MODE			6

#define bit_PWM2_EN				BIT_8
#define bit_PWM2_INT_ENABLE		BIT_9
#define bit_PWM2_MODE			10

#define bit_PWM3_EN				BIT_12
#define bit_PWM3_INT_ENABLE		BIT_13
#define bit_PWM3_MODE			14

#define bit_PWM4_EN				BIT_16
#define bit_PWM4_INT_ENABLE		BIT_17
#define bit_PWM4_MODE			18

#define bit_PWM5_EN				BIT_20
#define bit_PWM5_INT_ENABLE		BIT_21
#define bit_PWM5_MODE			22

#define REG_APB_BK_PWM_INTR    (*( (volatile unsigned long *)   (APB_PWM_BASE + (0x1*4)) ))
#define REG_APB_BK_PWM0_CNT    (*( (volatile unsigned long *)   (APB_PWM_BASE + (0x2*4)) ))
#define REG_APB_BK_PWM0_CAP    (*( (volatile unsigned long *)   (APB_PWM_BASE + (0x3*4)) ))
#define REG_APB_BK_PWM1_CNT    (*( (volatile unsigned long *)   (APB_PWM_BASE + (0x4*4)) ))
#define REG_APB_BK_PWM1_CAP    (*( (volatile unsigned long *)   (APB_PWM_BASE + (0x5*4)) ))
#define REG_APB_BK_PWM2_CNT    (*( (volatile unsigned long *)   (APB_PWM_BASE + (0x6*4)) ))
#define REG_APB_BK_PWM2_CAP    (*( (volatile unsigned long *)   (APB_PWM_BASE + (0x7*4)) ))
#define REG_APB_BK_PWM3_CNT    (*( (volatile unsigned long *)   (APB_PWM_BASE + (0x8*4)) ))
#define REG_APB_BK_PWM3_CAP    (*( (volatile unsigned long *)   (APB_PWM_BASE + (0x9*4)) ))
#define REG_APB_BK_PWM4_CNT    (*( (volatile unsigned long *)   (APB_PWM_BASE + (0xA*4)) ))
#define REG_APB_BK_PWM4_CAP    (*( (volatile unsigned long *)   (APB_PWM_BASE + (0xB*4)) ))
#define REG_APB_BK_PWM5_CNT    (*( (volatile unsigned long *)   (APB_PWM_BASE + (0xC*4)) ))
#define REG_APB_BK_PWM5_CAP    (*( (volatile unsigned long *)   (APB_PWM_BASE + (0xD*4)) ))
#define REG_APB_BK_PWM6_CNT    (*( (volatile unsigned long *)   (APB_PWM_BASE + (0xE*4)) ))
#define REG_APB_BK_PWM6_CAP    (*( (volatile unsigned long *)   (APB_PWM_BASE + (0xF*4)) ))

#pragma anon_unions
typedef struct HW_PWMU{
	union{
		uint32 setting;
		struct{
			uint32 end:16;
			//PWM0 counter end-value
			uint32 dc:16;
			//PWM0 Duty-Cycle. Must smaller or equal to end-value
		};
	};
	union{
		uint32 counter;
		struct{
			uint32 cap_out:16;
			//PWM0 capture value. Read-Only.
			uint32 :16;
		};
	};
}HW_PWMU;
typedef struct HW_PWM{
	union{
		uint32 cfg;
		struct{
			uint32 pwm0_en:1;
			//PWM0 1bit unit enable         ;0-Disable. 1-Enable
			uint32 pwm0_int_en:1;
			//PWM0 1bit interrupt enable;0-Disable. 1-Enable
			uint32 pwm0_mode:2;
			//PWM0 2bit mode selection;00: PWM Mode;01: TIMER;10: Capture Posedge;11: Cpature Negedge
			uint32 pwm1_en:1;
			//PWM1 1bit unit enable;0-Disable. ;1-Enable
			uint32 pwm1_int_en:1;
			//PWM1 1bit interrupt enable;0-Disable. ;1-Enable.
			uint32 pwm1_mode:2;
			//PWM1 2bit mode selection;00: PWM Mode;01: TIMER;10: Capture Posedge;11: Cpature Negedge
			uint32 pwm2_en:1;
			//PWM2 1bit unit enable         ;0-Disable. 1-Enable
			uint32 pwm2_int_en:1;
			//PWM2 1bit interrupt enable;0-Disable. 1-Enable
			uint32 pwm2_mode:2;
			//PWM2 2bit mode selection;00: PWM Mode;01: TIMER;10: Capture Posedge;11: Cpature Negedge
			uint32 pwm3_en:1;
			//PWM3 1bit unit enable;0-Disable. ;1-Enable
			uint32 pwm3_int_en:1;
			//PWM3 1bit interrupt enable;0-Disable. ;1-Enable.
			uint32 pwm3_mode:2;
			//PWM3 2bit mode selection;00: PWM Mode;01: TIMER;10: Capture Posedge;11: Cpature Negedge
			uint32 pwm4_en:1;
			//PWM4 1bit unit enable         ;0-Disable. 1-Enable
			uint32 pwm4_int_en:1;
			//PWM4 1bit interrupt enable;0-Disable. 1-Enable
			uint32 pwm4_mode:2;
			//PWM4 2bit mode selection;00: PWM Mode;01: TIMER;10: Capture Posedge;11: Cpature Negedge
			uint32 pwm5_en:1;
			//PWM5 1bit unit enable;0-Disable. ;1-Enable
			uint32 pwm5_int_en:1;
			//PWM5 1bit interrupt enable;0-Disable. ;1-Enable.
			uint32 pwm5_mode:2;
			//PWM5 2bit mode selection;00: PWM Mode;01: TIMER;10: Capture Posedge;11: Cpature Negedge
			uint32 :8;
		};
	};
	union{
		uint32 REG_0x1;
		struct{
			uint32 pwm0_int:1;
			//PWM0 Interrupt Status. Write 1 to clear.
			uint32 pwm1_int:1;
			//PWM1 Interrupt Status. Write 1 to clear.
			uint32 pwm2_int:1;
			//PWM2 Interrupt Status. Write 1 to clear.
			uint32 pwm3_int:1;
			//PWM3 Interrupt Status. Write 1 to clear.
			uint32 pwm4_int:1;
			//PWM4 Interrupt Status. Write 1 to clear.
			uint32 pwm5_int:1;
			//PWM5 Interrupt Status. Write 1 to clear.
			uint32 :26;
		};
	};
    HW_PWMU pwms[6];
}HW_PWM;

#define PWM0 \
    0

#define PWM1 \
    1

#define PWM2 \
    2

#define PWM3 \
    3

#define PWM4 \
    4

#define PWM5 \
    5

#define PWM8 \
	8

#define PWM9 \
	9

#define PWM10 \
	10

#define PWM11 \
	11

#define PWM_CLKSEL_32K \
    0

#define PWM_CLKSEL_16M \
    1

#define PWM_CLKSEL_DPLL \
    2

#define PWM_BFD_BS_END		0
#define PWM_BFD_BL_END		16
#define PWM_BFD_BS_DUTY		16
#define PWM_BFD_BL_DUTY		16

#define BK2471_PWM_CTRL				REG32(APB_PWM_BASE)
#define BK2471_PWM_SETTING(pn)		REG32(APB_PWM_BASE+8+(pn)*8)
#define BK2471_PWM_CAP(pn)			REG32(APB_PWM_BASE+0x0c+(pn)*8)

#define PWM_SetupIOL(bl) \
	{\
	if(bl&0xff)GPIO_SetSF(GPIOB, (bl&0xff));\
	if(bl&0xf00)GPIO_SetSF(GPIOA, ((bl)>>8));\
	}

#define PWM_OPEN_CLOCK(pn,pwmsel) \
	{\
    /*pn:pwm编号,0-5 pwmsel:pwm时钟源选择 */\
	if((pn)==PWM5){\
		/*BASE_ICU_PTR->pwm[4].pwm_clk*/REG_AHB0_ICU_PWM4CLKCON &= _BFD(7,4,3);\
		/*BASE_ICU_PTR->pwm[4].pwm_clk*/REG_AHB0_ICU_PWM4CLKCON |= BFD(pwmsel,5,2);\
	}else{\
		if(pn<8){\
			/*BASE_ICU_PTR->pwm[pn].pwm_clk*/REG32(GET_REG_ADDR(REG_AHB0_ICU_PWM0CLKCON)+ (pn)*4) &= _BFD(7,0,3);\
			/*BASE_ICU_PTR->pwm[pn].pwm_clk*/REG32(GET_REG_ADDR(REG_AHB0_ICU_PWM0CLKCON)+ (pn)*4) |= BFD(pwmsel,1,2);\
		}else{\
			/*BASE_ICU_PTR->ceva = 0;*/REG_AHB0_ICU_CEVA_CLKPWD=0;\
		}\
	}\
	}

#define PWM_Setup(pn,pres,resol,duty) \
    {\
    /*pn:pwm编号,0-5 pres:pwm预分频 */\
    /*pn>7,resol = end,duty = mid*/\
    /*resol:pwm周期(pres*resol<65536) duty:占空比*/\
    if((pn)<=PWM5){\
		/*BASE_PWM_PTR->pwms[pn].setting*/BK2471_PWM_SETTING(pn) =(BFD((pres)*(resol),PWM_BFD_BS_END,PWM_BFD_BL_END)|\
										BFD((pres)*(duty),PWM_BFD_BS_DUTY,PWM_BFD_BL_DUTY));\
	}else if((pn)>=PWM8){\
		BASE_BT_3DS_PTR->REG_0x12	= ((((pres)*(resol))-1)>>4);\
		BASE_BT_3DS_PTR->REG_0x13	= ((((pres)*(resol))-1)&0x0f)<<4;\
		BASE_BT_3DS_PTR->pwms[pn-PWM8].d[0]=BFD(0,0,22);\
		BASE_BT_3DS_PTR->pwms[pn-PWM8].d[1]=BFD((pres)*(duty),0,22);\
		BASE_BT_3DS_PTR->pwms[pn-PWM8].d[2]=BFD((pres)*(resol),0,22);\
	}\
	}

#define PWM_SET_DUTY(pn,pres,duty) \
    {\
    /*pn:pwm编号,0-5  duty:占空比*/\
	if(pn<8){\
		/*BASE_PWM_PTR->pwms[pn].setting*/BK2471_PWM_SETTING(pn) &= _BFD(0xffff,PWM_BFD_BS_DUTY,PWM_BFD_BL_DUTY);\
		/*BASE_PWM_PTR->pwms[pn].setting*/BK2471_PWM_SETTING(pn) |= BFD((duty)*(pres),PWM_BFD_BS_DUTY,PWM_BFD_BL_DUTY);\
	}else{\
		BASE_BT_3DS_PTR->pwms[pn-PWM8].d[1]=BFD((duty)*(pres),0,22);\
	}\
	}

#define PWM_Open(pn) \
    {\
    /*pn:pwm编号,0-5*/\
	if((pn)<8){/*BASE_PWM_PTR->cfg*/BK2471_PWM_CTRL |= BIT(4*(pn));}\
	if((pn)>=8){\
		BASE_BT_3DS_PTR->REG_0x0 |= (BIT(1)/*每次都操作*/|BIT((pn))|BIT(((pn)-8)+12));\
	}\
	}

#define PWM_CLOSE_CLOCK(pn) \
	{\
	if((pn)==PWM5){\
		REG_AHB0_ICU_PWM4CLKCON |= (BIT(4));\
	}else{\
		if(pn<8){\
			REG32(GET_REG_ADDR(REG_AHB0_ICU_PWM0CLKCON)+ (pn)*4) |= BIT(0);\
		}else{\
			BASE_ICU_PTR->ceva = 1;\
		}\
	}\
	}

#define PWM_CLOSE(pn) \
    {\
    /*pn:pwm编号,只能是数字0-4*/\
	if(pn<8)BK2471_PWM_CTRL &= _BIT(4*(pn));\
	else{\
		BASE_BT_3DS_PTR->REG_0x0 &=(_BIT((pn))&_BIT(((pn)-8)+12));\
	}\
	PWM_CLOSE_CLOCK(pn);\
	}


#endif
