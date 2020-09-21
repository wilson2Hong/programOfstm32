#ifndef __BK_DRV_EEPROM_H
#define __BK_DRV_EEPROM_H

/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x.h"
#include "..\bk2471\includes\types.h"
#include "..\bk2471\drivers\flash\flash.h"

#define PAGE_SIZE  (uint16_t)(FLASH_SECTOR_SIZE)
										/* Page size = 256 Byte */
/* EEPROM start address in Flash */
// #define EEPROM_START_ADDRESS    ((uint32_t)0x08010000) /* EEPROM emulation start address:
//                                                   after 64KByte of used Flash memory */

#define EEPROM_START_ADDRESS    ((uint32)FLASH_ADDR_SECTOR(FLASH_TOTAL_SECTOR-1)) 
/* EEPROM emulation start address:the last sector of the Flash memory */

/* Pages 0 and 1 base and end addresses */
#define PAGE0_BASE_ADDRESS      ((uint32_t)(EEPROM_START_ADDRESS + 0x000))
#define PAGE0_END_ADDRESS       ((uint32_t)(EEPROM_START_ADDRESS + (PAGE_SIZE - 1)))

#define PAGE1_BASE_ADDRESS      ((uint32_t)(EEPROM_START_ADDRESS + PAGE_SIZE))
#define PAGE1_END_ADDRESS       ((uint32_t)(EEPROM_START_ADDRESS + (2 * PAGE_SIZE - 1)))

/* Used Flash pages for EEPROM emulation */
#define PAGE0                   ((uint16_t)0x0000)
#define PAGE1                   ((uint16_t)0x0001)

/* No valid page define */
#define NO_VALID_PAGE           ((uint16_t)0x00AB)

/* Page status definitions */
#define ERASED                  (0xFFFFFFFF)     /* PAGE is empty */
#define RECEIVE_DATA            ((uint16_t)0xEEEE)     /* PAGE is marked to receive data */
#define VALID_PAGE              ((uint16_t)0x0000)     /* PAGE containing valid data */

/* Valid pages in read and write defines */
#define READ_FROM_VALID_PAGE    ((uint8_t)0x00)
#define WRITE_IN_VALID_PAGE     ((uint8_t)0x01)

/* Page full define */
#define PAGE_FULL               ((uint8_t)0x80)

/* Variables' number */
#define NumbOfVar               ((uint8_t)25)

#define FLASH_Status		uint16_t

uint16_t EE_Init(void);
uint16_t EE_ReadVariable(uint16_t VirtAddress, uint16_t* Data);
uint16_t EE_WriteVariable(uint16_t VirtAddress, uint16_t Data);
void EE_Show(uint32 addr,uint32 sz);

extern const uint16_t VirtAddVarTab[NumbOfVar];

/*
 *函数名:
 *	WriteFlashUnitProtocol
 *功能:
 *	按数据单元保存数据到flash策略
 *参数:
 *	1.addr:flash地址
 *	2.buf:数据缓冲区
 *	3.len:数据长度
 *返回:
 *	无
 *特殊:
 *	无
*/
void WriteFlashUnitProtocol(UI32 addr,void*buf,UI32 len);

/*
 *函数名:
 *	ReadFlashUnitProtocol
 *功能:
 *	从flash指定地址按数据单元读出数据
 *参数:
 *	1.addr:flash地址
 *	2.buf:数据缓冲区
 *	3.len:数据长度
 *返回:
 *	1=读出数据,0=数据不存在
 *特殊:
 *	无
*/
int ReadFlashUnitProtocol(UI32 addr,void*buf,UI32 len);

#endif /* __EEPROM_H */

