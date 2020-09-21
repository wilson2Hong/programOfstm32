#ifndef _FLASH_H_
#define _FLASH_H_
#include "..\..\includes\types.h"
#define	BASE_FLASH_PTR	\
		((HW_FLASH*)0x00820000)

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


#pragma anon_unions
typedef struct HW_FLASH{
	union{
		uint32 REG_0x0;
		uint32 cmd;
		struct{
			uint32 addr_sw_reg:24;
			//flash operation address
			uint32 op_type_sw:5;
			//flash operation command type(decimal);1  :WREN;2  :WRDI;3  :RDSR;4  :WRSR;5  :READ;6  :RDSR2;7  :WRSR2;12 :PP;13 :SE;14 :BE1;15 :BE2;16 :CE;17 :DP;18 :RFDP;20 :RDID;21 :HPM;22 :CRMR;23 :CRMR2
			uint32 op_sw:1;
			//software operation startup trigger
			uint32 wp_value:1;
			//wp output value
			uint32 busy_sw:1;
			//flash status busy bit for software
		};
	};
	union{
		uint32 REG_0x1;
		uint32 wr_dat;
		struct{
			uint32 data_sw_flash_reg:32;
			//data to be written from software to flash
		};
	};
	union{
		uint32 REG_0x2;
		uint32 rd_dat;
		struct{
			uint32 data_flash_sw_reg:32;
			//data read from flash to software
		};
	};
	uint32 REG_0x3;
	union{
		uint32 REG_0x4;
		uint32 rdid_dat;
		struct{
			uint32 rdid_data_flash:32;
			//read flash id data
		};
	};
	union{
		uint32 REG_0x5;
		uint32 sr;
		struct{
			uint32 sr_data_flash:8;
			//state register data from flash
			uint32 crc_err_counter:8;
			//crc error number
			uint32 data_flash_sw_sel:3;
			//No. byte software write to flash
			uint32 data_sw_flash_sel:3;
			//No. byte software read from flash
			uint32 :10;
		};
	};
    uint32 REG_0x6;
	union{
		uint32 REG_0x7;
		uint32 CONF;
		struct{
			uint32 flash_clk_conf:4;
			//[3]: 0:bit[2] dpll selection, 1:clk_XTAL;[2]: 0:clk_PLL1(48M), 1:clk_PLL0(DCO16M);[1:0](flash clock divider): ;00:1, 01:2, 10:4, 11:8
			uint32 mode_sel:5;
			//[4]:CRMR type select,  0:FF 1:FFFF;[3]:quad read mode select, 0:EB 1:E7;[2]:dual read mode select, 0:3B 1:BB;[1:0]:read mode select: 00:standard 01:dual read 10:quad read
			uint32 fwren_flash_cpu:1;
			//cpu data writting enable
			uint32 wrsr_data:16;
			//flash status register data to be written
			uint32 crc_en:1;
			//flash data to CPU CRC enable
			uint32 :5;
		};
	};
}HW_FLASH;
/// flash operation command type(decimal)
typedef enum {
	FLASH_OPCODE_WREN/*flash write enable*/				= 1,
	FLASH_OPCODE_WRDI/*flash write disable*/			= 2,
	FLASH_OPCODE_RDSR/*flash read status register(b0-b7)*/		= 3,
	FLASH_OPCODE_WRSR/*flash write status register(b0-b7)*/	= 4,
	FLASH_OPCODE_READ/*flash read operate*/				= 5,
	FLASH_OPCODE_RDSR2/*flash read status register(b8-b15)*/	= 6,
	FLASH_OPCODE_WRSR2/*flash write status register(b0-b15)*/	= 7,
	FLASH_OPCODE_PP/*flash page program*/				= 12,
	FLASH_OPCODE_SE/*flash sector erase */				= 13,
	FLASH_OPCODE_BE1/*flash block erase 32KB*/			= 14,
	FLASH_OPCODE_BE2/*flash block erase 64KB*/			= 15,
	FLASH_OPCODE_CE/*flash chip erase */				= 16,
	FLASH_OPCODE_DP/*flash deep power down*/			= 17,
	FLASH_OPCODE_RFDP/*release from deep power down*/	= 18,
	FLASH_OPCODE_RDID/*read flash-ic ID*/				= 20,
	FLASH_OPCODE_HPM/*flash high performance mode*/		= 21,
	FLASH_OPCODE_CRMR/*flash continous read mode reset*/	= 22,
	FLASH_OPCODE_CRMR2										= 23,
} FLASH_OPCODE;

/*
 *GD25Q41:总计512KB，每个page 256B，16page构成1个sector，16个sector构成1个block
*/
#define KBytes				*1024
#define FLASH_TOTAL_SIZE	(512 KBytes)
#define FLASH_PAGE_SIZE		(256)
#define FLASH_SECTOR_SIZE		(FLASH_PAGE_SIZE*16)
#define FLASH_BLOCK_SIZE		(FLASH_SECTOR_SIZE*16)

#define FLASH_TOTAL_PAGE	(FLASH_TOTAL_SIZE/FLASH_PAGE_SIZE)
#define FLASH_TOTAL_SECTOR	(FLASH_TOTAL_SIZE/FLASH_SECTOR_SIZE)
#define FLASH_TOTAL_BLOCK	(FLASH_TOTAL_SIZE/FLASH_BLOCK_SIZE)

#define FLASH_ADDR_PAGE(pn)	\
	((pn)<<8)

#define FLASH_ADDR_SECTOR(sn)	\
	((sn)<<(2+10))

#define FLASH_ADDR_BLOCK(bn)	\
	((bn)<<16)
// #ifdef __cplusplus  
// extern "C" {  
// #endif  
void flash_set_line_mode(uint8 mode);
void set_flash_qe(void) ;
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
void Flash_Erase(uint32 address,int sel);
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
void Flash_Read(uint32 address, void *buffer, uint32 len);

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
int Flash_CheckBlankPage(uint32 address);

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
int Flash_CheckBlankRange(uint32 address,uint32 sz);


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
char Flash_Write(uint32 address, void*buffer, uint32 len);

// #ifdef __cplusplus  
// }
// #endif  

extern char dFlashEn;

#endif
