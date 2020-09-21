#ifndef _WDT_H_
#define _WDT_H_
#include "..\..\includes\types.h"
#include "..\icu\icu.h"

#define	BASE_WDT_PTR	\
		((HW_WDT*)0x00f00000)

#define REG_APB0_WDT_CFG                (*((volatile unsigned long *)APB_WDT_BASE))

#pragma anon_unions
typedef struct HW_WDT{
	union{
		uint32 REG_0x0;
		struct{
			uint32 PERIOD:16;
			//Watch Dog Timer周期;0x0001：1个wd_clk时钟周期，大约0.512 ms;0xFFFF：最大周期，大约33.5秒;
			uint32 KEY:8;
			//Watch Dog Key
			uint32 :8;
		};
	};
}HW_WDT;

#define WDT_OPEN() \
    {BASE_ICU_PTR->REG_0x7=0;}

#define WDT_FEED() \
    {BASE_WDT_PTR->KEY=0x00;}

#define WDT_SET_TO(tmro) \
    {BASE_WDT_PTR->PERIOD = (tmro);}

#define WDT_MAKE_CTRL(key,cnt)	\
	(BFD(cnt,0,16)|BFD(key,16,8))

#define SW_RESET(cnt)	\
	{\
	WDT_OPEN();\
	BASE_WDT_PTR->REG_0x0=WDT_MAKE_CTRL(0,cnt);\
	BASE_WDT_PTR->REG_0x0=WDT_MAKE_CTRL(0x5a,cnt);\
	BASE_WDT_PTR->REG_0x0=WDT_MAKE_CTRL(0xa5,cnt);\
	}

#endif
