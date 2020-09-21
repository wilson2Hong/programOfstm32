#ifndef _SPI_H_
#define _SPI_H_
#include "..\..\includes\types.h"
#define	BASE_SPI_PTR	\
		0x00f00200
typedef struct HW_SPI{
	union{
		uint32 REG_0x0;
		struct{
			uint32 TXINT_MODE:2;
			//发送中断产生模式;00：即发送FIFO中数据个数少于1个才产生中断;01：即发送FIFO中数据个数少于4个才产生中断;10：即发送FIFO中数据个数少于8个才产生中断;11：即发送FIFO中数据个数少于12个才产生中断
			uint32 RXINT_MODE:2;
			//接收中断产生模式;00：接收FIFO中数据个数超过12个才产生接收中断;01：接收FIFO中数据个数超过8个才产生接收中断;10：接收FIFO中数据个数超过4个才产生接收中断;11：接收FIFO中数据个数超过1个就产生接收中断
			uint32 TXOVR_EN:1;
			//发送溢出(TXOVR)中断告警使能;0：禁止发送溢出中断;1：使能发送溢出中断
			uint32 RXOVR_EN:1;
			//接收溢出(RXOVR)中断告警使能;0：禁止接收溢出中断;1：使能接收溢出中断
			uint32 TXINT_EN:1;
			//发送中断使能
			uint32 RXINT_EN:1;
			//接收中断使能
			uint32 SPI_CKR:8;
			//SPI时钟速率配置
			uint32 NSSMD:2;
			//从选择方式位，选择NSS工作方式：;00：3线从方式或3线主方式。NSS信号不连到端口引脚;01：4线从方式或多主方式（默认值）。NSS总是器件的输入;1x：4线单主方式。NSS被分配一个输出引脚并输出NSSMD0的值;【注意】4线单主模式下，每次传输前软件需要线配置该参数为2’b11后配置成2’b10，传输结束后需要再次配置成2’b11。
			uint32 :16;
			uint32 BIT_WDTH:1;
			//数据位宽;0：8bit;1：16bit
			uint32 NC:1;
			//保留
			uint32 CKPOL:1;
			//SPI时钟极性。;0：SCK在空闲状态处于低电平;1：SCK在空闲状态处于高电平
			uint32 CKPHA:1;
			//SPI时钟相位。;0：在SCK周期的第一个边沿采样数据;1：在SCK周期的第二个边沿采样数据
			uint32 MSTEN:1;
			//主方式允许位。 ;0：从方式    ;1：主方式
			uint32 SPIEN:1;
			//SPI使能位。;0：禁止SPI;1：使能SPI
			uint32 :8;
		};
	};
	union{
		uint32 REG_0x1;
		struct{
			uint32 TXFIFO_EMPTY:1;
			//发送FIFO空志（只读）
			uint32 TXFIFO_FULL:1;
			//发送FIFO满标志（只读）
			uint32 RXFIFO_EMPTY:1;
			//接收FIFO空标志（只读）
			uint32 RXFIFO_FULL:1;
			//接收FIFO满标志（只读）
			uint32 :4;
			uint32 TXINT:1;
			//SPI发送中断标志;该位在发送FIFO的数据个数满足TXINT_MODE的配置值时被硬件置为逻辑1。该位不能被硬件自动清0，必须用软件写1清0。;【注意】该标志位会触发SPI中断
			uint32 RXINT:1;
			//SPI接收中断标志;该位在接收FIFO的数据个数满足RXINT_MODE的配置值时被硬件置为逻辑1。;【注意】该标志位会触发SPI中断
			uint32 MODF:1;
			//方式错误标志;当检测到主方式冲突（NSS为低电平，MSTEN＝1，NSSMD[1:0] = 01）时，该位由硬件置为逻辑1（并产生一个SPI中断）。该位不能被硬件自动清0，必须用软件写1清0。;【注意】该标志位会触发SPI中断
			uint32 TXOVR:1;
			//发送溢出标志。即发送FIFO发生满写错误，会产生一个SPI中断，该位不能被硬件自动清0，必须由软件写1清0。.;【注意】该标志位会触发SPI中断
			uint32 RXOVR:1;
			//接收溢出标志。即接收FIFO发生满写错误，会产生一个SPI中断，该位不能被硬件自动清0，必须由软件写1清0。.;【注意】该标志位会触发SPI中断
			uint32 No Name:1;
			//保留
			uint32 SLVSEL:1;
			//从选择标志位（只读）;当NSS引脚为低电平时，该位被置1，表示SPI时被选中的从器件。当NSS引脚为高时，（未被选中为从器件）该位被清0。该位不指示NSS引脚的即时值，而是该引脚的去噪信号。
			uint32 SPIBUSY:1;
			//SPI忙标志（只读）;0：SPI空闲;1：SPI忙
			uint32 :16;
		};
	};
	union{
		uint32 REG_0x2;
		struct{
			uint32 SPI_DAT:16;
			//SPI数据寄存器;【注意】对该寄存器的写操作对应写发送FIFO，读操作对应读接收FIFO。
			uint32 NC:16;
			//保留
		};
	};
}HW_SPI;

#endif