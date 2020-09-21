#ifndef __LED__H
#define __LED__H
#include "sys.h"
#define LED0 PBout(5)
#define LED1 PEout(5)

void LED_Init(void);

#endif
