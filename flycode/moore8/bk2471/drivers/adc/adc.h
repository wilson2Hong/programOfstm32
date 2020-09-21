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
			//ADC操作模式
			//休眠模式（mode==00）：ADC处于PowerDown状态;
			//单步模式（mode==01）：ADC转换完后，模式自动转变为休眠状态, 等待MCU来读。;
			//软件控制（mode==10）：ADC转换完后，中断触发，等待MCU来读, MCU读过后，ADC继续开始转换。;
			//连续模式（mode==11）：等待采样时间，开始转换，转换完成后触发中断, 再等待采样时间， 继续转换，……;【注意】连续模式是不受Read信号影响的，总是按固定的节拍来做采样。即使MCU不读，它也按自己的节拍来采样。而软件模式下，MCU不读，ADC就一直处于等待状态。;
			uint32 EN:1;
			uint32 CHNL:3;
			//ADC输入通道选择                                                               3' b000: 通道0;3’b001: 通道1;3’b010: 通道2;3’b011: 通道3;3’b100: 通道4;3’b101: 通道5;3’b110: 通道6;3’b111: 通道7
			uint32 FIFO_EMPTY:1;
			//ADC FIFO读空标志                                                                             (ADC转化后的数据存放在深度为4的FIFO，FIFO被读空后，FIFO_EMPTY为1)
			uint32 BUSY:1;
			//为1时ADC 正在转化数据,为0表示转换完成，数据读出后此位置1。
			uint32 SAMPLE_RATE:2;
			//连续模式下的采样率选择;2’b00: adc_clk/36
			// 2’b01: adc_clk/18;2’b10: reserved;2’b11: Reserved;
			uint32 settling:1;
			//ADC 模式1和模式2时，从写好ADC_MODE(启动ADC转化)后，到ADC_CLK开始提供给模拟ADC模块（开始转化）前有一段等待时间，长度大概为若干个ADC_CLK的周期，
			//setting用来选择等待时间的长短 : 1：等待8个ADC_CLK     0:等待4个ADC_CLK
			uint32 valid_mode:2;
			//ADC从power down进入工作模式之后，有效转换的次数。;
			// 2’b00: 第一次转换数据有效
			// 2’b01: 第二次转换数据有效       ;
			// 2’b10: 第三次转换数据有效       ;
			// 2’b11: 第四次转换数据有效       ;;
			uint32 :2;
			uint32 int_clear:1;
			//ADC中断清除信号，写1清0.
			uint32 CLK_RATE:3;
			//ADC clock 分频比设定(最大值不能超过512K)：;    000: 4分频;    001: 8分频;    010:16分频;    011:32分频;    100: 64分频;    101: 128分频;    110:256分频;    111:512分频;;
			uint32 :13;
		};
	};
	union{
		uint32 REG_0x1;
		struct{
			uint32 DAT:10;
			//ADC 数据（10位）
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
