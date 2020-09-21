/******************** (C) COPYRIGHT 2013 CEPARK�๦�ܿ���ѧϰ��********************
 * �ļ���  ��main.c
 * ����    ��CPU���ϵض�ȡPCF8591ת�����ADֵ�����������ʾ��LCD1602�ϣ���λΪmv��ͨ
 			 �����ڿɵ����裬LCD1602�Ͻ���ʾ��ͬ�ĵ�ѹֵ��
 * ʵ��ƽ̨��CEPARK�๦�ܿ���ѧϰ��
 * ��汾  ��ST3.5.0
 * Ӳ�����ӣ�----------------------
 * ��Ƭ��IO | PA8  - JP31 - RS     | LCD1602ģ��
 *          | PA9  - JP31 - RW     |
 *          | PA10 - JP31 - EN     |
 *           ----------------------
 * Ӳ�����ӣ�----------------------
 * ��Ƭ��IO |  PA0 - JP33 - D0	   | LCD1602ģ��
						|  PA1 - JP33 - D1	   |
						|  PA2 - JP33 - D2	   |
						|  PA3 - JP33 - D3	   |
						|  PA4 - JP33 - D4	   |
						|  PA5 - JP33 - D5	   |
						|  PA6 - JP33 - D6	   |
						|  PA7 - JP33 - D7	   |
 *           ----------------------
 * Ӳ�����ӣ�------------------------
 * ��Ƭ��IO |  PB10 - JP68 - SCL	   | AD/DAת��ģ��
						|  PB11 - JP68 - SDA	   |
 *           ------------------------
 * Ӳ�����ӣ�JP66�̽ӣ�����AD��ʾ��JP63��I0�̽ӣ����£�������RT2��LCD����ʾ��ͬ��ֵ
 * Ӳ�����ӣ�J3�϶����ӵ����İ��J7��3.3V��
**********************************************************************************/

#include "stm32f10x.h"
#include "PCF8591.h"
#include "delay.h"
#include "iic.h"
#include "lcd1602.h"


/* 
 * ��������main
 * ����  : ������
 * ����  ����
 * ���  : ��
 */
int main(void)
{  			    
	u8 pcf8591_adchannel=0;
	u8 ad_temp=0,ad_result1,ad_result2,ad_result3,ad_result4;
	u16 ad_result=0;
	
	/* ����ϵͳʱ��Ϊ72M */
  	SystemInit();
	
  	LCD1602_GPIO_Init();
	
	LCD1602_Init();
	
  	PCF8591_Init();			//IIC��ʼ�� 

	LCD1602_MoveToPosition(0,0);                 
  	LCD1602_DisplayString("PCF8591 AD TEST");  
  	 
  	LCD1602_MoveToPosition(1,0);
	LCD1602_DisplayString("AD Result:    mv");

	
										   
	while(1)
	{
		pcf8591_ad_write(0x40+pcf8591_adchannel);
    	ad_temp=pcf8591_ad_read();
    	ad_result=(ad_temp*5000)/256;
    	ad_result1=ad_result/1000;
    	ad_result2=ad_result%1000/100;
    	ad_result3=ad_result%100/10;
    	ad_result4=ad_result%10;
    	
    	LCD1602_DisplayOneCharOnAddr(1,10,ad_result1+0x30);
    	LCD1602_DisplayOneCharOnAddr(1,11,ad_result2+0x30);
    	LCD1602_DisplayOneCharOnAddr(1,12,ad_result3+0x30);
    	LCD1602_DisplayOneCharOnAddr(1,13,ad_result4+0x30);	
    	
	}
}




/******************* (C) COPYRIGHT 2013 CEPARK�๦�ܿ���ѧϰ��*****END OF FILE****/
