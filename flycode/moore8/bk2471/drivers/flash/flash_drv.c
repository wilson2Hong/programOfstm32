#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\icu\icu.h"
#include "..\flash\flash.h"
#include "..\..\common\common.h"
#include "..\uart\uart.h"

uint8 Flash_ID;

extern void Delay(int dly);
extern void Delay_ms(unsigned int ms);

void set_flash_clk(unsigned char clk_conf);
void set_flash_qe(void);

static void set_flash_qwfr(void);

void clr_flash_qwfr(void);
void flash_set_line_mode(uint8 mode);
void SET_FLASH_HPM(void);
uint32 GET_FLASH_STATUS(HW_FLASH*fls);

//=====================================================================================
//FLASH
//=====================================================================================
#define AHB_FLASH_BASE           0x00820000

#define reg_FLASH_OPERATE_SW            (*((volatile unsigned long *)   (AHB_FLASH_BASE+0*4)))
#define reg_FLASH_DATA_SW_FLASH         (*((volatile unsigned long *)   (AHB_FLASH_BASE+1*4)))
#define reg_FLASH_DATA_FLASH_SW         (*((volatile unsigned long *)   (AHB_FLASH_BASE+2*4)))
#define reg_FLASH_RDID_DATA_FLASH       (*((volatile unsigned long *)   (AHB_FLASH_BASE+4*4)))
#define reg_FLASH_SR_DATA_CRC_CNT       (*((volatile unsigned long *)   (AHB_FLASH_BASE+5*4)))
#define reg_FLASH_CONF                  (*((volatile unsigned long *)   (AHB_FLASH_BASE+7*4)))
#define flash_200k_ADDR                 (*((volatile unsigned long *)    (0x00032000)))
#define BIT_ADDRESS_SW                  0
#define BIT_OP_TYPE_SW                  24
#define BIT_OP_SW                       29
#define BIT_WP_VALUE                    30
#define BIT_BUSY_SW                     31

#define SET_ADDRESS_SW                  0xFFFFFF << BIT_ADDRESS_SW
#define SET_OP_TYPE_SW                  0x1F     << BIT_OP_TYPE_SW
#define SET_OP_SW                       0x1      << BIT_OP_SW
#define SET_WP_VALUE                    0x1      << BIT_WP_VALUE
#define SET_BUSY_SW                     0x1      << BIT_BUSY_SW

#define BIT_FLASH_CLK_CONF              0
#define BIT_MODE_SEL                    4
#define BIT_FWREN_FLASH_CPU             9
#define BIT_WRSR_DATA                   10
#define BIT_CRC_EN                      26

#define SET_FLASH_CLK_CONF              0xF      << BIT_FLASH_CLK_CONF
#define SET_MODE_SEL                    0x1F     << BIT_MODE_SEL
#define SET_FWREN_FLASH_CPU             0x1      << BIT_FWREN_FLASH_CPU
#define SET_WRSR_DATA                   0xFFFF   << BIT_WRSR_DATA
#define SET_CRC_EN                      0x1      << BIT_CRC_EN

#define BIT_SR_DATA_FLASH               0
#define BIT_CRC_ERR_COUNTER             8
#define BIT_DATA_FLASH_SW_SEL           16
#define BIT_DATA_SW_FLASH_SEL           19

#define SET_SR_DATA_FLASH               0xFF     << BIT_SR_DATA_FLASH
#define SET_CRC_ERR_COUNTER             0xFF     << BIT_CRC_ERR_COUNTER
#define SET_DATA_FLASH_SW_SEL           0x7      << BIT_DATA_FLASH_SW_SEL
#define SET_DATA_SW_FLASH_SEL           0x7      << BIT_DATA_SW_FLASH_SEL

#define FLASH_MAKE_OP(typ,trig,addr,wpv)	\
	/*typ:命令字;			trig:1=启动操作*/\
	/*addr:操作地址;		wpv:wp值*/\
	((addr&0xffffff)|\
	((typ)<<24)|\
	((trig)<<29)|\
	((wpv)<<30))

void WAIT_IDLE(HW_FLASH*fls){
	while(fls->busy_sw);
}

//GD25D40 id=514013,@16M
void GD25D40_init()
{
	HW_FLASH*fls=BASE_FLASH_PTR;
//	unsigned int temp0;

	WAIT_IDLE(fls);
	fls->wrsr_data = 0x002c;
	WAIT_IDLE(fls);
	//Start WRSR
	fls->cmd =FLASH_MAKE_OP(FLASH_OPCODE_WRSR2,1,0,1);
	
	WAIT_IDLE(fls);
	fls->cmd =FLASH_MAKE_OP(FLASH_OPCODE_RDSR2,1,0,1);

	WAIT_IDLE(fls);
}

//GD25Q41 id=c84013,@16M
void GD25Q41_init()
{
	HW_FLASH*fls=BASE_FLASH_PTR;
//	unsigned int temp0;

	//BK3231S_GPIO_DATA(PORTD) |= GPIO(0);
	WAIT_IDLE(fls);
	fls->cmd = FLASH_MAKE_OP(FLASH_OPCODE_RDID,1,0,1);
	WAIT_IDLE(fls);
	
	// WRITE FLASH EN BP[] = 0,
	fls->wrsr_data = 0;
	WAIT_IDLE(fls);
	//Start WRSR
	fls->cmd = FLASH_MAKE_OP(FLASH_OPCODE_WRSR2,1,0,1);
	WAIT_IDLE(fls);
}

uint32 GET_FLASH_ID(void)
{
	HW_FLASH*fls=BASE_FLASH_PTR;
	WAIT_IDLE(fls);
	fls->cmd = FLASH_MAKE_OP(FLASH_OPCODE_RDID,1,0,1);
	WAIT_IDLE(fls);
	return(fls->rdid_dat/*reg_FLASH_RDID_DATA_FLASH*/ );
}

void SET_FLASH_HPM(void){
	HW_FLASH*fls=BASE_FLASH_PTR;
	WAIT_IDLE(fls);
	fls->cmd = 
		FLASH_MAKE_OP(FLASH_OPCODE_HPM,1,0,fls->cmd&BIT(30));
	WAIT_IDLE(fls);
}

uint32 GET_FLASH_STATUS(HW_FLASH*fls)
{
	uint32 sr;
	WAIT_IDLE(fls);
	fls->cmd = FLASH_MAKE_OP(FLASH_OPCODE_RDSR,1,0,1);
	WAIT_IDLE(fls);
	sr=fls->sr_data_flash;
	WAIT_IDLE(fls);
	fls->cmd = FLASH_MAKE_OP(FLASH_OPCODE_RDSR2,1,0,1);
	WAIT_IDLE(fls);
	sr+=(fls->sr_data_flash<<8);
	return(sr);
}


void flash_init(void)
{
	uint32 i;
	HW_FLASH*fls=BASE_FLASH_PTR;
//	HW_ICU *icu=BASE_ICU_PTR;
	i = GET_FLASH_ID();
	if(i == 0xc84013 ){
		//Flash_ID = GD25Q41;
//		PRINT("GD25Q41\r\n");
		GD25Q41_init();

		set_flash_qe(); //enable qual mode
		SET_FLASH_HPM();

		Delay_ms(5);
		fls->CONF |= 0x10;
		flash_set_line_mode(0x4);// switch to Flash quad-line word operation
		set_flash_clk(0x01);
	}else//	if( i == 0x514013)
	{
		//Flash_ID = GD25D40;
//		PRINT("GD25D40\r\n");
		GD25D40_init();
		flash_set_line_mode(0x1);// switch to Flash single-line operation
		set_flash_clk(0x8);// 4'b1000=0x8: switch to 16MHz Flash clock
	}

}
void set_flash_clk(unsigned char clk_conf) {
	//note :>16M don't use la for flash debug
	BASE_FLASH_PTR->flash_clk_conf = clk_conf;
}
#define FLASH_CLK_XTAL			BIT(3)
#define FLASH_CLK_DPLL_48M		0x00
#define FLASH_CLK_DPLL_16M		BIT(2)
#define FLASH_MODE_RD_STANDARD	BFD(0,4,2)
//标准读模式
#define FLASH_MODE_RD_4L		BFD(2,4,2)
//4线读
#define FLASH_MODE_RD_QUAD		BFD(2,4,2)
//4线读
#define FLASH_MODE_RD_2L		BFD(1,4,2)
//2线读
#define FLASH_MODE_RD_DUAL		BFD(1,4,2)
//2线读

#define FLASH_MODE_QR_EB		0
//4线读命令字为EB
#define FLASH_MODE_QR_E7		BIT(7)
//4线读命令字为E7
#define FLASH_MODE_DR_3B		0
//2线读命令字为3B
#define FLASH_MODE_DR_BB		BIT(6)
//2线读命令字为BB
#define FLASH_MODE_CRMR_FF		0
//连续读复位(Continous Read Mode Reset)命令字为FF
#define FLASH_MODE_CRMR_FFFF	BIT(8)
//连续读复位命令字为FF

#define FLASH_MAKE_CONFIG(clk,pres,crmr,qr_cmd,dr_cmd,rdmd,fsr)		\
	/*clk:flash时钟设定；			pres：分频数，2^pres分频*/\
	/*crmr:连续读复位命令字选择;	qr_cmd:4线读命令字选择*/\
	/*dr_cmd:2线读命令字选择;		rdmd:读模式:standard,2L,4L*/\
	/*fsr：将要写入flash SR的值*/\
	((clk)|\
	(pres)|\
	(rdmd)|\
	(crmr)|\
	(qr_cmd)|\
	(dr_cmd)|\
	((fsr)<<10)|\
	0)


void set_flash_qe(void) {
	HW_FLASH*fls=BASE_FLASH_PTR;
	uint32 t;

	WAIT_IDLE(fls);
	//WRSR QE=1
	t=fls->CONF;
	t&=_BFD(0xffff,10,16);
	t|=BFD(0x22c,10,16);
	fls->CONF = t;
	//Start WRSR
	//temp0 = reg_FLASH_OPERATE_SW;
	fls->cmd = FLASH_MAKE_OP(FLASH_OPCODE_WRSR2,1,0,1);
	WAIT_IDLE(fls);

}

static void set_flash_qwfr(void) {
	uint32 tmp;
	HW_FLASH*fls=BASE_FLASH_PTR;
	tmp=fls->CONF;
//	PRINT("value0=%.8x\r\n",tmp);
	WAIT_IDLE(fls);
	//tmp = 0x0408b2a1;
	tmp&=_BFD(3,4,2);
	tmp|=FLASH_MODE_RD_4L;
// 	tmp=BFD(GET_BFD(tmp,10,16),10,10)|
// 		FLASH_MODE_RD_4L|
// 		(tmp&BIT(9))|
// 		(tmp&BFD(0x0f,0,4))|
// 		(tmp&BIT(26));
	fls->CONF = tmp;
	Delay(100);
	//fls->cmd = FLASH_MAKE_OP(FLASH_OPCODE_CRMR,1,0,fls->cmd&BIT(30));
	WAIT_IDLE(fls);
}


void clr_flash_qwfr(void) {
	HW_FLASH*fls=BASE_FLASH_PTR;
	WAIT_IDLE(fls);
	uint32 tmp=fls->CONF;
	tmp&=_BFD(3,4,2);
	tmp|=FLASH_MODE_RD_2L;
// 	tmp=BFD(GET_BFD(tmp,10,16),10,10)|
// 		FLASH_MODE_RD_2L|
// 		(tmp&BIT(9))|
// 		(tmp&BFD(0x0f,0,4))|
// 		(tmp&BIT(26));
	fls->CONF = tmp;
	fls->cmd = FLASH_MAKE_OP(FLASH_OPCODE_CRMR,1,0,fls->cmd&BIT(30));
	WAIT_IDLE(fls);
}

void flash_set_line_mode(uint8 mode) {
	if (mode == 1)
		clr_flash_qwfr();
	else if (mode == 4)
		set_flash_qwfr();                  /**< 4线打开 */
}

/*
 *函数名:
 *	Flash_WaitForWIP
 *功能:
 *	flash等待写操作完成
 *参数:
 *	1、fls：flash外设基地址
 *返回:
 *	无
 *特殊:
 *	1.
 *	2.stack:0
*/
static void Flash_WaitForWIP(HW_FLASH*fls)
{
	uint32 i;
	while(1){
		WAIT_IDLE(fls);
		fls->cmd = FLASH_MAKE_OP(FLASH_OPCODE_RDSR,1,0,1);
		WAIT_IDLE(fls);
		i=fls->sr_data_flash;
		if((i&BIT(0))==0)break;
	}
}

/*
 *函数名:
 *	Flash_Erase
 *功能:
 *	flash擦除sector/32K block/64K block/chip
 *参数:
 *	1、address：擦除的flash地址
 *	2、sel：擦除的方式:0=sector,1=32K block,2=64K block,3=chip
 *返回:
 *	无
 *特殊:
 *	1.
 *	2.stack:0
*/
void Flash_Erase(uint32 address,int sel)
{
	HW_FLASH*fls=BASE_FLASH_PTR;
	int cmd;
	switch(sel){
		case 0:
			cmd=FLASH_OPCODE_SE;
			break;
		case 1:
			cmd=FLASH_OPCODE_BE1;
			break;
		case 2:
			cmd=FLASH_OPCODE_BE2;
			break;
		case 3:
			cmd=FLASH_OPCODE_CE;
			break;
	}
//	PRINT("operating address=%x,",address);

	WAIT_IDLE(fls);
	fls->cmd = FLASH_MAKE_OP(cmd,1,address,1);
	WAIT_IDLE(fls);
	Flash_WaitForWIP(fls);

}

/*
 *函数名:
 *	flash_read_in_sub_page
 *功能:
 *	flash下一次读操作命令
 *参数:
 *	1、fls：flash外设指针
 *	1、address：flash地址（4的倍数）
 *	2、buffer，len：缓冲区指针和大小(4的倍数)。
 *返回:
 *	无
 *特殊:
 *	1.地址的b1b0为00
 *	2.stack:0
*/
static void flash_read_in_sub_page(HW_FLASH*fls,uint32 address, void *buffer, uint32 len){
	uint8 buf[32];
	uint32 *pbuf=(uint32*)buf;
	uint32 sz=len;
	WAIT_IDLE(fls);
	fls->cmd = FLASH_MAKE_OP(FLASH_OPCODE_READ,1,(address&_BFD(0x1f,0,6)),fls->cmd&BIT(30));
	//每下一次cmd能够读取32bytes,并且不支持跨页
	WAIT_IDLE(fls);
	len=8;
	while(len--){
		*pbuf++=fls->rd_dat;
	}
	memcpy(buffer,&buf[address&0x1f],sz);
}


/*
 *函数名:
 *	Flash_Read
 *功能:
 *	flash读操作
 *参数:
 *	1、address：flash地址
 *	2、buffer，len：缓冲区指针和大小。
 *返回:
 *	无
 *特殊:
 *	1.
*/
void Flash_Read(uint32 address, void *buffer, uint32 len)
{
	HW_FLASH*fls=BASE_FLASH_PTR;
	uint8 *pbuf=(uint8*)buffer;
	int pre,p_in,pst;
	int i;
	pre=32-(address&0x1f);
	if(address&0x1f){//子页对齐
		if(len>=pre){
			flash_read_in_sub_page(fls,address,pbuf,pre);
			address+=pre;
			pbuf+=pre;
		}else{
			pre=0;
		}
	}else{
		pre=0;
	}
	pst=((len-pre)&0x1f);
	p_in=((len-pre)>>5);
	for(i=0;i<p_in;i++){//整子页读入
		flash_read_in_sub_page(fls,address,pbuf,32);
		pbuf+=32;
		address+=32;
	}
	if(pst){//尾数据读入
		flash_read_in_sub_page(fls,address,pbuf,pst);
	}
}
/*
 *函数名:
 *	Flash_CheckBlankPage
 *功能:
 *	flash检查空页面
 *参数:
 *	1、address：flash地址（4的倍数）
 *返回:
 *	无
 *特殊:
 *	1.地址的b1b0为00
 *	2.stack:0
*/
static int is_blank(void*buf,int len)
{
	int*ptr=(int*)buf;
	len=(len>>2);
	while(len--){
		if(*ptr++!=-1)return(0);
	}
	return(1);
}

/*
 *函数名:
 *	Flash_CheckBlankPage
 *功能:
 *	flash检查空页面
 *参数:
 *	1、address：flash地址（4的倍数）
 *返回:
 *	无
 *特殊:
 *	1.地址的b1b0为00
 *	2.stack:0
*/
int Flash_CheckBlankPage(uint32 address)
{
	int buf[FLASH_PAGE_SIZE/sizeof(int)];
	address&=(0xffffffff^(FLASH_PAGE_SIZE-1));//取页面首地址
	Flash_Read(address,buf,FLASH_PAGE_SIZE);
	return(is_blank(buf,FLASH_PAGE_SIZE));
}

/*
 *函数名:
 *	Flash_CheckBlankRange
 *功能:
 *	flash检查空区域
 *参数:
 *	1、address：flash地址（4的倍数）
 *	2、sz:区域大小，（4的倍数）
 *返回:
 *	无
 *特殊:
 *	1.地址的b1b0为00
 *	2.stack:0
*/
int Flash_CheckBlankRange(uint32 address,uint32 sz)
{
	uint32 i;
	uint8 buf[FLASH_PAGE_SIZE];
	uint32 m,r;
	int f;
	m=(sz>>8);
	r=(sz&0xff);
	for(i=0;i<m;i++){
		Flash_Read(address,buf,FLASH_PAGE_SIZE);
		f=is_blank(buf,FLASH_PAGE_SIZE);
		if(f==0)return(f);
		address+=FLASH_PAGE_SIZE;
	}
	if(r){
		Flash_Read(address,buf,r);
		return(is_blank(buf,r));
	}
	return(1);
}
/*
 *函数名:
 *	flash_write_in_sub_page
 *功能:
 *	flash下一次写操作命令
 *参数:
 *	1、fls：flash外设指针
 *	1、address：flash地址（4的倍数）
 *	2、buffer，len：缓冲区指针和大小(4的倍数)。
 *返回:
 *	无
 *特殊:
 *	1.地址的b1b0为00
 *	2.stack:0
*/
static void flash_write_in_sub_page(HW_FLASH*fls,uint32 address, void *buffer, uint32 len){
	uint8 buf[32];
	uint32 *pbuf=(uint32*)buf;
	//每下一次cmd最多能够写入32bytes,并且不支持跨页
	//因为flash只能将1改为0，所以写1并不影响对应的位
	memset(buf,0xff,32);
	memcpy(&buf[address&0x1f],buffer,len);
	WAIT_IDLE(fls);
	len=8;
	while(len--){
		fls->wr_dat=*pbuf++;
	}
	WAIT_IDLE(fls);
	fls->cmd = FLASH_MAKE_OP(FLASH_OPCODE_PP,1,(address&_BFD(0x1f,0,6)),fls->cmd&BIT(30));
	WAIT_IDLE(fls);
	//Flash_WaitForWIP(fls);
	//WAIT_IDLE(fls);
	
}

/*
 *函数名:
 *	Flash_Write
 *功能:
 *	flash写操作
 *参数:
 *	1、address：flash地址
 *	2、buffer，len：缓冲区指针和大小。
 *返回:
 *	无
 *特殊:
 *	1.
*/
char dFlashEn=0;
char Flash_Write(uint32 address, void *buffer, uint32 len)
{
	HW_FLASH*fls=BASE_FLASH_PTR;
	uint8 *pbuf=(uint8*)buffer;
	
	int pre,p_in,pst;
	int i;
	if(dFlashEn == 0)
		return 0;
	//锁定flash地址
//	if(address=!0x7c000)	return 0;	
	pre=32-(address&0x1f);
	if(address&0x1f){//子页对齐
		if(len>=pre){
			flash_write_in_sub_page(fls,address,pbuf,pre);
			address+=pre;
			pbuf+=pre;
		}else{
			pre=0;
		}
	}else{
		pre=0;
	}
	pst=((len-pre)&0x1f);
	p_in=((len-pre)>>5);
	for(i=0;i<p_in;i++){//整子页写入
		flash_write_in_sub_page(fls,address,pbuf,32);
		pbuf+=32;
		address+=32;
	}
	if(pst){//尾数据处理
		flash_write_in_sub_page(fls,address,pbuf,pst);
	}
	return 1;
}

