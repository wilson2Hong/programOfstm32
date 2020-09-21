#ifndef __PCF8591_H__
#define __PCF8591_H__

#include "stm32f10x.h"
#include "iic.h"  

#define pcf8591_read  0x91              //PCF8591¶Á¿ØÖÆ×Ö
#define pcf8591_write 0x90              //PCF8591Ð´¿ØÖÆ×Ö 
	
void PCF8591_Init(void);				  
void pcf8591_ad_write(u8 c);
u8 pcf8591_ad_read(void);
void pcf8591_da_write(u8 dat);


#endif
















