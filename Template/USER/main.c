#include "stm32f4xx.h"

void delay(int cnt);
int main()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_pp;
	GPIO_InitStructure.GPIO_Speed=GPIO_GPIO_Speed_100MHZ;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	while(1)
 {
	 *(uint32_t*)(0x40020018)=0xFFFF;
	 GPIO_SetBits(GPIOB,GPIO_Pin_8);//USER_LEDÃð
	 delay(1000);
	 GPIO_ResetBits(GPIOB,GPIO_Pin_8);//USER_LEDÁÁ
	 delay(1000);
 }
}
void delay(int cnt)
{
	int i,j;
	for(i=0;i<cnt;i++)
  {
		for(j=0;j<0xff;j++)
		{}
	}
}
