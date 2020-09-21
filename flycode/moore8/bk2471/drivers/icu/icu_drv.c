#include <stdio.h>
#include "..\gpio\gpio.h"
#include "..\icu\icu.h"
#include "..\flash\flash.h"
#include "..\xvr\XVR_3231S.h"
#include "..\..\common\common.h"


#define PRN_NAME_VAL(name,fmt)	\
	""#name##"="##fmt##"\r\n",name
#if 0
#define AHB_ICU_BASE             0x00800000
#define REG_AHB0_ICU_ANALOG0_PWD           (*((volatile unsigned long *)   (AHB_ICU_BASE + 0x54) ))
#define REG_AHB0_ICU_ANALOG_MODE           (*((volatile unsigned long *)   (AHB_ICU_BASE + 0x50) ))
#define REG_AHB0_ICU_CORECLKCON            (*((volatile unsigned long *)   (AHB_ICU_BASE + 0x04) ))
#define REG_AHB0_ICU_CLKSRCSEL             (*((volatile unsigned long *)   (AHB_ICU_BASE + 0x00) ))
#define REG_AHB0_ICU_DIGITAL_PWD           (*((volatile unsigned long *)   (AHB_ICU_BASE + 0x5c) ))

#define REG_AHB0_BOOST_READY_DLY           (*((volatile unsigned long *)   (AHB_ICU_BASE + 0x70) ))

#define REG_AHB0_DCO16M_PWD                (*((volatile unsigned long *)   (AHB_ICU_BASE + 0x80) ))
#define REG_AHB0_ICU_LPO_CLKCON            (*((volatile unsigned long *)   (AHB_ICU_BASE + 0x24) ))
#define REG_AHB0_ICU_CEVA_CLKCON           (*((volatile unsigned long *)   (AHB_ICU_BASE + 0x18) ))

#define REG_AHB0_JTAG_MODE                 (*((volatile unsigned long *)   (AHB_ICU_BASE + 0x98) ))

#define REG_AHB0_FIQ_PRIORITY_EN           (*((volatile unsigned long *)   (AHB_ICU_BASE + 0x7C) ))
#endif

void ICU_SetSysclk16M(void){
//	UI32 cpu_flags;
	HW_ICU*icu=BASE_ICU_PTR;


	icu->CLK_SRC_SEL=ICU_CLKSRC_16M;
	icu->core = 0;
	Delay(2);
	icu->pwdSARADC1V = 1;
	icu->pwd48MPLL1V = 1;
}

void ICU_SetSysclk96M(int div){
	HW_XVR_3231S*xvr=BASE_XVR_3231S_PTR;
	HW_ICU*icu=BASE_ICU_PTR;
	icu->REG_0x17 = 0;
//	PRINT("step 1\r\n");
	xvr->REG_0x9 = 0x19407d80;
	//xvr->digpll_pwd_spi = 1;
//	PRINT("step 2\r\n");
	icu->pwdSARADC1V =0;
	icu->pwd48MPLL1V = 0;
//	PRINT("step 3\r\n");
	Delay(5);
	xvr->REG_0x9 = 0x19407d00;
	//xvr->digpll_pwd_spi = 0;
//	PRINT("step 4\r\n");
	Delay(20);
	icu->CORE_DIV = div;
//	PRINT("step 5\r\n");
	icu->CORE_PWD = 0;
//	PRINT("step 6\r\n");
	icu->CLK_SRC_SEL = ICU_CLKSRC_PLL ;
//	PRINT("step 7\r\n");
	//BASE_FLASH_PTR->flash_clk_conf = BIT(3);
//	PRINT("step 8\r\n");
}

int ICU_GetSystemClk(void){
////	HW_XVR_3231S*xvr=BASE_XVR_3231S_PTR;
	HW_ICU*icu=BASE_ICU_PTR;
	int freq=96000000;
	if(icu->CLK_SRC_SEL==ICU_CLKSRC_16M){
		freq=16000000;
	}
	if(icu->CLK_SRC_SEL==ICU_CLKSRC_32K){
		freq=32000;
	}
	return(freq/(icu->CORE_DIV+1));
}

int ICU_CheckSystem96M(void){
	HW_ICU*icu=BASE_ICU_PTR;
	if((icu->CLK_SRC_SEL==ICU_CLKSRC_PLL)&&(icu->CORE_DIV==0))return(1);
	return(0);
}

int ICU_CheckSystem48M(void){
	HW_ICU*icu=BASE_ICU_PTR;
	if((icu->CLK_SRC_SEL==ICU_CLKSRC_PLL)&&(icu->CORE_DIV==1))return(1);
	return(0);
}

void ICU_EnableIRQ(HW_ICU*icu){
	icu->IRQ_EN = 1;
}

void ICU_EnableFIQ(HW_ICU*icu){
	icu->FIQ_EN = 1;
}

void ICU_DisableIRQ(HW_ICU*icu){
	icu->IRQ_EN = 0;
}

void ICU_DisableFIQ(HW_ICU*icu){
	icu->FIQ_EN = 0;
}

void ICU_Initial(void)
#if 1
{
	HW_ICU*icu=BASE_ICU_PTR;
	icu->jtag_mode = 0;
	icu->digital_pwd = 0;
	icu->dco16m_pwd =1;
	icu->boost_ready_dly = 0x500;
#ifdef LPO_GEN_IS_16M_TO_32K
	icu->LPO_GEN = LPO_GEN_FROM_DIV;
#else
	icu->LPO_GEN = LPO_GEN_FROM_XTAL;
#endif

	icu->ceva = 0;
	//icu->fiq_priority = BIT(PID_CEVA);
	icu->fiq_irq = (BIT(PID_CEVA)|BIT(PID_UART));/*解决超过20B接收时丢信息的bug*/\
	BASE_XVR_3231S_PTR->REG_0x9 =0x19407D80;
	icu->pwdSARADCldo1V_en = 1;
	Delay(10);
	icu->pwd48MPLL1V_en = 1;
	Delay(2);
	BASE_XVR_3231S_PTR->REG_0x9 =0x19407D00;
	Delay(20);
	BASE_FLASH_PTR->flash_clk_conf = BIT(3);

	//icu->fiq_irq |= BIT(PID_UART);

	ICU_EnableFIQ(icu);
	ICU_EnableIRQ(icu);

}
#else
{
	HW_ICU*icu=BASE_ICU_PTR;
	icu->jtag_mode = 0;
	icu->digital_pwd = 0;
	icu->dco16m_pwd =1;
	icu->boost_ready_dly = 0x500;
#ifdef LPO_GEN_IS_16M_TO_32K
	icu->LPO_GEN = LPO_GEN_FROM_DIV;
#else
	icu->LPO_GEN = LPO_GEN_FROM_XTAL;
#endif

	icu->ceva = 0;
	icu->fiq_priority = BIT(PID_CEVA);
	BASE_XVR_3231S_PTR->REG_0x9 =0x19407D80;
	icu->pwdSARADCldo1V_en = 1;
	Delay(10);
	icu->pwd48MPLL1V_en = 1;
	Delay(2);
	BASE_XVR_3231S_PTR->REG_0x9 =0x19407D00;
	Delay(20);
	BASE_FLASH_PTR->flash_clk_conf = BIT(3);
	ICU_EnableFIQ(icu);
	ICU_EnableIRQ(icu);
}

#endif
