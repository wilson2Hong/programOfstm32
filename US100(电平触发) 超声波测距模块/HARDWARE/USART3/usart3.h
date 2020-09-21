#ifndef __USART_H
#define __USART_H
#include "stdio.h"
#include "sys.h"
#define u8 int8_t
#define u16 int16_t
#define u32 int32_t

void uart2_init();

void UART2_send_byte(char data);

#endif
