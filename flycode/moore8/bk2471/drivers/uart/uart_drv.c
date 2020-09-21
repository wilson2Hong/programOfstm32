//======================================================
// File Name:     Uart_API.c
// Author:
// Created Date:  @2015-05-18
// Description:   Project BK2471 - Test Firmware for Massive Production
//                UART (Host-Controller-Interface) transaction protocol
//                Source from BK3260 test firmware: uart.c
//======================================================

#include <stdio.h>
#include <string.h>
#include "uart.h"

#define RX_FIFO_MAX_COUNT           0X100
#define TX_FIFO_MAX_COUNT           0X100

// Global variables used in UART API
uint8 uart_rx_buf[RX_FIFO_MAX_COUNT]={0};
uint8 uart_tx_buf[TX_FIFO_MAX_COUNT]={0};
volatile uint8   uart_rx_done = 0;
volatile uint8   uart_tx_done = 0;
volatile uint32 uart_rx_index;
uint32 uart_rx_length;

uint8 txInput;
uint8 txCur;
uint32 txTotalLen;
uint32 txLen;

uint8 rxAligned;
uint8 rxUL;
uint8 rxInput;
uint8 rxCur;
uint32 rxTotalLen;
uint32 rxLen;

struct __FILE {
	int handle;                 // Add whatever you need here
};
FILE __stdout;
FILE __stdin;

void uart_write_fifo(void);

void Beken_Uart_Tx_Init(void){
	uart_tx_done=1;//tx is done now
	txLen=0;//tx已发送字节计数器
	txTotalLen=0;//tx目标字节总长度
	txCur=0;//txbuf输出指针
	txInput=0;//txbuf写入指针
}

void Beken_Uart_Rx_Init(){
	rxLen=0;//rx已解析字节计数器
	rxTotalLen=0;//rx已接收字节总长度
	rxCur=0;//rxbuf输出指针
	rxInput=0;//rxbuf写入指针
}

void Beken_UART_Initial(int dr)
{
	HW_UART*uart=BASE_UART_PTR;
	UART_SetupIOL(0);

	uart->uart_conf=UART_Setup(0, dr, 8, 1, 0, 0);
	uart->fifo_conf=UART_SetupTRFifo(1, 16);
	UART_OPEN_CLOCK();
	//打开UART TX、RX（=UART_Open(1, 1)）
	uart->uart_conf |= (BIT(0)|BIT(1));
	//
	UART_SetupInt();
	memset(uart_rx_buf,0,sizeof(uart_rx_buf));
	Beken_Uart_Tx_Init();
	Beken_Uart_Rx_Init();
}

void Beken_Uart_Read_fifo(HW_UART *uart)
{
	int j;
	j=0;
	while(uart->FIFO_RD_READY)
	{
		uart_rx_buf[rxInput++] = uart->UART_RX_FIFO_DOUT;
		j++;
	}
	rxTotalLen+=j;
}



//----------------------------------------------
// UART Interrupt Service Rountine. Source from BK3260.
//----------------------------------------------
void Uart_isr(void)
{
	uint8  uart_int_status ;

	HW_UART *uart=BASE_UART_PTR;
	uart_int_status = uart->int_flag ;
	if(uart_int_status & (RX_FIFO_NEED_READ_FLAG|UART_RX_STOP_END_FLAG)){
		uart->int_flag = uart_int_status;
		Beken_Uart_Read_fifo(uart);
	}
	if(uart_int_status & (UART_TX_STOP_END_FLAG/*|TX_FIFO_NEED_WRITE_FLAG*/))
	{
		uart->int_flag = uart_int_status;
		if(txLen==txTotalLen){
			uart_tx_done=1;
		}else
			uart_write_fifo();
	}

	uart->int_flag = uart_int_status;
}

//----------------------------------------------
// UART Tx/Rx character driver. Source from BK3260.
//----------------------------------------------
void uart_tx_trigger(){
	if(uart_tx_done){
		uart_tx_done=0;
		uart_write_fifo();
	}
}
void uart_send_byte(u8 data) {
	uart_send(&data,1);
}
int uart_TX_end(){
	return(uart_tx_done);
}
void uart_wait_for_txEnd(){
	while(uart_tx_done==0);
}

u8 uart_receive_byte(void) {
	HW_UART *uart=BASE_UART_PTR;
	while(uart->FIFO_RD_READY == 0);
	return uart->UART_RX_FIFO_DOUT;
}

void uart_write_fifo(){
	uint32 i,j;
	j=8;
	if((txTotalLen-txLen)<j){
		j=txTotalLen-txLen;
	}
	txLen+=j;
	HW_UART *uart=BASE_UART_PTR;
	for(i=0;i<j;i++){
		uart->UART_TX_FIFO_DIN = uart_tx_buf[txCur++];
	}
}

void uart_send( u8 *buff, int len) {
	uint8 i;
	for(i=0;i<len;i++){
		uart_tx_buf[txInput++]=*buff++;
	}
	txTotalLen+=len;
	uart_tx_trigger();
}

void uart_puts( char *buff) {
	uint8 j;	////i,
	j=strlen(buff);
	uart_send((u8*)buff,j);
}


void itoa_hex(uint32 i,char *buf){
	int j;
	uint32 t;
	for(j=0;j<8;j++){
		t=(i>>((7-j)*4))&0x0f;
		if(t<=9)buf[j]='0'+t;
		else buf[j]='A'+(t-10);
	}
}
const uint32 tbl10Pwr[]={
	1,				//10^0
	10,				//10^1
	100,			//10^2
	1000,			//10^3
	10000,			//10^4
	100000,			//10^5
	1000000,		//10^6
	10000000,		//10^7
	100000000,		//10^8
	1000000000,		//10^9
};

void itoa_dec(uint32 i,char *buf){
	int j,k;
////	uint32 t;
	int f=0;
	k=9;
	j=0;
	while(1){
		if(i<tbl10Pwr[k]){
			if(f==1){
				buf[j++]='0';
			}
			//k--;
		}else{
			buf[j++]=i/tbl10Pwr[k]+'0';
			if(f==0){
				f=1;
			}
			i%=tbl10Pwr[k];
			//k--;
		}
		k--;
		if(k<1){
			buf[j]='0'+i;
			break;
		}
	}
}

void itoa_dec_s(int32 i,char *buf){
	if(i<0){
		itoa_dec(-i,&buf[1]);
	}else{
		itoa_dec(i,buf);
	}
}

void x_putc(u8 dat){
	HW_UART *uart=BASE_UART_PTR;
 	while(uart->FIFO_WR_READY == 0);
	uart->UART_TX_FIFO_DIN =dat;
}

void x_puts(u8 *dat,int len){
	while(len--)
		x_putc(*dat++);
}
void x_puts_all(){
	x_puts(uart_tx_buf,txTotalLen);
	print_si_dec(txLen);
	print_newline();
	print_si_dec(txTotalLen);
	print_newline();
	print_si_dec(txInput);
	print_newline();
	print_si_dec(txCur);

}
void print_i_hex(uint32 i){
	char buf[12]={0};
	itoa_hex(i,buf);
	uart_puts(buf);
}

void print_ui_dec(uint32 i){
	char buf[12]={0};
	itoa_dec(i,buf);
	uart_puts(buf);
}

void print_si_dec(int32 i){
	char buf[12]={0};
	itoa_dec_s(i,buf);
	uart_puts(buf);
}

void print_newline(){
	uart_puts("\r\n");
}

void print_i_hex_c(uint32 i,int32 c){
	char buf[12]={0};
	itoa_hex(i,buf);
	uart_puts(&buf[8-c]);
}

/*----------------------------------------------------------------------------
fputc
*----------------------------------------------------------------------------*/
int fputc(int ch, FILE *f) {
	uart_send_byte(ch);
	return ch;
}

/*----------------------------------------------------------------------------
fgetc
*----------------------------------------------------------------------------*/
int fgetc(FILE *f) {
	int ch;

	do {
		ch = uart_receive_byte ();
	}
	while (ch == -1);
	uart_send_byte(ch);
	return (ch);
}
