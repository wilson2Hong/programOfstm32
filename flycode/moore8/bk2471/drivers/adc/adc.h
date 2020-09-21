#ifndef _ADC_H_
#define _ADC_H_
#include "..\..\includes\types.h"
#include "..\gpio\gpio.h"
#include "..\icu\icu.h"

#define	BASE_ADC_PTR	\
		((HW_ADC*)0x00f00700)
//=====================================================================================
// ADC
//=====================================================================================
// TBD
#define REG_APB7_ADC_CFG                (*((volatile unsigned long *)   (APB_ADC_BASE + 0x00)))
#define REG_APB7_ADC_DAT                (*((volatile unsigned long *)   (APB_ADC_BASE + 0x04)))

#define BIT_ADC_MODE                    0
#define BIT_ADC_EN                      2
#define BIT_ADC_CHNL                    3
#define BIT_ADC_FIFO_EMPTY              6
#define BIT_ADC_FIFO_BUSY               7//BIT_ADC_FIFO_FULL
#define BIT_ADC_SAMPLE_RATE             8
#define BIT_ADC_WAIT_CLK_SETTING        10
#define BIT_ADC_VALID_MODE              11
#define BIT_ADC_INT_CLEAR               15
#define BIT_ADC_CLK_RATE                16
#define SET_ADC_MODE                    (0x3 << BIT_ADC_MODE            )
#define SET_ADC_EN                      (0x1 << BIT_ADC_EN              )
#define SET_ADC_CHNL                    (0x7 << BIT_ADC_CHNL            )
#define SET_ADC_FIFO_EMPTY              (0x1 << BIT_ADC_FIFO_EMPTY      )
#define SET_ADC_FIFO_FULL               (0x1 << BIT_ADC_FIFO_FULL       )
#define SET_ADC_SAMPLE_RATE             (0x3 << BIT_ADC_SAMPLE_RATE     )
#define SET_ADC_WAIT_CLK_SETTING        (0x1 << BIT_ADC_WAIT_CLK_SETTING)
#define SET_ADC_VALID_MODE              (0x3 << BIT_ADC_VALID_MODE      )
#define SET_ADC_INT_CLEAR               (0x1 << BIT_ADC_INT_CLEAR       )
#define SET_ADC_CLK_RATE                (0x3 << BIT_ADC_CLK_RATE        )

#pragma anon_unions
typedef struct HW_ADC{
	union{
		uint32 cfg;
		struct{
			uint32 MODE:2;
			//ADC����ģʽ
			//����ģʽ��mode==00����ADC����PowerDown״̬;
			//����ģʽ��mode==01����ADCת�����ģʽ�Զ�ת��Ϊ����״̬, �ȴ�MCU������;
			//������ƣ�mode==10����ADCת������жϴ������ȴ�MCU����, MCU������ADC������ʼת����;
			//����ģʽ��mode==11�����ȴ�����ʱ�䣬��ʼת����ת����ɺ󴥷��ж�, �ٵȴ�����ʱ�䣬 ����ת��������;��ע�⡿����ģʽ�ǲ���Read�ź�Ӱ��ģ����ǰ��̶��Ľ���������������ʹMCU��������Ҳ���Լ��Ľ����������������ģʽ�£�MCU������ADC��һֱ���ڵȴ�״̬��;
			uint32 EN:1;
			uint32 CHNL:3;
			//ADC����ͨ��ѡ��                                                               3' b000: ͨ��0;3��b001: ͨ��1;3��b010: ͨ��2;3��b011: ͨ��3;3��b100: ͨ��4;3��b101: ͨ��5;3��b110: ͨ��6;3��b111: ͨ��7
			uint32 FIFO_EMPTY:1;
			//ADC FIFO���ձ�־                                                                             (ADCת��������ݴ�������Ϊ4��FIFO��FIFO�����պ�FIFO_EMPTYΪ1)
			uint32 BUSY:1;
			//Ϊ1ʱADC ����ת������,Ϊ0��ʾת����ɣ����ݶ������λ��1��
			uint32 SAMPLE_RATE:2;
			//����ģʽ�µĲ�����ѡ��;2��b00: adc_clk/36
			// 2��b01: adc_clk/18;2��b10: reserved;2��b11: Reserved;
			uint32 settling:1;
			//ADC ģʽ1��ģʽ2ʱ����д��ADC_MODE(����ADCת��)�󣬵�ADC_CLK��ʼ�ṩ��ģ��ADCģ�飨��ʼת����ǰ��һ�εȴ�ʱ�䣬���ȴ��Ϊ���ɸ�ADC_CLK�����ڣ�
			//setting����ѡ��ȴ�ʱ��ĳ��� : 1���ȴ�8��ADC_CLK     0:�ȴ�4��ADC_CLK
			uint32 valid_mode:2;
			//ADC��power down���빤��ģʽ֮����Чת���Ĵ�����;
			// 2��b00: ��һ��ת��������Ч
			// 2��b01: �ڶ���ת��������Ч       ;
			// 2��b10: ������ת��������Ч       ;
			// 2��b11: ���Ĵ�ת��������Ч       ;;
			uint32 :2;
			uint32 int_clear:1;
			//ADC�ж�����źţ�д1��0.
			uint32 CLK_RATE:3;
			//ADC clock ��Ƶ���趨(���ֵ���ܳ���512K)��;    000: 4��Ƶ;    001: 8��Ƶ;    010:16��Ƶ;    011:32��Ƶ;    100: 64��Ƶ;    101: 128��Ƶ;    110:256��Ƶ;    111:512��Ƶ;;
			uint32 :13;
		};
	};
	union{
		uint32 REG_0x1;
		struct{
			uint32 DAT:10;
			//ADC ���ݣ�10λ��
			uint32 :22;
		};
	};
}HW_ADC;
#define ADC_CLK \
    16000000l
#define ADC_SetupIO(cl) \
	GPIO_SetSF(GPIOD, cl)

#define ADC_OPEN_CLOCK(fr) \
	{\
	SET_BFD(REG_AHB0_ICU_ADCCLKCON,(((ADC_CLK/(fr))<1)?0:((ADC_CLK/(fr))-1)),1,3);\
	}

#define ADC_CLOSE_CLOCK() \
	{\
	SET_BFD(REG_AHB0_ICU_ADCCLKCON,1,0,1);\
	/*BASE_ICU_PTR->ADC_PWD = 1;*/\
	}

#define ADC_OPEN() \
	{\
	SET_BFD(REG_AHB0_ICU_ADCCLKCON,0,0,1);\
	/*BASE_ICU_PTR->ADC_PWD = 0;*/\
	/*BASE_ADC_PTR->EN = 1;*/REG_APB7_ADC_CFG|=BIT(BIT_ADC_EN);\
	}

#define ADC_CLOSE() \
	{\
	/*BASE_ADC_PTR->MODE = ADC_MODE_PD;*/SET_BFD(REG_APB7_ADC_CFG,ADC_MODE_PD,BIT_ADC_MODE,2);\
	ADC_CLOSE_CLOCK();\
	}

#define ADC_MODE_PD \
    0

#define ADC_MODE_Single \
    1

#define ADC_MODE_Soft \
    2

#define ADC_MODE_Continue \
    3
#define ADC_CLKPRES_4 \
    0

#define ADC_CLKPRES_8 \
    1

#define ADC_CLKPRES_16 \
    2

#define ADC_CLKPRES_32 \
    3

#define ADC_CLKPRES_64 \
    4

#define ADC_CLKPRES_128 \
    5

#define ADC_CLKPRES_256 \
    6

#define ADC_CLKPRES_512 \
    7


#define ADC_SETUP(pres,sr,mode,chn,_12bits) \
    {\
    /*BASE_ADC_PTR->cfg*/REG_APB7_ADC_CFG = BFD(mode, 0, 2)|BFD(chn, 3, 3)|BFD(sr, 8, 2)|\
		BFD(3, 11, 2)|BFD(pres, 16, 3);\
    }

#define ADC_SWITCH_CHN(chn) \
    {\
    /*BASE_ADC_PTR->CHNL*//*REG_APB7_ADC_CFG &= _BFD(7,BIT_ADC_CHNL,3);*/\
	/*REG_APB7_ADC_CFG |= BFD(chn,BIT_ADC_CHNL,3);*/\
	SET_BFD(REG_APB7_ADC_CFG,chn,BIT_ADC_CHNL,3);\
    }

#define ADC_INT_SETUP(inte) \
    {\
	if(inte){\
		REG_AHB0_ICU_INT_ENABLE |= BIT(PID_ADC);\
	}else{\
		REG_AHB0_ICU_INT_ENABLE &= _BIT(PID_ADC);\
	}\
    /*BASE_ICU_PTR->adc_int_en = inte;*/\
    }

#define ADC_CHECK_RDY() \
    /*BASE_ADC_PTR->BUSY*/(REG_APB7_ADC_CFG&BIT(BIT_ADC_FIFO_BUSY))

#define ADC_10bitSetup(pres,sr,chn) \
    ADC_SETUP(pres, sr, ADC_MODE_Soft,chn, 0)

#define ADC_CLEAR_INTF() \
    {/*BASE_ADC_PTR->int_clear*/ REG_APB7_ADC_CFG |= BIT(BIT_ADC_INT_CLEAR);}


void ADC_Init(void);
void ADC_Samp(int*buf);
int ADC_GetTotalChn(void);

#endif
