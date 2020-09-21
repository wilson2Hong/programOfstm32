#include "adc.h"
#include "..\gpio\gpio.h"
#include "..\icu\icu.h"
const uint8 tblAdcChn[]={2,1,5};
/*
 *������:
 *	ADC_Init
 *����:
 *	ADC��ʼ��
 *����:
 *	��
 *����:
 *	��
 *����:
 *	1.�ı�:
 *	2.stack:
*/
//����Ҫ��1��2��4����ͨ��,��ʼͨ��Ϊ2��cl=BIT(1)|BIT(2)|BIT(4);chn=2;����
void ADC_Init(){
	uint32 i;
//	uint32*ptr=(uint32*)BASE_ADC_PTR;
	HW_ICU *icu=BASE_ICU_PTR;
// 	HW_GPIO *gpio=BASE_GPIO_PTR;
// 	HW_ADC*adc=BASE_ADC_PTR;
	uint32 cl;
	//ADCʹ�ò���:
	//1.ʹ��SAR 1V ldo
	icu->pwdSARADC1V = 0;
	icu->pwdSARADCldo1V = 0;
	icu->pwdSARADC1V_en = 1;
	icu->pwdSARADCldo1V_en = 1;
	//2.�趨ADC��Ӧ��GPIO����ADC����ģʽ
	cl=0;
	for(i=0;i<sizeof(tblAdcChn);i++){
		cl|=BIT(tblAdcChn[i]);
	}
	GPIO_DiablePU(GPIOD,cl);
	GPIO_DiablePD(GPIOD,cl);
	ADC_SetupIO(cl);

	//3.�趨ADC SRC clock
	icu->adc = BFD(0x0f, 1, 7);
	//ADC_OPEN_CLOCK(1000000l);

	//4.�趨ADC����
	ADC_10bitSetup(ADC_CLKPRES_4, 1, tblAdcChn[0]);
	//5.��ADC
	ADC_OPEN();
	//6.�ȴ�ADCת������,��ȡADC���
	//7.�л�ADCͨ��,��6

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
