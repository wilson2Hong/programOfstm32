#include "us100.h"
#include "usart.h"
#include "sys.h"
#include "sys.h"
#include "delay.h"

int main(void)
{
  float tmp=0;
  delay_init();
	us100_Init();
	//NVIC_Config();
	uart_init(9600);	 //���ڳ�ʼ��Ϊ115200
	while(1)
	{
		tmp=Senor_Using();
		printf("����õľ���Ϊ:%f\n" ,tmp);//��λ����
	
	}
}


