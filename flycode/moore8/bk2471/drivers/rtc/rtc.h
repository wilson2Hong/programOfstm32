#ifndef _RTC_H_
#define _RTC_H_
#include "..\..\includes\types.h"
#define	BASE_RTC_PTR	\
		((HW_RTC*)0x00f00600)
#define FREQ_RTC_CLK	32000
//=====================================================================================
//RTC
//=====================================================================================
#define REG_APB6_RTC_CFG                (*((volatile unsigned long *)   (APB_RTC_BASE + 0x00) ))
#define BIT_RTC_ENABLE                  0
#define BIT_RTC_CLEAR                   1
#define BIT_RTC_ALARM_EN                2
#define BIT_RTC_ALARM_MODE              3
#define SET_RTC_ENABLE                  (0x1 << BIT_RTC_ENABLE     )
#define SET_RTC_CLEAR                   (0x1 << BIT_RTC_CLEAR      )
#define SET_RTC_ALARM_EN                (0x1 << BIT_RTC_ALARM_EN   )
#define SET_RTC_ALARM_MODE              (0x1 << BIT_RTC_ALARM_MODE )

#define REG_APB6_RTC_UNIT               (*((volatile unsigned long *)   (APB_RTC_BASE + 0x04) ))
#define BIT_RTC_DIV                     0
#define BIT_RTC_MSUNIT                  2
#define BIT_RTC_SUNIT                   8
#define SET_RTC_DIV                     (0x3    << BIT_RTC_DIV   )
#define SET_RTC_MSUNIT                  (0x3F   << BIT_RTC_MSUNIT)
#define SET_RTC_SUNIT                   (0xFFFF << BIT_RTC_SUNIT )

#define REG_APB6_RTC_SET                (*((volatile unsigned long *)   (APB_RTC_BASE + 0x08) ))
#define BIT_RTC_SECOND                  0
#define BIT_RTC_MINUTE                  6
#define BIT_RTC_HOUR                    12
#define BIT_RTC_WEEK                    17
#define SET_RTC_SECOND                  (0x3F << BIT_RTC_SECOND )
#define SET_RTC_MINUTE                  (0x3F << BIT_RTC_MINUTE )
#define SET_RTC_HOUR                    (0x1F << BIT_RTC_HOUR   )
#define SET_RTC_WEEK                    (0x7  << BIT_RTC_WEEK   )

#define REG_APB6_RTC_ALM_TIME           (*((volatile unsigned long *)   (APB_RTC_BASE + 0x0C) ))
#define BIT_RTC_ALARM_SECOND            0
#define BIT_RTC_ALARM_MINUTE            6
#define BIT_RTC_ALARM_HOUR              12
#define BIT_RTC_ALARM_MILLISEC          17
#define SET_RTC_ALARM_SECOND            (0x3F  << BIT_RTC_ALARM_SECOND   )
#define SET_RTC_ALARM_MINUTE            (0x3F  << BIT_RTC_ALARM_MINUTE   )
#define SET_RTC_ALARM_HOUR              (0x1F  << BIT_RTC_ALARM_HOUR     )
#define SET_RTC_ALARM_MILLISEC          (0x3FF << BIT_RTC_ALARM_MILLISEC )

#define REG_APB6_RTC_ALM_FLAG           (*((volatile unsigned long *)   (APB_RTC_BASE + 0x10) ))

typedef struct HW_RTC{
	union{
		uint32 REG_0x0;
		struct{
			uint32 RTC_ENABLE:1;
			//RTC enable (1) or disable (0);When it is disabled, all registers hold their previous value (start work when =1);
			uint32 RTC_CLEAR:1;
			//Reset all status register and counter to 0
			uint32 RTC_ALARM_EN:1;
			//Alarm enable
			uint32 RTC_ALARM_MODE:1;
			//0: Clock mode, alarming only when both second:minute:hour counters is equal the set alarm time;1: Millisecond mode, alarming as long as the millseond counter is equal to the set millsecond time;
			uint32 :28;
		};
	};
	union{
		uint32 REG_0x1;
		struct{
			uint32 RTC_DIV:2;
			//RTC counter clock divider;RT counter clock frequency = rtc_clk/rtc_div, where rtc_div is defined as follows.;00: 1;01: 2;10: 4;11: 16;
			uint32 RTC_MSUNIT:6;
			//Number of RTC counter clock cycles for one millisecond;For example, rtc_clk = 16m /500 = 32 kHz;and RTC_DIV = 0, then RTC_MSUNIT = 32-1;
			uint32 RTC_SUNIT:16;
			//Number of RTC counter clock cycles for one second, the setting value is same as RTC_MSUNIT
			uint32 :8;
		};
	};
	union{
		uint32 REG_0x2;
		struct{
			uint32 RTC_S:6;
			//The second counter, 0 ~ 59;Write this register will set the current value of the counter;
			uint32 RTC_M:6;
			//The minute counter, 0 ~ 59;Write this register will set the current value of the counter;
			uint32 RTC_H:5;
			//The hour counter, 0 ~ 23;Write this register will set the current value of the counter;
			uint32 RTC_W:3;
			//The weekday counter, 1 ~ 7;Write this register will set the current value of the counter;
			uint32 :12;
		};
	};
	union{
		uint32 REG_0x3;
		struct{
			uint32 RTC_ALARM_S:6;
			//Second of Alarm time
			uint32 RTC_ALARM_M:6;
			//Minute of Alarm time
			uint32 RTC_ALARM_H:5;
			//Hour of Alarm time
			uint32 RTC_ALARM_MS:10;
			//Millsecond of Alarm time
			uint32 :5;
		};
	};
	union{
		uint32 REG_0x4;
		struct{
			uint32 RTC_ALARM_FLAG:1;
			//RTC alarm interrupt flag. ;Write 1 to this bit will clear it.
			uint32 :31;
		};
	};
}HW_RTC;

#define RTC_OPEN_CLOCK(pn,tar_freq) \
	{\
	/*pn:timer±àºÅ,0-1 srcsel:rtcÊ±ÖÓÔ´Ñ¡Ôñ */\
	BASE_ICU_PTR->RTC_PWD = 0;\
	BASE_RTC_PTR->pwm[4].pwm_clk |= BFD(srcsel,9,1);\
	}

#define RTC_Setup(pn,period) \
	{\
		BASE_RTC_PTR->tmr[pn].timeto=(period);
	}

#define RTC_SetupInt(pn,inte) \
	{\
	/*pn:timer±àºÅ,0-1 inte:1=ÖÐ¶ÏÔÊÐí */\
		if(inte)BASE_RTC_PTR->cfg |= BIT(1+2*(pn));\
		else BASE_RTC_PTR->cfg &= _BIT(1+2*(pn));\
	}

#define RTC_Open(pn) \
	{\
	/*pn:timer±àºÅ,0-5*/\
		BASE_RTC_PTR->cfg |= BIT(2*(pn));\
	}

#define RTC_CLOSE_CLOCK(pn) \
	{\
		BASE_ICU_PTR->pwm[4].pwm_clk |= (BIT(8));\
	}

#define RTC_CLOSE(pn) \
	{\
	/*pn:timer±àºÅ,0-1*/\
		BASE_RTC_PTR->cfg &= _BIT(2*(pn));\
		PWM_CLOSE_CLOCK(pn);\
	}

#endif