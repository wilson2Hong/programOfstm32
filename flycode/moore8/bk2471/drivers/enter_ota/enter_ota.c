#include <stdio.h>
#include "..\wdt\wdt.h"
#include "..\flash\flash.h"
#include "..\uart\uart.h"

// #define AHB_ICU_BASE             0x00800000
// #define APB_WDT_BASE             0x00F00000
// #define REG_AHB0_ICU_WDTCLKCON             (*((volatile unsigned long *)(AHB_ICU_BASE + 0x1c) ))
// #define REG_APB0_WDT_CFG                (*((volatile unsigned long *)APB_WDT_BASE))
void udi_wdt_enable(uint16 wdt_cnt)
{
	//the timer is 48uS @1 CLK
	//0xffff: 3s
	REG_AHB0_ICU_WDTCLKCON = 0x0 ; // Step1. WDT clock enable,16M
	REG_APB0_WDT_CFG  = wdt_cnt;   // Step2. Set WDT period=0xFF

	// Do two things together: 1. Set WDT period. 2. Write WDT key to feed dog.
	// Write WDT key: 0x5A firstly and 0xA5 secondly.
	REG_APB0_WDT_CFG = (0x5A<<16) + wdt_cnt;
	REG_APB0_WDT_CFG = (0xA5<<16) + wdt_cnt;
}

void HwSoftReset(void){
	udi_wdt_enable(1);
	while(1);
}

//进入空中升级程序
void Enter_OTA(){
	uint32 val=0x0;
	uint32 valt=0x87;
//	printf("enter_ota\r\n");
	uart_wait_for_txEnd();
	//Delay_ms(100);
	//写flash[0x41800]=0
	//关中断
	ICU_DisableFIQ(BASE_ICU_PTR);
	ICU_DisableIRQ(BASE_ICU_PTR);
	//切换到1线模式
	Flash_Read(0x41800,&valt,sizeof(val));
	if(valt!=0){
		flash_set_line_mode(1);
		Flash_Erase(0x41800,0);
		Flash_Write(0x41800,&val,sizeof(val));
	}
	Flash_Read(0x41800,&valt,sizeof(val));
	//printf("0x%.8x\r\n",valt);
	print_i_hex(valt);
	print_newline();
	//reset
	udi_wdt_enable(1);
	while(1);
}

