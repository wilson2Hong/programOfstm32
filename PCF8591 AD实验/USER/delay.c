/******************** (C) COPYRIGHT 2013 CEPARK�๦�ܿ���ѧϰ��********************
 * �ļ���  ��delay.c
 * ����    ��delay Ӧ�ú�����
 *          
 * ʵ��ƽ̨��CEPARK�๦�ܿ���ѧϰ��
																				 
**********************************************************************************/

#include "delay.h"

//΢��
void delay_us(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=10;   
      while(i--) ;    
   }
}


//����
void delay_ms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=12000;  
      while(i--) ;    
   }
}

//��ʱ����
void delay(u16 m)
{
	while(m--);
}


/******************* (C) COPYRIGHT 2013 CEPARK�๦�ܿ���ѧϰ��*****END OF FILE****/
