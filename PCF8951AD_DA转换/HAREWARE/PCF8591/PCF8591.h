#ifndef __PCF8591_H
#define __PCF8591_H

#include "stm32f10x.h"
#include "myiic.h"

#define pcf8591_read 0x91     //pcf8591��������  �����ΪΪ1��ʾ��һ���ֽڴ������϶�
#define pcf8591_write 0x90     //pcf8591д������  ���һλΪ0��ʾ��һ���ֽ���������д

void pcf8591_Init(void);                
void pcf8591_addr_write(u8 addr);       
u8 pcf8591_addr_read(void);
void pcf8591_data_write(u8 data);
u8 pcf8591_data_read(void);

#endif __PCF8591_H
