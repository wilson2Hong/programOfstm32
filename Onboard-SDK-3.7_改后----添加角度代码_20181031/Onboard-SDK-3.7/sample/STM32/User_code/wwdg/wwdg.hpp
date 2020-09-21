#ifndef _WWDG_H
#define _WWDG_H
#include "sys.h"
#include "stm32f4xx_wwdg.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
void WWDG_Init(u8 tr,u8 wr,u32 fprer);
void WWDG_IRQHandler(void);
#ifdef __cplusplus
}
#endif //__cplusplus
#endif
