#ifndef __USART2_H
#define __USART2_H

#include "sys.h"
#include "stdio.h"

#define u8 int8_t
#define u16 int16_t
#define u32 int32_t

void uart2_init(u32 bound);

void USART2_send_byte(char data);

#endif