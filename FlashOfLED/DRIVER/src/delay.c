#include "stm32f10x.h"
void delay(uint32_t timers)
{
	uint16_t i,j;
	for(i=0;i<timers;i++)
	{
		for(j=0;j<0xffff;j++)
		{}
	}
}
