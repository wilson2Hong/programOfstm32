#include "bk24.h"
#include "..\gpio\gpio.h"
#include "..\icu\icu.h"
#include "..\xvr\XVR_3231S.h"
#include "..\timer\timer.h"
#include "..\..\common\common.h"

const uint32 Cfg_0c_Val[4] = {0x1F/*0x1b*/, 0x1b, 0x73, 0x00};
const uint32 Cfg_0d_Val[4] = {0x36, 0xB4, 0x80, 0x28};

const uint32 P0_Address[5] = {0xAA,0xBB,0xCC,0x00,0x00};
const uint32 P1_Address[5] = {0xAA,0xBB,0xCC,0x00,0x01};

#define myLocalAddr rxEndpAddr
const uint32 txEndpAddr[5]= {0xAA,0xBB,0xCC,0x00,0x01};//遥控地址
const uint32 rxEndpAddr[5]= {0xAA,0xBB,0xCC,0x00,0x02};//飞控地址
const uint32 monEndpAddr[5]= {0xAA,0xBB,0xCC,0x00,0x03};//监控地址

uint32 xvr_reg0_f_bak[0x10];
uint8 Fifo_Data[32];
void kmod_calibration(void);
void memcpy_2461(volatile uint32 *p, void*src, uint8 len)
{
	uint32*val=(uint32*)src;
	uint8 i = 0;

	for ( i = 0; i < len ; i++ )
	{
		p[i] = val[i];
	}
}

void RF_SetMyAddr(char*addr){
	uint32*val=(uint32*)&TRX_TX_ADDR_0;
	uint8 i = 0;
	int len=((TRX_SETUP_AW&0x03)+2);
	for ( i = 0; i < len ; i++ ){
		val[i]=addr[i];
	}
}

void RF_SetRxPipeAddr(int no,char*addr){	
	const uint32*tblAddr[]={
		(uint32*)&TRX_RX_ADDR_P0_0,
		(uint32*)&TRX_RX_ADDR_P1_0,
		(uint32*)&TRX_RX_ADDR_P2,
		(uint32*)&TRX_RX_ADDR_P3,
		(uint32*)&TRX_RX_ADDR_P4,
		(uint32*)&TRX_RX_ADDR_P5
	};
	uint32*val=(uint32*)tblAddr[no];
	uint8 i = 0;
	int len=((TRX_SETUP_AW&0x03)+2);
	if(len>=2)len=1;
	for ( i = 0; i < len ; i++ ){
		val[i]=addr[i];
	}
}

void PowerUp_Rf(void)
{
	TRX_CONFIG |= 0x02;
}

void PowerDown_Rf(void)
{
	TRX_CONFIG &= 0xFD;
}

void SwitchToRxMode(void)
{
	PowerUp_Rf();
	FLUSH_RX;
	TRX_CE = 0;
	TRX_CONFIG |= 0x01;
	TRX_CE = 1;
}

void SwitchToTxMode(void)
{
	PowerUp_Rf();
	FLUSH_TX;
	TRX_CE = 0;
	TRX_CONFIG &= 0xFE;
	TRX_CE = 1;
}

void ChangeTxPipe(uint8 pipe)
{
	uint32 tmp_address[5];

	switch(pipe)
	{
	case 0:
		memcpy_2461(&TRX_RX_ADDR_P0_0, (void*)P0_Address, 5);
		memcpy_2461(&TRX_TX_ADDR_0, (void*)P0_Address, 5);
		memcpy_2461(&TRX_RX_ADDR_P1_0, (void*)P1_Address, 5);
		break;

	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		memcpy_2461(tmp_address, (void*)P1_Address, 5);

		if(pipe == 2)                              // For P1, need not change LSB
			tmp_address[0] = TRX_RX_ADDR_P2;
		else if(pipe == 3)
			tmp_address[0] = TRX_RX_ADDR_P3;
		else if(pipe == 4)
			tmp_address[0] = TRX_RX_ADDR_P4;
		else if(pipe == 5)
			tmp_address[0] = TRX_RX_ADDR_P5;

		memcpy_2461(&TRX_RX_ADDR_P0_0, (void*)tmp_address, 5);
		memcpy_2461(&TRX_TX_ADDR_0, (void*)tmp_address, 5);
		memcpy_2461(tmp_address, (void*)P1_Address, 5);
		tmp_address[2] = 0x37;                          // avoid for 2 same address for R1, R2, ... R5
		memcpy_2461(&TRX_RX_ADDR_P1_0, (void*)tmp_address, 5);
		break;

	default:
		break;
	}
}

void R_RX_PAYLOAD(uint8 *pBuf, uint8 bytes)
{
	uint8 i;

	TRX_CMD = 0x40;                   // command
	for(i=0; i<bytes; i++)
		pBuf[i] = TRX_FIFO;           // data
	TRX_CMD = 0x00;                   // end: nop command
}

void W_TX_PAYLOAD(uint8 *pBuf, uint8 bytes)
{
	uint8 i;

	TRX_CMD = 0x60;
	for(i=0; i<bytes; i++)
		TRX_FIFO = pBuf[i];
	TRX_CMD = 0x00;
}

void W_TX_PAYLOAD_NOACK(uint8 *pBuf, uint8 bytes)
{
	uint8 i;

	TRX_CMD = 0x68;
	for(i=0; i<bytes; i++)
		TRX_FIFO = pBuf[i];
	TRX_CMD = 0x00;
}

void W_ACK_PAYLOAD(uint8 *pBuf, uint8 bytes, uint8 pipe)
{
	uint8 i;

	TRX_CMD = 0x68 + pipe;
	for(i=0; i<bytes; i++)
		TRX_FIFO = pBuf[i];
	TRX_CMD = 0x00;
}
// #define __VER_IC__			__VER_IC_PIN64__
// #define __VER_IC__			__VER_IC_0629__
#define __VER_IC__			__VER_IC_0901__
#define __VER_IC_NEW__		3	//新版ic，not rdy
#define __VER_IC_PIN36__	2	//旧版32pin ic
#define __VER_IC_PIN64__	1	//旧版64pin ic
#define __VER_IC_0629__		4	//版本丝印：FS52620
#define __VER_IC_0901__		5	//版本丝印同0629：0901号贾波调距离版本
const uint32 tblXvrInit[]={
#if __VER_IC__==__VER_IC_NEW__
	//Analog Registers
	//reg 0x00~0x0f
	0x041025FB,0x61F936CC,0x41083441,0x801FEC00,
	0x7F91FE90,0x05490A0B,0x3D2B120F,0x8000480A,
	0x07A4A028,0x19407C00,0x00036208,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,
	//reg 0x10~0x1f
	0x00103232,0x15311910,0x00000056,0x00000000,
	0x00080000,0x00000000,0x00000000,0x00000000,
	0x000001DE,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,

	//reg 0x20~0x2f
	0x00A57977,0x0295E500,0x96000011,0xA0000000,
	0x00000780,0x00300000,0x58000800,0x0008F100,
	0x03030000,0x00001100,0x406A4054,0x00000000,
	0x00000000,0x0038B441,0x00000000,0x00000000,
	//reg 0x30~0x3f
	0x174110A3,0x0000026A,0xFFFF8080,0x0000029B,
	0x00000000,0x00000000,0x00000000,0x00000000,
	0x361C8011,0xC0008400,0x00000000,0x3F541280,
	0x9728051E,0x83FD8D14,0x83828F87,0x0000811B,
	//reg 0x40~0x4f
	0x01000000,0x07050402,0x120F0C0A,0x221E1A16,
	0x35302B26,0x4B45403A,0x635D5751,0x7C767069,
	0x968F8983,0xAEA8A29C,0xC5BFBAB4,0xD9D4CFCA,
	0xE9E5E1DD,0xF5F3F0ED,0xFDFBFAF8,0xFFFFFFFE,
#elif __VER_IC__==__VER_IC_PIN64__
	//Analog Registers
	0x041025FB,0x61F936CC,0x41083441,0x801FEC00,
	0x5F91FE90,0x05C90A0B,0x3D2B120F,0x8000480A,
	0x07A4A028,0x19407C00,0x00036208,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,
	//-------------------------------------------------------
	0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,
	// Reg0x20 ~ Reg0x2F : General and RF Timing
	0x00A57977,0x0295E500,0x96000000,0xA0000000,
	0x00000780,0x04700000,0x58000800,0x0008F100,
	0x03134363,0x00001100,0x405A4044,0x00000000,
	0x00000000,0x0038F441,0x00000000,0x00000000,
	// Reg0x30 ~ Reg0x37 : TX Modulate
	0x1D6110A3,0x0000026A,0xFFFF8080,0x0000029B,
	0x00000000,0x00000000,0x00000000,0x00000000,
	// Reg0x38 ~ Reg0x3F : RX Demodulate
	0x361C8011,0xC0008400,0x00000000,0x3F541280,
	0x9728051E,0x83FD8D14,0x83828F87,0x0000811B,
	// Reg0x40 ~ Reg0x4F : Ramping Table
	0x01000000,0x07050402,0x120F0C0A,0x221E1A16,
	0x35302B26,0x4B45403A,0x635D5751,0x7C767069,
	0x968F8983,0xAEA8A29C,0xC5BFBAB4,0xD9D4CFCA,
	0xE9E5E1DD,0xF5F3F0ED,0xFDFBFAF8,0xFFFFFFFE,

#elif __VER_IC__==__VER_IC_PIN36__
	//Analog Registers
	0x041025FB,0x61F936CC,0x41083441,0x801FEC00,
	0x5F91e690,0x05C90ACB,0x3D2B120F,0x8000480A,
	0x07A4A028,0x19407C00,0x00036208,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,

	//-------------------------------------------------------
	//skip:reg 0x10~0x1f
	0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,
	//-------------------------------------------------------

	// Reg0x20 ~ Reg0x2F : General and RF Timing
	0x00A57977,0x0295E500,0x96000000,0xA0000000,
	0x00000780,0x04300000,0x58000800,0x0008F100,
	0x03134363,0x00001100,0x405A4044,0x00000000,
	0x00000000,0x0038F441,0x00000000,0x00000000,
	// Reg0x30 ~ Reg0x37 : TX Modulate
	0x1D6110A3,0x0000026A,0xFFFF8080,0x0000029B,
	0x00000000,0x00000000,0x00000000,0x00000000,
	// Reg0x38 ~ Reg0x3F : RX Demodulate
	0x361C8011,0xC0008400,0x00000000,0x3F541280,
	0x9728051E,0x83FD8D14,0x83828F87,0x0000811B,
	// Reg0x40 ~ Reg0x4F : Ramping Table
	0x01000000,0x07050402,0x120F0C0A,0x221E1A16,
	0x35302B26,0x4B45403A,0x635D5751,0x7C767069,
	0x968F8983,0xAEA8A29C,0xC5BFBAB4,0xD9D4CFCA,
	0xE9E5E1DD,0xF5F3F0ED,0xFDFBFAF8,0xFFFFFFFE,
#elif __VER_IC__==__VER_IC_0629__
	//Analog Registers
	0x041025FB,0x65F936CC,0x41083441,0x809FEC00,
	0x7F91FE90,0x05490A0B,0x3D2B120f,0xc000480E,//0xc000480A;
	0x07A4A028,0x19407D00,//0x19507D00;// Set bit[22]=1, bit[12]=1, bit[11]=1, bit[10]=1. bit[9]=0
	0x00036208,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,
	//-------------------------------------------------------

	0x00103232,0x15311910,0x00000056,0x00000000,
	0x00080000,0x00000000,0x00000000,0x00000000,
	0x000001DE,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,

	0x00A57977,0x0295E500,0x96000011,0xA0000000,
	0x00000780,0x00300000,0x58000800,0x0008F100,
	0x03030000,0x00001100,0x406A404D,0x00000000,
	0x00000000,0x0038B441,0x00000000,0x00000000,

	0x174110A3,0x0000026A,0xFFFF8080,0x0000029B,
	0x00000000,0x00000000,0x00000000,0x00000000,
	0x361C8011,0xC0008400,0x00000000,0x3F541280,
	0x9728051E,0x83FD8D14,0x83828F87,0x0000811B,
	
	0x01000000,0x07050402,0x120F0C0A,0x221E1A16,
	0x35302B26,0x4B45403A,0x635D5751,0x7C767069,
	0x968F8983,0xAEA8A29C,0xC5BFBAB4,0xD9D4CFCA,
	0xE9E5E1DD,0xF5F3F0ED,0xFDFBFAF8,0xFFFFFFFE,
#elif __VER_IC__==__VER_IC_0901__
	0x041025FB,0x61F936CC,0x41083441,0x801FEC00,
	0x7f91e690,0x05490acb,0x3D2B120F,0x0000480A,
	0x07A4A028,0x18407C00,0x00032208,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,

	//-------------------------------------------------------
	0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,

	// Reg0x20 ~ Reg0x2F : General and RF Timing
	0x00A57977,0x0295E500,0x96000011,0xA0000000,
	0x00000780,0x04300000,0x58000800,0x0008F100,
	0x03030000,0x00001100,0x406A4054,0x00000000,
	0x00000000,0x0038B441,0x00000000,0x00000000,
	// Reg0x30 ~ Reg0x37 : TX Modulate
	0x1D6110A3,0x0000026A,0xFFFF8080,0x0000029B,
	0x00000000,0x00000000,0x00000000,0x00000000,
	// Reg0x38 ~ Reg0x3F : RX Demodulate
	0x361C8011,0xC0008400,0x00000000,0x3F541280,
	0x9728051E,0x83FD8D14,0x83828F87,0x0000811B,
	// Reg0x40 ~ Reg0x4F : Ramping Table
	0x01000000,0x07050402,0x120F0C0A,0x221E1A16,
	0x35302B26,0x4B45403A,0x635D5751,0x7C767069,
	0x968F8983,0xAEA8A29C,0xC5BFBAB4,0xD9D4CFCA,
	0xE9E5E1DD,0xF5F3F0ED,0xFDFBFAF8,0xFFFFFFFE,

#endif
};
void XVR_Init(){
	volatile uint32*ptr=(volatile uint32*)BASE_XVR_3231S_PTR;
	volatile uint32*src=(volatile uint32*)tblXvrInit;
	int i;
	uint32 t;
	//uint32 t;
	for(i=0;i<0x50;i++){
		t=src[i];
// #if __VER_IC__!=__VER_IC_NEW__
		if((i>>4)==1)continue;
//#endif
		if((i>>4)==0)xvr_reg0_f_bak[i]=t;
		ptr[i]=t;
	}
	kmod_calibration();
}

void Rf_Init(void)
{
	HW_XVR_3231S*xvr=BASE_XVR_3231S_PTR;
	XVR_Init();
	//volatile uint32 *p_APB_XVER_ADDR   = (volatile uint32*)  APB_XVER_BASE ;
	BASE_ICU_PTR->BK24_PWD = 0;
	xvr->REG_0x28 = 0x03044363;
	xvr->REG_0x2B = 0x000A2071;
	xvr->REG_0x3B = 0x3F541288;

	TRX_PLL_SDM &= _BIT(4);
	// 初始化cfg_0C, cfg_0D
	memcpy_2461(&TRX_CFG_0C_0, (void*)Cfg_0c_Val, 4);
	memcpy_2461(&TRX_CFG_0D_0, (void*)Cfg_0d_Val, 4);
	//	 SetDataRate(1);

// 	RF_SetupCRC(1,1);
	RF_SetupCRC(1,2);
	RF_EnAA(BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5));
	RF_EnRxAddr(BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5));
	RF_SetAddrWidth(5);

	RF_SetupRetrans(250,0);
	//TRX_RF_CH      = 0x80;//0x00;
	TRX_RF_SETUP   = 0x07;
    Rf_SetupDR(1);


	memcpy_2461(&TRX_RX_ADDR_P0_0, (void*)rxEndpAddr, 5);
	memcpy_2461(&TRX_RX_ADDR_P1_0, (void*)txEndpAddr, 5);
// 	TRX_RX_ADDR_P2 = 0x65;
// 	TRX_RX_ADDR_P3 = 0x65;
// 	TRX_RX_ADDR_P4 = 0x65;
// 	TRX_RX_ADDR_P5 = 0x65;
	TRX_RX_ADDR_P2 = 0x11;
	TRX_RX_ADDR_P3 = 0x12;
	TRX_RX_ADDR_P4 = 0x13;
	TRX_RX_ADDR_P5 = 0x14;
	memcpy_2461(&TRX_TX_ADDR_0, (void*)myLocalAddr, 5);

	TRX_RX_PW_P0 = 0x20;
	TRX_RX_PW_P1 = 0x20;
	TRX_RX_PW_P2 = 0x20;
	TRX_RX_PW_P3 = 0x20;
	TRX_RX_PW_P4 = 0x20;
	TRX_RX_PW_P5 = 0x20;
	RF_EnDyncPL(0x3f);
	RF_SetupFeature(1,1,1);
	PowerDown_Rf();
}

void RF_SetTxPower(int pwr){
	HW_XVR_3231S*xvr=BASE_XVR_3231S_PTR;
	uint32 t;
	switch(pwr){
		case RF_TXPWR_N49dBm:
			t=0;
			break;
		case RF_TXPWR_N19dBm:
			t=4;
			break;
		case RF_TXPWR_N13dBm:
			t=8;
			break;
		case RF_TXPWR_N8dBm:
			t=0x0c;
			break;
		case RF_TXPWR_N3dBm:
			t=0x10;
			break;
		case RF_TXPWR_0dBm:
			t=0x14;
			break;
		case RF_TXPWR_2dBm:
			t=0x18;
			break;
		case RF_TXPWR_4dBm:
			t=0x1c;
			break;
		case RF_TXPWR_5dBm:
			t=0x1f;
			break;
	}
	xvr_reg0_f_bak[4]&=_BFD(0x1f,24,5);
	xvr_reg0_f_bak[4]&=_BIT(29);
	xvr_reg0_f_bak[4]|=BFD(t,24,5);
	xvr->REG_0x4=xvr_reg0_f_bak[4];
// 	xvr->cur_cfg_pwr =pwr;
	//xvr->PAHqEn=0;
}

// void RF_SetTxPower(int pwr){
// 	HW_XVR_3231S*xvr=BASE_XVR_3231S_PTR;
// 	xvr->cur_cfg_pwr =pwr;
// }

void RF_SingleWaveTest(uint8 chn)
{
	HW_XVR_3231S*xvr=BASE_XVR_3231S_PTR;
	xvr->cur_cfg_chn = chn;
	xvr->REG_0x25 &= 0xfff00000;
	Delay_ms(200);
	xvr->REG_0x25 |= (0x1<<13) + (0x1<<12) ;
}

void RF_BeginTxPN9_Test(uint8 chn)
{
	HW_XVR_3231S*xvr=BASE_XVR_3231S_PTR;
	xvr->test_radio =0;
	xvr->test_tx_mode = 0;
	xvr->cur_cfg_chn = chn;
	Delay_ms(10);
	xvr->test_radio = 1;
	xvr->test_tx_mode =1;
	xvr->pn9_send_en =1;
}

void RF_StopTxPN9_Test()
{
	HW_XVR_3231S*xvr=BASE_XVR_3231S_PTR;
	xvr->pn9_send_en =0;
	xvr->test_radio =0;
	xvr->test_tx_mode = 0;
}

float RF_BER_Test(uint8 chn,int rpt)
{
	HW_XVR_3231S*xvr=BASE_XVR_3231S_PTR;
	xvr->REG_0x25 &=(_BIT(11)&_BIT(12)&_BIT(13));
	xvr->cur_cfg_chn = chn;
	xvr->test_radio = 1;
	xvr->test_radio = 0;
	xvr->test_radio = 1;
	xvr->pn9_recv_en =1;
	//int i;
	float ber;
	xvr->pn9_hold_en = 0;
	Delay_ms(6*rpt);//延时接收pn9
	xvr->pn9_hold_en = 1;
	ber=(float)xvr->REG_0x16;
	ber/=xvr->REG_0x15;
	return(ber);
}

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
void RF_SetupInterrupt(uint32 bl){
	/*清除RF中断标志*/
	TRX_IRQ_STATUS |=(B_IRQ_RX_DR|B_IRQ_TX_DS|B_IRQ_MAX_RT);
	/*清除中断标志*/
	BASE_ICU_PTR->bk24_if = 1;
	/*使能相应的RF中断源*/
	TRX_CONFIG |= (B_IRQ_RX_DR|B_IRQ_TX_DS|B_IRQ_MAX_RT);
	TRX_CONFIG &= (~bl);
	/*打开RF中断允许位*/
	BASE_ICU_PTR->bk24_int_en = 1;
}

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
void RF_StartTX(int chn,char*buf,int len){
	RF_Set_Chn(chn);
	Delay(50);
	SwitchToTxMode();
	FLUSH_TX;
	FLUSH_RX;
	TRX_IRQ_STATUS = 0x70;
	//RF_SetupInterrupt(B_IRQ_TX_DS|B_IRQ_RX_DR);
	while(TRX_FIFO_STATUS & B_FIFO_TX_FULL);    // Wait for TX_FIFO empty
	W_TX_PAYLOAD_NOACK((uint8*)buf, len);
	W_TX_PAYLOAD_NOACK((uint8*)buf, len);
	W_TX_PAYLOAD_NOACK((uint8*)buf, len);
}

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
void RF_StartRX(int chn){
	RF_Set_Chn(chn);
	Delay(50);
	SwitchToRxMode();
	FLUSH_TX;
	FLUSH_RX;
	//清rf中断标志
	TRX_IRQ_STATUS = 0x70;
}
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
void RF_StartTX_ACK(int chn,char*buf,int len){
	RF_Set_Chn(chn);
	//Delay(50);
	SwitchToTxMode();
	FLUSH_TX;
	FLUSH_RX;
	TRX_IRQ_STATUS = 0x70;
	//RF_SetupInterrupt(B_IRQ_TX_DS|B_IRQ_RX_DR);
	while(TRX_FIFO_STATUS & B_FIFO_TX_FULL);    // Wait for TX_FIFO empty
	
//	W_TX_PAYLOAD_NOACK((uint8*)buf, len);
	W_TX_PAYLOAD((uint8*)buf, len);
}

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
void RF_StartRX_ACK(int chn,char*buf,int len,int pipe){
	RF_StartRX(chn);
	W_ACK_PAYLOAD((uint8*)buf,len,pipe);
}

/*
*函数名:
*	kmod_calibration
*功能:
*	kmod_calibration
*参数:
*	无
*返回:
*	无
*/
void kmod_calibration(void) 
{
	uint32 value;
	uint32 value_kcal_result;
	uint32 tmp;
	// uint8  value_temp1, value_temp2, value_temp3, value_temp4;
	//uint8  k;
	HW_XVR_3231S*xvr=BASE_XVR_3231S_PTR;
	//   UART_WRITE_BYTE(0xB4);// Debug Only
	xvr->REG_0x5 = tmp = tblXvrInit[5]|BIT(23);
// 	printf("step1\r\n");
// 	Timer_SetTO_32K(TIMER1,TIMER_SRC32K_Nms(1),0);
// 	Timer_WaitTO(TIMER1,NULL,NULL);
// 	printf("step1 end\r\n");
	Delay(6000);
	xvr->REG_0x5=(tmp&_BIT(23));
	// Step 1.
	// Config the XVR analog SPI registers for Kmod calibration spe
	xvr->REG_0x1=	tmp = tblXvrInit[1] & (_BIT(7));// Clear Reg0x1 bit[7]
	xvr->REG_0x5=0x05490acb;
	xvr->REG_0x30 &= _BFD(0x1ff,21,9);
	xvr->REG_0x30 |= BFD(0x100,21,9);
// 	p_APB_XVER_ADDR[0x01] = XVR_ANALOG_REG_BAK[1] = XVR_ANALOG_REG_BAK[1] & (~(0x1<<7));// Clear Reg0x1 bit[7]
// 	p_APB_XVER_ADDR[0x05] = XVR_ANALOG_REG_BAK[5] = 0x05490ACB;//0x05490A0B ; // Set Reg0x5 bit[26:23]=0xA
// 	p_APB_XVER_ADDR[0x30] &= (~(0x1ff<<21));// Set FM Gain to ideal 0x100
// 	p_APB_XVER_ADDR[0x30] |=   (0x100<<21) ;

	// Step 2. 
	// Enable CEVA clock and interrupt to be used as a Timer. 
// 	REG_AHB0_ICU_CEVA_CLKPWD  = 0x00000000 ;  //Enable CEVA clock 
// 	REG_AHB0_ICU_INT_ENABLE  |= (INT_STATUS_CEVA_bit<<16) + INT_STATUS_CEVA_bit;
// 	REG_AHB0_FIQ_PRIORITY_EN |=  INT_STATUS_CEVA_bit;	// ZGF@20150123 added for BK3231S 

	// Set XVR.vco_kcal_en=1 to start Kmod Calibration.
// 	xvr->REG_0x25 |= BIT(16);
	xvr->vco_kcal_en =1;
// 	p_APB_XVER_ADDR[0x25] |= (1<<16); 

	// Use CEVA TIM3 interrupt to wait for enough time, here is 15ms
// 	printf("step2\r\n");
// 	Timer_SetTO_32K(TIMER1,TIMER_SRC32K_Nms(15),0);
// 	Timer_WaitTO(TIMER1,NULL,NULL);
// 	printf("step2 end\r\n");
	Delay_ms(90);
// 	CEVA_Intr_TIM3_Enable();  // TIM_INTR_MASK[3:0]=4'b0111
// 	k=0;
// 	while(k<12)
// 	{
// 		REG_AHB0_ICU_CORECLKCON  = 0x01;
// 		Delay(10);
// 
// 		if(IRQ_Flag_TIM3==0x1)
// 		{
// 			IRQ_Flag_TIM3=0x0;
// 			k++;
// 		}
// 	}
// 	CEVA_Intr_TIM3_Disable();  // TIM_INTR_MASK[3:0]=4'b1111

	// Step 3.
	// Get calibrated Kmod and clear XVR.vco_kcal_en to end Kmod Calibration. 
	value = xvr->REG_0x12;
// 	value = p_APB_XVER_ADDR[0x12];
	value = ((value & 0x1fff0000) >> 16);
// 	p_APB_XVER_ADDR[0x25] &= (~(1<<16)); 
// 	xvr->REG_0x25 &= _BIT(16);
	xvr->vco_kcal_en = 0;
	// Debug Only
	//   UART_WRITE_BYTE(0xB5);
	//   value_temp1 = (value&0xFF000000) >> 24;
	//   value_temp2 = (value&0x00FF0000) >> 16;
	//   value_temp3 = (value&0x0000FF00) >> 8;
	//   value_temp4 = (value&0x000000FF);
	//   UART_WRITE_BYTE(value_temp1);
	//   UART_WRITE_BYTE(value_temp2);
	//   UART_WRITE_BYTE(value_temp3);
	//   UART_WRITE_BYTE(value_temp4);

	// Step 4. Software calculation
	// FM_Gain * 250k / (Calibreated Kmod), here 250k means FM_Gain=0x100 for ideal 250k devaition 
	value_kcal_result = ( ((256 * 250 / value)-10) & 0x1ff );

	// Debug Only
	//   UART_WRITE_BYTE(0xB6);
	//   value_temp1 = (value_kcal_result&0xFF000000) >> 24;
	//   value_temp2 = (value_kcal_result&0x00FF0000) >> 16;
	//   value_temp3 = (value_kcal_result&0x0000FF00) >> 8;
	//   value_temp4 = (value_kcal_result&0x000000FF);
	//   UART_WRITE_BYTE(value_temp1);
	//   UART_WRITE_BYTE(value_temp2);
	//   UART_WRITE_BYTE(value_temp3);
	//   UART_WRITE_BYTE(value_temp4);

	// Step 5. Set FM Gain with calculated Kmod. 
	xvr->REG_0x30 &= _BFD(0x1ff,21,9);
	xvr->REG_0x30 |= BFD(value_kcal_result,21,9);
	xvr->REG_0x1 =(tmp | BIT(7));
// 	p_APB_XVER_ADDR[0x30] &= (~(0x1ff<<21));
// 	p_APB_XVER_ADDR[0x30] |= (value_kcal_result<<21);
// 	p_APB_XVER_ADDR[0x01]  = XVR_ANALOG_REG_BAK[1] = XVR_ANALOG_REG_BAK[1] | (0x1<<7);// Set Reg0x1 bit[7] for restore 

	//   UART_WRITE_BYTE(0xB7);// Debug Only
	//-------------------------------------------------------
}
