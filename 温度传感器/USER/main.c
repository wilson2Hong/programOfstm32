#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "adc.h"
#include "dma.h"
#include "stm32f10x.h"
#include "beep.h"
#include "math.h"

#define D0 PBout(2)
void Rain_Do_GPIO_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

extern  uint16_t ADCConvertedValue;

int main(void)
{
	float ADC_ConvertedValueLocal;
	double Vr,Rt,tmp;
	u16 temp;

	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();			 	
 	Adc_Init();		  		//ADC��ʼ��
	BEEP_Init();
	
	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,200,16,16,"WarShip STM32");	
	LCD_ShowString(60,70,200,16,16,"ADC TEST");	
	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,200,16,16,"2015/1/14");	
	//��ʾ��ʾ��Ϣ
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(60,130,200,16,16,"ADC_CH0_VAL:");	      
	LCD_ShowString(60,150,200,16,16,"ADC_CH0_VOL:0.000V");		
	
	while(1)
	{
		LCD_ShowxNum(156,130,ADCConvertedValue,4,16,0);//��ʾADC��ֵ
		printf("%d\n",ADCConvertedValue);
		
		/*��LCD������ʾ����Ӧ�¶ȵ�ģ���ѹ*/
//				ADC_ConvertedValueLocal=(float)ADCConvertedValue*(5.0/4096);	
//				temp=ADC_ConvertedValueLocal;
//				LCD_ShowxNum(156,150,temp,1,16,0);//��ʾ�������ֵ�ѹֵ
//				//��ʾ��ѹֵ��С������
//				ADC_ConvertedValueLocal-=temp;
//				ADC_ConvertedValueLocal*=1000;		
//				LCD_ShowxNum(172,150,ADC_ConvertedValueLocal,3,16,0X80);
		
		/*�ڴ��������ϴ�ӡ����ʱ���¶�*/
				Vr=ADCConvertedValue*(5.0/4095);
		    printf("Current Voltage : %1f\n",Vr);			
				Rt=10000*Vr/(5-Vr);
				tmp = 1/(((log(Rt/10000))/3950)+(1/(273.15+25)));
				tmp=tmp-273.15;
				printf("Current temperture : %1f\n",tmp);
			
		
		
		delay_ms(500);
  }
	
}
