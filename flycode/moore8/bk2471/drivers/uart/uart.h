#ifndef _UART_H_
#define _UART_H_
#include "..\..\includes\types.h"
#include "..\gpio\gpio.h"
#include "..\icu\icu.h"

#define	BASE_UART_PTR	\
		((HW_UART*)0x00f00300)
#pragma anon_unions
#pragma pack(4)
typedef struct HW_UART{
	union{
		uint32 uart_conf;
		struct{
			uint32 UART_TX_ENABLE:1;
			//UART TX Enable,  1:enable,  0:disable
			uint32 UART_RX_ENABLE:1;
			//UART RX Enable,  1:enable,  0:disable
			uint32 UART_IRDA:1;
			//0:UART Frame Mode, 1:IRDA Mode
			uint32 UART_LEN:2;
			//UART Data Length, 0:5 bit, 1:6 bit, 2:7 bit, 3:8 bit
			uint32 UART_PAR_EN:1;
			//Parity Check enable, 1:enable, 0:disable
			uint32 UART_PAR_MODE:1;
			//Parity Check Mode,  1:Odd,  0:Even
			uint32 UART_STOP_LEN:1;
			//Min STOP Space,  0:1 bit, 1:2 bits
			uint32 UART_CLK_DIVID:13;
			//UART baud rate dev = UART_CLK / baud rate (MUST >=4)
			uint32 :11;
		};
	};
	union{
		uint32 fifo_conf;
		struct{
			uint32 TX_FIFO_THRESHOLD:8;
			//TX Fifo threshold, when data left less than the value, genreate Tx Int
			uint32 RX_FIFO_THRESHOLD:8;
			//RX Fifo threshold, when data more than the value, genreate Rx Int
			uint32 RX_STOP_DETECT_TIME:2;
			//Timeout for the last byte
			uint32 :14;
		};
	};
	union{
		uint32 fifo_status;
		struct{
			uint32 TX_FIFO_COUNT:8;
			//Tx Fifo count
			uint32 RX_FIFO_COUNT:8;
			//Rx Fifo count
			uint32 TX_FIFO_FULL:1;
			//Tx Fifo full flag
			uint32 TX_FIFO_EMPTY:1;
			//Tx Fifo empty flag
			uint32 RX_FIFO_FULL:1;
			//Rx Fifo full flag
			uint32 RX_FIFO_EMPTY:1;
			//Rx Fifo empty flag
			uint32 FIFO_WR_READY:1;
			//Tx Fifo can be write flag
			uint32 FIFO_RD_READY:1;
			//Rx Fifo can be read flag
			uint32 :10;
		};
	};
	union{
		uint32 fifo_port;
		struct{
			uint32 UART_TX_FIFO_DIN:8;
			//UART Tx Fifo data input
			uint32 UART_RX_FIFO_DOUT:8;
			//UART Rx Fifo data output
			uint32 :16;
		};
	};
	union{
		uint32 int_en;
		struct{
			uint32 TX_FIFO_NEED_WRITE_MASK:1;
			//�ж�ʹ��  0���������ж� 1�������ж�
			uint32 RX_FIFO_NEED_READ_MASK:1;
			//�ж�ʹ��  0���������ж� 1�������ж�
			uint32 RX_FIFO_OVER_FLOW_MASK:1;
			//�ж�ʹ��  0���������ж� 1�������ж�
			uint32 UART_RX_PARITY_ERR_MASK:1;
			//�ж�ʹ��  0���������ж� 1�������ж�
			uint32 UART_RX_STOP_ERR_MASK:1;
			//�ж�ʹ��  0���������ж� 1�������ж�
			uint32 UART_TX_STOP_END_MASK:1;
			//�ж�ʹ��  0���������ж� 1�������ж�
			uint32 UART_RX_STOP_END_MASK:1;
			//�ж�ʹ��  0���������ж� 1�������ж�
			uint32 UART_RXD_WAKEUP_MASK:1;
			//�ж�ʹ��  0���������ж� 1�������ж�
			uint32 :24;
		};
	};
	union{
		uint32 int_flag;
		struct{
			uint32 TX_FIFO_NEED_WRITE:1;
			//����FIFO��Ҫд�ж�(��������CPU)��д���ݳ������޺��Զ�����
			uint32 RX_FIFO_NEED_READ:1;
			//����FIFO��Ҫ���ж�(��������CPU)�������ݵ������޺��Զ�����
			uint32 RX_FIFO_OVER_FLOW:1;
			//���������־(��������CPU)��0����ȷ 1������ д1����
			uint32 UART_RX_PARITY_ERROR:1;
			//��żУ�����(��������CPU)��0����ȷ 1������ д1����
			uint32 UART_RX_STOP_ERROR:1;
			//STOP bit����(��������CPU)��0����ȷ 1������ д1����
			uint32 UART_TX_STOP_END:1;
			//UARTȫ���������ݽ����ж�(��������CPU) 1�����ͽ��� д1����
			uint32 UART_RX_STOP_END:1;
			//UART����ȫ���������жϣ���������CPU�� 1�����ܽ��� д1����
			uint32 UART_RXD_WAKEUP:1;
			//UART�����ж�(��������CPU) 1����⵽���� д1����
			uint32 :24;
		};
	};
	union{
		uint32 flow_conf;
		struct{
			uint32 FLOW_CTL_LOW_CNT:8;
			//��UART RX_FIFO_COUNT <= FLOW_CTL_LOW_CNT,  CTS ������һ����ζ��UART�������Զ�˷��������ݡ�
			uint32 FLOW_CTL_HIGH_CNT:8;
			//��UART RX_FIFO_COUNT >= FLOW_CTL_HIGH_CNT,  CTS �������㣬��ζ��UART��ֹ����Զ�˷��������ݡ�
			uint32 FLOW_CONTROL_ENA:1;
			//UART CTS/RTS  ����ʹ�ܣ� 1��enable��0��disable
			uint32 RTS_POLARITY_SEL:1;
			//RTS ����ѡ��0��High ����Low��ֹ 1��Low ���� High��ֹ
			uint32 CTS_POLARITY_SEL:1;
			//CTS ����ѡ��0��High ����Low��ֹ 1��Low ���� High��ֹ
			uint32 :13;
		};
	};
	union{
		uint32 wake_conf;
		struct{
			uint32 UART_WAKE_COUNT:10;
			//UART RXD/TXD ���ѵ͵�ƽ�����ĳ��ȣ�32K��ʱ�Ӽ�����
			uint32 UART_TXD_WAIT_CNT:10;
			//UART TXD ���Ѻ���Ҫ�ȴ���ʱ�䣬 Ȼ��ʹ��UART�����ݷ���
			uint32 UART_RXD_WAKE_EN:1;
			//UART RXD ���ѹ���ʹ�ܣ� 1��enable�� 0��Disable
			uint32 UART_TXD_WAKE_EN:1;
			//UART TXD ���ѹ���ʹ�ܣ� 1��enable�� 0��Disable
			uint32 RXD_NEGEDGE_WAKE_EN:1;
			//UART RXD �½��ػ���ʹ�ܣ�1��enable�� 0��Disable
			uint32 :9;
		};
	};
}HW_UART;
#pragma pack(1)
#define UART_CLK            16000000

//// UART INT flag
#define TX_FIFO_NEED_WRITE_FLAG     BIT(0)
#define RX_FIFO_NEED_READ_FLAG      BIT(1)
#define RX_FIFO_OVER_FLOW_FLAG      BIT(2)
#define UART_RX_PARITY_ERR_FLAG     BIT(3)
#define UART_RX_STOP_ERR_FLAG       BIT(4)
#define UART_TX_STOP_END_FLAG       BIT(5)
#define UART_RX_STOP_END_FLAG       BIT(6)
#define UART_RXD_WAKEUP_FLAG        BIT(7)

#define UART_SetupIOL(bl) \
    GPIO_SetSF(GPIOC, BIT(0)|BIT(1))

#define UART_OPEN_CLOCK() \
	{\
     BASE_ICU_PTR->UART_PWD = 0;\
	}

#define UART_SetupTRFifo(txFifoTh,rxFifoTh) \
	(BFD(txFifoTh,0,8)|\
	BFD(rxFifoTh,8,8)|\
	0)

//     {\
//     BASE_UART_PTR->TX_FIFO_THRESHOLD =txFifo;\
//     BASE_UART_PTR->RX_FIFO_THRESHOLD =rxFifo;\
//     }

#define UART_Setup(ir_uart,dr,bl,sb,parEn,par) \
    /*ir_uart:1=irda,0=uart;  dr=datarate;  bl=bit length,5~8;  sb:stop bits,1~2;*/\
    /*parEn,par:parEn=1ʱ,1=��У��,0=żУ��*/\
	(BFD(ir_uart,2,1)|\
	BFD(bl-5,3,2)|\
	BFD(sb-1,7,1)|\
	BFD(UART_CLK/dr,8,13)|\
	BFD(parEn,5,1)|\
	BFD(par,6,1))

//     {\
//     /*ir_uart:1=irda,0=uart;  dr=datarate;  bl=bit length,5~8;  sb:stop bits,1~2;*/\
//     /*parEn,par:parEn=1ʱ,1=��У��,0=żУ��*/\
//     BASE_UART_PTR->UART_IRDA = ir_uart;\
//     BASE_UART_PTR->UART_LEN = bl-5;\
//     BASE_UART_PTR->UART_STOP_LEN = sb - 1;\
//     BASE_UART_PTR->UART_PAR_EN = parEn ;\
//     BASE_UART_PTR->UART_PAR_MODE = par;\
//     BASE_UART_PTR->UART_CLK_DIVID = (UART_CLK/dr);\
// 	}

#define UART_SetupInt() \
    {\
    BASE_UART_PTR->RX_FIFO_NEED_READ_MASK = 1;\
	/*BASE_UART_PTR->int_en = (RX_FIFO_NEED_READ_FLAG|UART_RX_STOP_END_FLAG|UART_TX_STOP_END_FLAG|TX_FIFO_NEED_WRITE_FLAG)*/;\
	BASE_UART_PTR->UART_TX_STOP_END_MASK = 1;\
    BASE_UART_PTR->UART_RX_STOP_END_MASK =1;\
    BASE_ICU_PTR->uart_int_en = 1;\
	}

#define UART_Open(tx,rx) \
    {\
    BASE_UART_PTR->UART_TX_ENABLE = tx;\
    BASE_UART_PTR->UART_RX_ENABLE =rx;\
	}

#define UART_CLOSE_CLOCK() \
	{\
     BASE_ICU_PTR->uart_pwd = 1;\
	}

#define UART_CLOSE(pn) \
    {\
    UART_CLOSE_CLOCK();\
	}

// #ifdef __cplusplus
// extern "C" {
// #endif

void Beken_UART_Initial(int dr);
void uart_send_byte(u8 data);
void uart_send( u8 *buff, int len);
void uart_puts( char *buff);
void print_i_hex(uint32 i);
void print_i_hex_c(uint32 i,int32 c);
void print_ui_dec(uint32 i);
void print_si_dec(int32 i);
void print_newline(void);
int uart_TX_end(void);
void uart_wait_for_txEnd(void);

int Beken_Uart_Rx_GetData(void*tar);
#define print_varname(vn)	\
	uart_puts(#vn)

#define print_var_ih(vn)	\
	{uart_puts(#vn);uart_puts(":");print_i_hex(vn);print_newline();}

#define print_var_sid(vn)	\
	{uart_puts(#vn);uart_puts(":");print_si_dec(vn);print_newline();}

#define print_var_uid(vn)	\
	{uart_puts(#vn);uart_puts(":");print_ui_dec(vn);print_newline();}

#define print_var_val_uh(vn,val)	\
	{uart_puts(#vn);uart_puts(":");print_i_hex(val);print_newline();}

#define print_var_val_ud(vn,val)	\
	{uart_puts(#vn);uart_puts(":");print_ui_dec(val);print_newline();}

#define print_var_val_sd(vn,val)	\
	{uart_puts(#vn);uart_puts(":");print_si_dec(val);print_newline();}
void x_puts_all(void);
// #ifdef __cplusplus
// }
// #endif

#endif
