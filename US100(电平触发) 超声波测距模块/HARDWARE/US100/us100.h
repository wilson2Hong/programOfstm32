#ifndef __US100_H
#define __US100_H

#include "sys.h"

#define uint unsigned int 
#define TRIG_Send  PBout(3)
#define ECHO_Recv  PBin(4)

void us100_Init(void);

float Senor_Using(void);

void NVIC_Config(void);

#endif
