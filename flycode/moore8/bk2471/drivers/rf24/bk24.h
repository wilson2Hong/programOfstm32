#ifndef _BK24_H_
#define _BK24_H_
#include "..\..\includes\types.h"
#define	BASE_BK24_PTR	\
		((HW_BK24*)0x00810000)

#define UART_DATA_LEN       32
#define UART_COMMAND_LEN    8

#define xdata
#define CODE


/* BEGIN: Added by 常云松, 2015/1/30   PN:1 */
#define  XBYTE      ((volatile uint32 *)0x00810000)
/* END:   Added by 常云松, 2015/1/30   PN:1 */

#define  ADDR_BASE_TRX          0x00
#define  ADDR_BASE_XRAM         0x00

#define  TRX_CONFIG             XBYTE[0x00 + ADDR_BASE_TRX]
#define  TRX_EN_AA              XBYTE[0x01 + ADDR_BASE_TRX]
#define  TRX_EN_RXADDR          XBYTE[0x02 + ADDR_BASE_TRX]
#define  TRX_SETUP_AW           XBYTE[0x03 + ADDR_BASE_TRX]
#define  TRX_SETUP_RETR         XBYTE[0x04 + ADDR_BASE_TRX]
#define  TRX_RF_CH              XBYTE[0x05 + ADDR_BASE_TRX]
#define  TRX_RF_SETUP           XBYTE[0x06 + ADDR_BASE_TRX]
#define  TRX_RX_ADDR_P0_0       XBYTE[0x07 + ADDR_BASE_TRX]
#define  TRX_RX_ADDR_P0_1       XBYTE[0x08 + ADDR_BASE_TRX]
#define  TRX_RX_ADDR_P0_2       XBYTE[0x09 + ADDR_BASE_TRX]
#define  TRX_RX_ADDR_P0_3       XBYTE[0x0A + ADDR_BASE_TRX]
#define  TRX_RX_ADDR_P0_4       XBYTE[0x0B + ADDR_BASE_TRX]
#define  TRX_RX_ADDR_P1_0       XBYTE[0x0C + ADDR_BASE_TRX]
#define  TRX_RX_ADDR_P1_1       XBYTE[0x0D + ADDR_BASE_TRX]
#define  TRX_RX_ADDR_P1_2       XBYTE[0x0E + ADDR_BASE_TRX]
#define  TRX_RX_ADDR_P1_3       XBYTE[0x0F + ADDR_BASE_TRX]

#define  TRX_RX_ADDR_P1_4       XBYTE[0x10 + ADDR_BASE_TRX]
#define  TRX_RX_ADDR_P2         XBYTE[0x11 + ADDR_BASE_TRX]
#define  TRX_RX_ADDR_P3         XBYTE[0x12 + ADDR_BASE_TRX]
#define  TRX_RX_ADDR_P4         XBYTE[0x13 + ADDR_BASE_TRX]
#define  TRX_RX_ADDR_P5         XBYTE[0x14 + ADDR_BASE_TRX]
#define  TRX_TX_ADDR_0          XBYTE[0x15 + ADDR_BASE_TRX]
#define  TRX_TX_ADDR_1          XBYTE[0x16 + ADDR_BASE_TRX]
#define  TRX_TX_ADDR_2          XBYTE[0x17 + ADDR_BASE_TRX]
#define  TRX_TX_ADDR_3          XBYTE[0x18 + ADDR_BASE_TRX]
#define  TRX_TX_ADDR_4          XBYTE[0x19 + ADDR_BASE_TRX]
#define  TRX_RX_PW_P0           XBYTE[0x1A + ADDR_BASE_TRX]
#define  TRX_RX_PW_P1           XBYTE[0x1B + ADDR_BASE_TRX]
#define  TRX_RX_PW_P2           XBYTE[0x1C + ADDR_BASE_TRX]
#define  TRX_RX_PW_P3           XBYTE[0x1D + ADDR_BASE_TRX]
#define  TRX_RX_PW_P4           XBYTE[0x1E + ADDR_BASE_TRX]
#define  TRX_RX_PW_P5           XBYTE[0x1F + ADDR_BASE_TRX]

#define  TRX_DYNPD              XBYTE[0x20 + ADDR_BASE_TRX]
#define  TRX_FEATURE            XBYTE[0x21 + ADDR_BASE_TRX]
#define  TRX_CFG_0C_0           XBYTE[0x22 + ADDR_BASE_TRX]
#define  TRX_CFG_0C_1           XBYTE[0x23 + ADDR_BASE_TRX]
#define  TRX_CFG_0C_2           XBYTE[0x24 + ADDR_BASE_TRX]
#define  TRX_CFG_0C_3           XBYTE[0x25 + ADDR_BASE_TRX]
#define  TRX_CFG_0D_0           XBYTE[0x26 + ADDR_BASE_TRX]
#define  TRX_CFG_0D_1           XBYTE[0x27 + ADDR_BASE_TRX]
#define  TRX_CFG_0D_2           XBYTE[0x28 + ADDR_BASE_TRX]
#define  TRX_CFG_0D_3           XBYTE[0x29 + ADDR_BASE_TRX]
#define  TRX_RAMP_TABLE_0       XBYTE[0x2A + ADDR_BASE_TRX]
#define  TRX_RAMP_TABLE_1       XBYTE[0x2B + ADDR_BASE_TRX]
#define  TRX_RAMP_TABLE_2       XBYTE[0x2C + ADDR_BASE_TRX]
#define  TRX_RAMP_TABLE_3       XBYTE[0x2D + ADDR_BASE_TRX]
#define  TRX_RAMP_TABLE_4       XBYTE[0x2E + ADDR_BASE_TRX]
#define  TRX_RAMP_TABLE_5       XBYTE[0x2F + ADDR_BASE_TRX]

#define  TRX_RAMP_TABLE_6       XBYTE[0x30 + ADDR_BASE_TRX]
#define  TRX_RAMP_TABLE_7       XBYTE[0x31 + ADDR_BASE_TRX]
#define  TRX_RAMP_TABLE_8       XBYTE[0x32 + ADDR_BASE_TRX]
#define  TRX_RAMP_TABLE_9       XBYTE[0x33 + ADDR_BASE_TRX]
#define  TRX_RAMP_TABLE_A       XBYTE[0x34 + ADDR_BASE_TRX]
#define  TRX_CE                 XBYTE[0x35 + ADDR_BASE_TRX]
#define  TRX_CMD                XBYTE[0x36 + ADDR_BASE_TRX]
#define  TRX_FIFO               XBYTE[0x37 + ADDR_BASE_TRX]
#define  TRX_SDATA_0            XBYTE[0x38 + ADDR_BASE_TRX]
#define  TRX_SDATA_1            XBYTE[0x39 + ADDR_BASE_TRX]
#define  TRX_SDATA_2            XBYTE[0x3A + ADDR_BASE_TRX]
#define  TRX_SDATA_3            XBYTE[0x3B + ADDR_BASE_TRX]
#define  TRX_SCTRL              XBYTE[0x3C + ADDR_BASE_TRX]
//#define  TRX_                 XBYTE[0x3D + ADDR_BASE_TRX]
#define  TRX_KCAL_OUT_B8_9      XBYTE[0x3E + ADDR_BASE_TRX]
#define  TRX_KCAL_OUT_B0_7      XBYTE[0x3F + ADDR_BASE_TRX]

#define  TRX_IRQ_STATUS         XBYTE[0x40 + ADDR_BASE_TRX]
//interrupt status bit
#define  B_IRQ_RX_DR            0x40
#define  B_IRQ_TX_DS            0x20
#define  B_IRQ_MAX_RT           0x10
#define  B_IRQ_TX_FULL          0x01
#define  TRX_OBSERVE_TX         XBYTE[0x41 + ADDR_BASE_TRX]
#define  TRX_RSSI_IND           XBYTE[0x42 + ADDR_BASE_TRX]
#define  TRX_FIFO_STATUS        XBYTE[0x43 + ADDR_BASE_TRX]
//FIFO status bit
#define  B_FIFO_TX_REUSE        0x40
#define  B_FIFO_TX_FULL         0x20
#define  B_FIFO_TX_EMPTY        0x10
#define  B_FIFO_RX_FULL         0x02
#define  B_FIFO_RX_EMPTY        0x01
#define  TRX_RX_RPL_WIDTH       XBYTE[0x44 + ADDR_BASE_TRX]
#define  TRX_MBIST_STATUS       XBYTE[0x45 + ADDR_BASE_TRX]
//#define  TRX_                 XBYTE[0x46 + ADDR_BASE_TRX]
//#define  TRX_                 XBYTE[0x47 + ADDR_BASE_TRX]
#define  TRX_BER_CNT_RCV_0      XBYTE[0x48 + ADDR_BASE_TRX]
#define  TRX_BER_CNT_RCV_1      XBYTE[0x49 + ADDR_BASE_TRX]
#define  TRX_BER_CNT_RCV_2      XBYTE[0x4A + ADDR_BASE_TRX]
#define  TRX_BER_CNT_RCV_3      XBYTE[0x4B + ADDR_BASE_TRX]
#define  TRX_BER_CNT_ERR_0      XBYTE[0x4C + ADDR_BASE_TRX]
#define  TRX_BER_CNT_ERR_1      XBYTE[0x4D + ADDR_BASE_TRX]
#define  TRX_BER_CNT_ERR_2      XBYTE[0x4E + ADDR_BASE_TRX]
#define  TRX_BER_CNT_ERR_3      XBYTE[0x4F + ADDR_BASE_TRX]

#define  TRX_TX_FREQ_OFFSET_0   XBYTE[0x50 + ADDR_BASE_TRX]
#define  TRX_TX_FREQ_OFFSET_1   XBYTE[0x51 + ADDR_BASE_TRX]
#define  TRX_TX_FREQ_OFFSET_2   XBYTE[0x52 + ADDR_BASE_TRX]
#define  TRX_TX_FREQ_OFFSET_3   XBYTE[0x53 + ADDR_BASE_TRX]
#define  TRX_RX_FREQ_OFFSET_0   XBYTE[0x54 + ADDR_BASE_TRX]
#define  TRX_RX_FREQ_OFFSET_1   XBYTE[0x55 + ADDR_BASE_TRX]
#define  TRX_RX_FREQ_OFFSET_2   XBYTE[0x56 + ADDR_BASE_TRX]
#define  TRX_RX_FREQ_OFFSET_3   XBYTE[0x57 + ADDR_BASE_TRX]
#define  TRX_TWO_POINT_DLY      XBYTE[0x58 + ADDR_BASE_TRX]
#define  TRX_PLL_SDM            XBYTE[0x59 + ADDR_BASE_TRX]
#define  TRX_KCAL_EN_BIT        0x00
#define  TRX_FM_GAIN_B8         XBYTE[0x5A + ADDR_BASE_TRX]
#define  TRX_FM_GAIN_B0_7       XBYTE[0x5B + ADDR_BASE_TRX]
#define  TRX_FM_KMOD_SET_B8     XBYTE[0x5C + ADDR_BASE_TRX]
#define  TRX_FM_KMOD_SET_B0_7   XBYTE[0x5D + ADDR_BASE_TRX]
#define  TRX_MOD_COEF_B8_12     XBYTE[0x5E + ADDR_BASE_TRX]
#define  TRX_MOD_COEF_B0_7      XBYTE[0x5F + ADDR_BASE_TRX]

#define  TRX_ANACTRL0           XBYTE[0x60 + ADDR_BASE_TRX]
#define  TRX_GPA0               XBYTE[0x61 + ADDR_BASE_TRX]
#define  TRX_GPA1               XBYTE[0x62 + ADDR_BASE_TRX]
#define  TRX_ANAPWD_CTRL0       XBYTE[0x63 + ADDR_BASE_TRX]
#define  TRX_ANAPWD_CTRL1       XBYTE[0x64 + ADDR_BASE_TRX]
#define  TRX_ANAPWD_CTRL2       XBYTE[0x65 + ADDR_BASE_TRX]
// #define  TRX_                XBYTE[0x66 + ADDR_BASE_TRX]
// #define  TRX_                XBYTE[0x67 + ADDR_BASE_TRX]
// #define  TRX_                XBYTE[0x68 + ADDR_BASE_TRX]
// #define  TRX_                XBYTE[0x69 + ADDR_BASE_TRX]
// #define  TRX_                XBYTE[0x6A + ADDR_BASE_TRX]
// #define  TRX_                XBYTE[0x6B + ADDR_BASE_TRX]
// #define  TRX_                XBYTE[0x6C + ADDR_BASE_TRX]
// #define  TRX_                XBYTE[0x6D + ADDR_BASE_TRX]
// #define  TRX_                XBYTE[0x6E + ADDR_BASE_TRX]
// #define  TRX_                XBYTE[0x6F + ADDR_BASE_TRX]

// #define  TRX_                XBYTE[0x70 + ADDR_BASE_TRX]
// #define  TRX_                XBYTE[0x71 + ADDR_BASE_TRX]
// #define  TRX_                XBYTE[0x72 + ADDR_BASE_TRX]
// #define  TRX_                XBYTE[0x73 + ADDR_BASE_TRX]
// #define  TRX_                XBYTE[0x74 + ADDR_BASE_TRX]
// #define  TRX_                XBYTE[0x75 + ADDR_BASE_TRX]
// #define  TRX_                XBYTE[0x76 + ADDR_BASE_TRX]
// #define  TRX_                XBYTE[0x77 + ADDR_BASE_TRX]
// #define  TRX_                XBYTE[0x78 + ADDR_BASE_TRX]
#define  TRX_ANAIND             XBYTE[0x79 + ADDR_BASE_TRX]
#define  TRX_CHIP_ID_1          XBYTE[0x7A + ADDR_BASE_TRX]
#define  TRX_CHIP_ID_0          XBYTE[0x7B + ADDR_BASE_TRX]
#define  TRX_DEVICE_ID_3        XBYTE[0x7C + ADDR_BASE_TRX]
#define  TRX_DEVICE_ID_2        XBYTE[0x7D + ADDR_BASE_TRX]
#define  TRX_DEVICE_ID_1        XBYTE[0x7E + ADDR_BASE_TRX]
#define  TRX_DEVICE_ID_0        XBYTE[0x7F + ADDR_BASE_TRX]

/*
#define  TRX_                   XBYTE[0x10 + ADDR_BASE_TRX]
#define  TRX_                   XBYTE[0x11 + ADDR_BASE_TRX]
#define  TRX_                   XBYTE[0x12 + ADDR_BASE_TRX]
#define  TRX_                   XBYTE[0x13 + ADDR_BASE_TRX]
#define  TRX_                   XBYTE[0x14 + ADDR_BASE_TRX]
#define  TRX_                   XBYTE[0x15 + ADDR_BASE_TRX]
#define  TRX_                   XBYTE[0x16 + ADDR_BASE_TRX]
#define  TRX_                   XBYTE[0x17 + ADDR_BASE_TRX]
#define  TRX_                   XBYTE[0x18 + ADDR_BASE_TRX]
#define  TRX_                   XBYTE[0x19 + ADDR_BASE_TRX]
#define  TRX_                   XBYTE[0x1A + ADDR_BASE_TRX]
#define  TRX_                   XBYTE[0x1B + ADDR_BASE_TRX]
#define  TRX_                   XBYTE[0x1C + ADDR_BASE_TRX]
#define  TRX_                   XBYTE[0x1D + ADDR_BASE_TRX]
#define  TRX_                   XBYTE[0x1E + ADDR_BASE_TRX]
#define  TRX_                   XBYTE[0x1F + ADDR_BASE_TRX]
*/


// command
#define  FLUSH_TX               { TRX_CMD = 0xA0; }
#define  FLUSH_RX               { TRX_CMD = 0x80; }
#define  REUSE_TX_PL            { TRX_CMD = 0x10; }

#define RF_PowerUp() \
	TRX_CONFIG &= _BIT(1)

#define RF_PowerDown() \
	TRX_CONFIG |= BIT(1)

#define RF_TurnOn_RX() \
	TRX_CONFIG |= BIT(0)

#define RF_TurnOn_TX() \
	TRX_CONFIG &= _BIT(0)

#define RF_EnAA(bl) \
	TRX_EN_AA = bl

#define RF_EnRxAddr(bl) \
	TRX_EN_RXADDR = bl

#define RF_SetAddrWidth(n) \
	TRX_SETUP_AW = ((n==3)?1:((n==4)?2:3))/*默认为5B地址*/

#define RF_SetupRetrans(dly,rpt) \
	TRX_SETUP_RETR = (\
	(rpt)|\
	(((dly)/250-1)<<4)\
	)/*定制重送参数，dly为重送延时，rpt重送次数*/

#define RF_SetupCRC(en,l) \
	TRX_CONFIG &= (~(BIT(2)|BIT(3)));\
	TRX_CONFIG |=(\
	((en)<<3)|\
	(((l==1)?0:1)<<2)\
	)/*定制crc参数，en使能crc，l为1字节或2字节(默认为2)*/

#define RF_SetupFeature(dpl,ackPL,dynACK) \
	TRX_FEATURE = ((dpl<<2)|(ackPL<<1)|dynACK)

#define RF_CE(s) \
	TRX_CE = (s)

#define RF_EnDyncPL(bl) \
	TRX_DYNPD = (bl)

#define RF_Set_Chn(chn) \
	{\
	TRX_RF_CH = chn+0x80;\
	/*RF_TX_FREQERR()=0x4b000000-0x80000*chn;*/\
	/*TRX_TX_FREQ_OFFSET_2 = ((0x4b00-(chn<<3))&0xff);*/\
	/*TRX_TX_FREQ_OFFSET_3 = (((0x4b00-(chn<<3))>>8)&0xff);*/\
	}

#define Rf_SetupDR(dr) \
    {/*dr<128,表示单位为Mbps;dr>128,表示单位为Kbps*/\
    TRX_RF_SETUP &= ~(BIT(5)|BIT(3));\
    if(dr==250){\
        TRX_RF_SETUP |= (BIT(5));\
        }\
    }

// #ifdef __cplusplus  
// extern "C" {  
// #endif  

/*
*函数名:
*	PowerUp_Rf
*功能:
*	RF上电
*参数:
*	无
*返回:
*	无
*/
void PowerUp_Rf(void);
/*
*函数名:
*	PowerDown_Rf
*功能:
*	RF power down
*参数:
*	无
*返回:
*	无
*/
void PowerDown_Rf(void);
/*
*函数名:
*	SwitchToRxMode
*功能:
*	RF 切换到接收模式
*参数:
*	无
*返回:
*	无
*/
void SwitchToRxMode(void);
/*
*函数名:
*	SwitchToTxMode
*功能:
*	RF 切换到接收模式
*参数:
*	无
*返回:
*	无
*/
void SwitchToTxMode(void);
/*
*函数名:
*	ChangeTxPipe
*功能:
*	RF 切换TX pipe
*参数:
*	无
*返回:
*	无
*/
void ChangeTxPipe(uint8 pipe_num);

/*
*函数名:
*	R_RX_PAYLOAD
*功能:
*	将RF的fifo数据读到buf中
*参数:
*	1.pBuf，bytes：payload数据的指针和长度
*返回:
*	无
*/
void R_RX_PAYLOAD(uint8 *pBuf, uint8 bytes);

/*
*函数名:
*	W_TX_PAYLOAD
*功能:
*	将数据写入RF的fifo（等待RX的ACK）
*参数:
*	1.pBuf，bytes：payload数据的指针和长度
*返回:
*	无
*/
void W_TX_PAYLOAD( uint8 *pBuf, uint8 bytes);

/*
*函数名:
*	W_TX_PAYLOAD_NOACK
*功能:
*	将数据写入RF的fifo（不需等待RX的ACK）
*参数:
*	1.pBuf，bytes：payload数据的指针和长度
*返回:
*	无
*/
void W_TX_PAYLOAD_NOACK(uint8 *pBuf, uint8 bytes);

/*
*函数名:
*	W_ACK_PAYLOAD
*功能:
*	带payload的ack包
*参数:
*	1.pBuf，bytes：payload数据的指针和长度
*	2.pipe：管道号
*返回:
*	无
*/
void W_ACK_PAYLOAD(uint8 *pBuf, uint8 bytes, uint8 pipe);

/*
*函数名:
*	Rf_Init
*功能:
*	RF初始化
*参数:
*	无
*返回:
*	无
*/
void Rf_Init(void);

/*
*函数名:
*	Rf_Init
*功能:
*	RF初始化
*参数:
*	1.data_rate:0=250Kbps,1=1Mbps
*返回:
*	无
*/
void Rf_SetDataRate(int data_rate);

/*
*函数名:
*	RF_SingleWaveTest
*功能:
*	单载波测试
*参数:
*	1.chn：测试频道
*返回:
*	无
*/
void RF_SingleWaveTest(uint8 chn);

/*
*函数名:
*	RF_SetupInterrupt
*功能:
*	设置RF中断
*参数:
*	1.bl：启用的rf中断列表
*返回:
*	无
*/
void RF_SetupInterrupt(uint32 bl);

/*
*函数名:
*	RF_StartTX
*功能:
*	启动rf发射数据
*参数:
*	1.chn：发射频道
*	2.buf，len：发射的数据和长度
*返回:
*	无
*/
void RF_StartTX(int chn,char*buf,int len);

/*
*函数名:
*	RF_StartRX
*功能:
*	启动rf接收数据
*参数:
*	1.chn：接收频道
*返回:
*	无
*/
void RF_StartRX(int chn);
/*
*函数名:
*	RF_StartTX_ACK
*功能:
*	启动rf发射数据需接收方ACK的
*参数:
*	1.chn：发射频道
*	2.buf，len：发射的数据和长度
*返回:
*	无
*/
void RF_StartTX_ACK(int chn,char*buf,int len);

/*
*函数名:
*	RF_StartRX_ACK
*功能:
*	启动rf接收数据并准备回传数据
*参数:
*	1.chn：接收频道
*	2.buf，len：回传数据参数
*	3.pipe：通讯pipe
*返回:
*	无
*/
void RF_StartRX_ACK(int chn,char*buf,int len,int pipe);

/*
*函数名:
*	RF_SetMyAddr
*功能:
*	设定RF本地地址
*参数:
*	1.addr：本地地址(最多5Byte)
*返回:
*	无
*/
void RF_SetMyAddr(char*addr);

/*
*函数名:
*	RF_SetRxPipeAddr
*功能:
*	设定RF支持的远程地址
*参数:
*	1.no：索引号
*	2.addr：远程地址(最多5Byte)
*返回:
*	无
*/
void RF_SetRxPipeAddr(int no,char*addr);

/*
*函数名:
*	RF_SetTxPower
*功能:
*	设定RF发射功率
*参数:
*	1.pwr：功率
*返回:
*	无
*/
#define RF_TXPWR_N49dBm		0
#define RF_TXPWR_N19dBm		1
#define RF_TXPWR_N13dBm		2
#define RF_TXPWR_N8dBm		3
#define RF_TXPWR_N3dBm		4
#define RF_TXPWR_0dBm		5
#define RF_TXPWR_2dBm		6
#define RF_TXPWR_4dBm		7
#define RF_TXPWR_5dBm		8

void RF_SetTxPower(int pwr);
// #ifdef __cplusplus  
// }
// #endif  

#if 0
typedef struct HW_BK24{
	union{
		uint32 TRX_CONFIG;
		struct{
			uint32 PRIM_RX:1;
			//RX/TX control,;1: PRX, 0: PTX ;
			uint32 PWR_UP:1;
			// 1: POWER UP,; 0:POWER DOWN
			uint32 CRCO:1;
			//CRC encoding scheme  ;'0' - 1 byte  ;'1' - 2 bytes;
			uint32 EN_CRC:1;
			//Enable CRC. Forced high if ;one of the bits in the EN_AA is high
			uint32 MASK_MAX_RT:1;
			//Mask interrupt caused by MAX_RT  ;1: Interrupt not reflected on the IRQ pin  ;0: Reflect MAX_RT as active low interrupt on the IRQ pin;
			uint32 MASK_TX_DS:1;
			//Mask interrupt caused by TX_DS  ;1: Interrupt not reflected on the IRQ pin  ;0: Reflect TX_DS as active low interrupt on the IRQ pin;
			uint32 MASK_RX_DR:1;
			//Mask interrupt caused by RX_DR  ;1: Interrupt not reflected on the IRQ pin  ;0: Reflect RX_DR as active low interrupt on the IRQ pin ;
			uint32 :25;
		};
	};
	union{
		uint32 TRX_EN_AA;
		struct{
			uint32 ENAA_P0:1;
			//Enable auto acknowledgement; data pipe 0
			uint32 ENAA_P1:1;
			//Enable auto acknowledgement; data pipe 1
			uint32 ENAA_P2:1;
			//Enable auto acknowledgement; data pipe 2
			uint32 ENAA_P3:1;
			//Enable auto acknowledgement; data pipe 3
			uint32 ENAA_P4:1;
			//Enable auto acknowledgement; data pipe 4
			uint32 ENAA_P5:1;
			//Enable auto acknowledgement; data pipe 5
			uint32 :26;
		};
	};
	union{
		uint32 TRX_EN_RXADDR;
		struct{
			uint32 ERX_P0:1;
			//Enable data pipe 0
			uint32 ERX_P1:1;
			//Enable data pipe 1
			uint32 ERX_P2:1;
			//Enable data pipe 2
			uint32 ERX_P3:1;
			//Enable data pipe 3
			uint32 ERX_P4:1;
			//Enable data pipe 4
			uint32 ERX_P5:1;
			//Enable data pipe 5
			uint32 :26;
		};
	};
	union{
		uint32 TRX_SETUP_AW;
		struct{
			uint32 AW:2;
			//RX/TX Address field width  ;'00' - Illegal  ;'01' - 3 bytes  ;'10' - 4 bytes  ;'11' -  5 bytes  ;LSB bytes are used if address width is below 5 bytes;
			uint32 :30;
		};
	};
	union{
		uint32 TRX_SETUP_RETR;
		struct{
			uint32 ARC:4;
			//Auto Retransmission Count  ;‘0000’ –Re-Transmit disabled  ;‘0001’ – Up to 1 Re-Transmission on fail; of AA  ; ……  ;‘1111’ – Up to 15 Re-Transmission on fail of AA ;
			uint32 ARD:4;
			//Auto Retransmission Delay  ;‘0000’ – Wait 250 us  ;‘0001’ – Wait 500 us  ;‘0010’ – Wait 750 us  ; ……..  ;‘1111’ – Wait 4000 us  ;(Delay defined from end of transmission to start of next transmission);
			uint32 :24;
		};
	};
	union{
		uint32 TRX_RF_CH              ;
		struct{
			uint32 RF_CH:7;
			//Sets the frequency channel
			uint32 RF_CH_sel:1;
			//BK24 auto frequency selection:;0: XVR use cur_cfg_chn as RF freq. channel;1: XVR use BK24 RF_CH[6:0] as RF freq. channel
			uint32 :24;
		};
	};
	union{
		uint32 TRX_RF_SETUP           ;
		struct{
			uint32 LNA_HCURR:1;
			//Setup LNA gain;0:Low gain(20dB down);1:High gain;
			uint32 RF_PWR:2;
			//Set RF output power in TX mode;RF_PWR[1:0];'00' – -10 dBm  ;'01' – -5 dBm  ;'10' –  0 dBm  ;'11' –  5 dBm;
			uint32 RF_DR:1;
			//Air Data Rate ,decide by 0x886 bit {[5],[3]};‘00’ – 1Mbps  ;‘01’ – 2Mbps  ;‘10’ – 250kbps  ;‘11’ – reserved;
			uint32 :1;
			uint32 En_250k_rate:1;
			//Set RF datarate to 250k
			uint32 :26;
		};
	};
    uint32 TRX_RX_ADDR_P0[5]       ;
    //Receive address data pipe 0. 5 Bytes maximum length. Write the number of bytes defined by SETUP_AW) ;
    uint32 TRX_RX_ADDR_P1[5]       ;
    //Receive address data pipe 1. 5 Bytes maximum length. Write the number of bytes defined by SETUP_AW) ;
	union{
		uint32 TRX_RX_ADDR_P2         ;
		struct{
			uint32 RX_ADDR_P2:8;
			//Receive address data pipe 2. Only LSB in this register.;MSB bytes is equal to RX_ADDR_P1[39:8]
			uint32 :24;
		};
	};
	union{
		uint32 TRX_RX_ADDR_P3         ;
		struct{
			uint32 RX_ADDR_P3:8;
			//Receive address data pipe 3. Only LSB in this register.;MSB bytes is equal to RX_ADDR_P1[39:8]
			uint32 :24;
		};
	};
	union{
		uint32 TRX_RX_ADDR_P4         ;
		struct{
			uint32 RX_ADDR_P4:8;
			//Receive address data pipe 4. Only LSB in this register.;MSB bytes is equal to RX_ADDR_P1[39:8]
			uint32 :24;
		};
	};
	union{
		uint32 TRX_RX_ADDR_P5         ;
		struct{
			uint32 RX_ADDR_P5:8;
			//Receive address data pipe 5. Only LSB in this register.;MSB bytes is equal to RX_ADDR_P1[39:8]
			uint32 :24;
		};
	};
    uint32 TRX_TX_ADDR[5]          ;
	union{
		uint32 TRX_RX_PW_P0           ;
		struct{
			uint32 RX_PW_P0:6;
			//Number of bytes in RX payload in data pipe 0 (1 to 32 bytes).  ;0:  not used  ;1 = 1 byte  ; …  ;32 = 32 bytes;
			uint32 :26;
		};
	};
	union{
		uint32 TRX_RX_PW_P1           ;
		struct{
			uint32 RX_PW_P1:6;
			//Number of bytes in RX payload in data pipe 1 (1 to 32 bytes).  ;0:  not used  ;1 = 1 byte  ; …  ;32 = 32 bytes  ;
			uint32 :26;
		};
	};
	union{
		uint32 TRX_RX_PW_P2           ;
		struct{
			uint32 RX_PW_P2:6;
			//Number of bytes in RX payload in data pipe 2 (1 to 32 bytes).  ;0:  not used  ;1 = 1 byte  ; …  ;32 = 32 bytes;
			uint32 :26;
		};
	};
	union{
		uint32 TRX_RX_PW_P3           ;
		struct{
			uint32 RX_PW_P3:6;
			//Number of bytes in RX payload in data pipe 3 (1 to 32 bytes).  ;0:  not used  ;1 = 1 byte  ;…  ;32 = 32 bytes;
			uint32 :26;
		};
	};
	union{
		uint32 TRX_RX_PW_P4           ;
		struct{
			uint32 RX_PW_P4:6;
			//Number of bytes in RX payload in data pipe 4 (1 to 32 bytes).  ;0:  not used  ;1 = 1 byte  ;…  ;32 = 32 bytes
			uint32 :26;
		};
	};
	union{
		uint32 TRX_RX_PW_P5           ;
		struct{
			uint32 RX_PW_P5:6;
			//Number of bytes in RX payload in data pipe 5 (1 to 32 bytes).  ;0:  not used  ;1 = 1 byte  ;…  ;32 = 32 bytes
			uint32 :26;
		};
	};
	union{
		uint32 TRX_DYNPD              ;
		struct{
			uint32 DPL_P0:1;
			//Enable dynamic payload length data pipe 0.  ;(Requires EN_DPL and ENAA_P0) ;
			uint32 DPL_P1:1;
			//Enable dynamic payload length data pipe 1.  ; (Requires EN_DPL and ENAA_P1) ;
			uint32 DPL_P2:1;
			//Enable dynamic payload length data pipe 2.  ; (Requires EN_DPL and ENAA_P2) ;
			uint32 DPL_P3:1;
			//Enable dynamic payload length data pipe 3.  ; (Requires EN_DPL and ENAA_P3) ;
			uint32 DPL_P4:1;
			//Enable dynamic payload length data pipe 4.  ; (Requires EN_DPL and ENAA_P4) ;
			uint32 DPL_P5:1;
			//Enable dynamic payload length data pipe 5.  ; (Requires EN_DPL and ENAA_P5) ;
			uint32 :26;
		};
	};
	union{
		uint32 TRX_FEATURE            ;
		struct{
			uint32 EN_DYN_ACK:1;
			//Enables the W_TX_PAYLOAD_NOACK
			uint32 EN_ACK_PAY:1;
			//Enables Payload with ACK
			uint32 EN_DPL:1;
			//Enables Dynamic Payload Length
			uint32 :29;
		};
	};
	union{
		uint32 TRX_CFG_0C_0           ;
		struct{
			uint32 cfg0c0:8;
			//No description
			uint32 :24;
		};
	};
	union{
		uint32 TRX_CFG_0C_1           ;
		struct{
			uint32 cfg0c1:8;
			//No description
			uint32 :24;
		};
	};
	union{
		uint32 TRX_CFG_0C_2           ;
		struct{
			uint32 cfg0c2:8;
			//No description
			uint32 :24;
		};
	};
	union{
		uint32 TRX_CFG_0C_3           ;
		struct{
			uint32 cfg0c3:8;
			//No description
			uint32 :24;
		};
	};
	union{
		uint32 TRX_CFG_0D_0           ;
		struct{
			uint32 cfg0d0:8;
			//No description
			uint32 :24;
		};
	};
	union{
		uint32 TRX_CFG_0D_1           ;
		struct{
			uint32 cfg0d1:8;
			//No description
			uint32 :24;
		};
	};
	union{
		uint32 TRX_CFG_0D_2           ;
		struct{
			uint32 cfg0d2:8;
			//No description
			uint32 :24;
		};
	};
	union{
		uint32 TRX_CFG_0D_3           ;
		struct{
			uint32 cfg0d3:8;
			//No description
			uint32 :24;
		};
	};
    uint32 TRX_RAMP_TABLE[11]       ;
	union{
		uint32 TRX_CE                 ;
		struct{
			uint32 BK2423_ce:1;
			//No description
			uint32 :31;
		};
	};
	union{
		uint32 TRX_CMD                ;
		struct{
			uint32 BK2401_cmd:8;
			//8'b10000000 :  Flush RX         8'b10100000 :  Flush TX          8'b00010000 :  Reusle TX PL     8'b01000000 :  Read RX Payload 8'b01100000 :  Write TX Payload   8'b01101ppp :  W_ACK_PAYLOAD    8'b01101000 :  W_TX_PAYLAOD_NOACK   8'b00000000 :  NOP
			uint32 :24;
		};
	};
	union{
		uint32 TRX_FIFO               ;
		struct{
			uint32 BK2401_FIFO:8;
			//X MODE: TX data payload register 1 - 32 bytes.;RX MODE: RX data payload register 1 - 32 bytes.;
			uint32 :24;
		};
	};
	union{
		uint32 TRX_SDATA_0            ;
		struct{
			uint32 :8;
			uint32 :24;
		};
	};
	union{
		uint32 TRX_SDATA_1            ;
		struct{
			uint32 :8;
			uint32 :24;
		};
	};
	union{
		uint32 TRX_SDATA_2            ;
		struct{
			uint32 :8;
			uint32 :24;
		};
	};
	union{
		uint32 TRX_SDATA_3            ;
		struct{
			uint32 :8;
			uint32 :24;
		};
	};
	union{
		uint32 TRX_SCTRL              ;
		struct{
			uint32 :8;
			uint32 :24;
		};
	};
	union{
		uint32 REG_0x3D;
		struct{
			uint32 :8;
			uint32 :24;
		};
	};
	union{
		uint32 TRX_KCAL_OUT_B8_9      ;
		struct{
			uint32 :5;
			uint32 :27;
		};
	};
	union{
		uint32 TRX_KCAL_OUT_B0_7      ;
		struct{
			uint32 :8;
			uint32 :24;
		};
	};
	union{
		uint32 TRX_IRQ_STATUS         ;
		struct{
			uint32 TX_FULL:1;
			//TX FIFO full flag.  ;1: TX FIFO full ;0: Available locations in TX FIFO;;
			uint32 RX_P_NO:3;
			//Data pipe number for the payload available for reading from RX_FIFO  ;000-101: Data Pipe Number  ;110: Not used ;111: RX FIFO Empty;
			uint32 MAX_RT:1;
			//Maximum number of TX retransmits interrupt  ;Write 1 to clear bit. If MAX_RT is asserted it must be cleared to enable
			uint32 TX_DS:1;
			//Data Sent TX FIFO interrupt;Asserted when packet transmitted on TX. If AUTO_ACK is activated, this bit is set high only when ACK is received.  ;Write 1 to clear bit.  ;
			uint32 RX_DR:1;
			//Data Ready RX FIFO interrupt;Asserted when new data arrives RX FIFO;Write 1 to clear bit.;
			uint32 :25;
		};
	};
	union{
		uint32 TRX_OBSERVE_TX         ;
		struct{
			uint32 :8;
			uint32 :24;
		};
	};
	union{
		uint32 TRX_RSSI_IND           ;
		struct{
			uint32 clr_cd:1;
			//Carrier Detect
			uint32 :7;
			uint32 :24;
		};
	};
}HW_BK24;
#endif

#endif
