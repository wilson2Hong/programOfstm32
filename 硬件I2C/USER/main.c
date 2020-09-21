#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "stm32f10x.h"
#include "i2c_ee.h"

#define  EEP_Firstpage      0x00
u8 I2c_Buf_Write[256];
u8 I2c_Buf_Read[256];

void I2C_Test(void);

float ADC_ConvertedValueLocal;

extern uint16_t ADCConvertedValue;

int main(void)
{
	
	//float ADC_ConvertedValueLocal;

	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	//LCD_Init();
  Adc_Init();	
 	
	/* I2C �����(AT24C02)ʼ�� */
	I2C_EE_Init();
	
	printf( "\r\n ����һ��I2C����(AT24C02)��д�������� \r\n");
	printf("\r\n ("__DATE__ " - " __TIME__ ") \r\n");
	
	I2C_Test();
	
//	POINT_COLOR=RED;//��������Ϊ��ɫ 
//	LCD_ShowString(60,50,200,16,16,"WarShip STM32");	
//	LCD_ShowString(60,70,200,16,16,"ADC TEST");	
//	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
//	LCD_ShowString(60,110,200,16,16,"2015/1/14");	
//	//��ʾ��ʾ��Ϣ
//	POINT_COLOR=BLUE;//��������Ϊ��ɫ
//	LCD_ShowString(60,130,200,16,16,"ADC_CH0_VAL:");	      
//	LCD_ShowString(60,150,200,16,16,"ADC_CH0_VOL:0.000V");		
	
	while(1)
	{
//		LCD_ShowxNum(156,130,ADCConvertedValue,4,16,0);//��ʾADC��ֵ
//		
//		LCD_ShowxNum(156,150,ADCConvertedValue,1,16,0);//��ʾ��ѹֵ
//		
//		//��ʾ��ѹֵ��С������		
//		LED0=!LED0;
//		delay_ms(250);
		
		
  }	
}



void I2C_Test(void)
{
	u16 i;

	printf("д�������\n\r");
    
	for ( i=0; i<=255; i++ ) //��仺��
  {   
    I2c_Buf_Write[i] = ADCConvertedValue;

    printf("0x%02X ", I2c_Buf_Write[i]);
    if(i%16 == 15)    
        printf("\n\r");    
   }

  //��I2c_Buf_Write��˳�����������д��EERPOM�� 
	I2C_EE_BufferWrite( I2c_Buf_Write, EEP_Firstpage, 256);	 
  
  printf("\n\r����������\n\r");
  //��EEPROM��������˳�򱣳ֵ�I2c_Buf_Read�� 
	I2C_EE_BufferRead(I2c_Buf_Read, EEP_Firstpage, 256); 

  //��I2c_Buf_Read�е�����ͨ�����ڴ�ӡ
	for (i=0; i<256; i++)
	{	
		if(I2c_Buf_Read[i] != I2c_Buf_Write[i])
		{
			printf("0x%02X ", I2c_Buf_Read[i]);
			printf("����:I2C EEPROMд������������ݲ�һ��\n\r");
			return;
		}
    printf("0x%02X ", I2c_Buf_Read[i]);
    if(i%16 == 15)    
        printf("\n\r");
    
	}
  printf("I2C(AT24C02)��д���Գɹ�\n\r");
}
