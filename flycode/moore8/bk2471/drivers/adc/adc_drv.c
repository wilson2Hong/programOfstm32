#include "adc.h"
#include "..\gpio\gpio.h"
#include "..\icu\icu.h"
const uint8 tblAdcChn[]={2,1,5};
/*
 *函数名:
 *	ADC_Init
 *功能:
 *	ADC初始化
 *参数:
 *	无
 *返回:
 *	无
 *特殊:
 *	1.改变:
 *	2.stack:
*/
//比如要打开1、2、4几个通道,初始通道为2：cl=BIT(1)|BIT(2)|BIT(4);chn=2;即可
void ADC_Init(){
	uint32 i;
//	uint32*ptr=(uint32*)BASE_ADC_PTR;
	HW_ICU *icu=BASE_ICU_PTR;
// 	HW_GPIO *gpio=BASE_GPIO_PTR;
// 	HW_ADC*adc=BASE_ADC_PTR;
	uint32 cl;
	//ADC使用步骤:
	//1.使能SAR 1V ldo
	icu->pwdSARADC1V = 0;
	icu->pwdSARADCldo1V = 0;
	icu->pwdSARADC1V_en = 1;
	icu->pwdSARADCldo1V_en = 1;
	//2.设定ADC对应的GPIO进入ADC输入模式
	cl=0;
	for(i=0;i<sizeof(tblAdcChn);i++){
		cl|=BIT(tblAdcChn[i]);
	}
	GPIO_DiablePU(GPIOD,cl);
	GPIO_DiablePD(GPIOD,cl);
	ADC_SetupIO(cl);

	//3.设定ADC SRC clock
	icu->adc = BFD(0x0f, 1, 7);
	//ADC_OPEN_CLOCK(1000000l);

	//4.设定ADC参数
	ADC_10bitSetup(ADC_CLKPRES_4, 1, tblAdcChn[0]);
	//5.打开ADC
	ADC_OPEN();
	//6.等待ADC转换结束,读取ADC结果
	//7.切换ADC通道,至6

}

int ADC_GetTotalChn(){
	return(sizeof(tblAdcChn));
}

void ADC_Samp(int*buf){
	int i;
	uint32 tmp;
	for(i=0;i<sizeof(tblAdcChn);i++){
		ADC_SWITCH_CHN(tblAdcChn[i]);
		while(ADC_CHECK_RDY());
		tmp=BASE_ADC_PTR->DAT;
		while(ADC_CHECK_RDY());
		tmp=BASE_ADC_PTR->DAT;
		buf[i]=tmp;
	}
}
