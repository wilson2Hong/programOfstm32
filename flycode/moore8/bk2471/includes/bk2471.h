#ifndef _BK_2471_H_
#define _BK_2471_H_

#define BIT_0               0x00000001
#define BIT_1               0x00000002
#define BIT_2               0x00000004
#define BIT_3               0x00000008
#define BIT_4               0x00000010
#define BIT_5               0x00000020
#define BIT_6               0x00000040
#define BIT_7               0x00000080
#define BIT_8               0x00000100
#define BIT_9               0x00000200
#define BIT_10              0x00000400
#define BIT_11              0x00000800
#define BIT_12              0x00001000
#define BIT_13              0x00002000
#define BIT_14              0x00004000
#define BIT_15              0x00008000
#define BIT_16              0x00010000
#define BIT_17              0x00020000
#define BIT_18              0x00040000
#define BIT_19              0x00080000
#define BIT_20              0x00100000
#define BIT_21              0x00200000
#define BIT_22              0x00400000
#define BIT_23              0x00800000
#define BIT_24              0x01000000
#define BIT_25              0x02000000
#define BIT_26              0x04000000
#define BIT_27              0x08000000
#define BIT_28              0x10000000
#define BIT_29              0x20000000
#define BIT_30              0x40000000
#define BIT_31              0x80000000

/////////////////////////////////////////////////////////////////////////////
//memory layout
/////////////////////////////////////////////////////////////////////////////
#define ROM_START_ADDR				0x00000000
#define RAM_START_ADDR				0x00400000

#define AHB_ICU_BASE				0x00800000
#define AHB_BK24_BASE				0x00810000
#define AHB_FLASH_BASE				0x00820000
#define AHB_AHB2APB_BASE			0x00F00000

#define APB_WDT_BASE				0x00F00000
#define APB_PWM_BASE				0x00F00100
#define APB_SPI_BASE				0x00F00200
#define APB_UART_BASE				0x00F00300
#define APB_I2C_BASE				0x00F00400
#define APB_GPIO_BASE				0x00F00500
#define APB_RTC_BASE				0x00F00600
#define APB_ADC_BASE				0x00F00700
#define APB_3DS_BASE				0x00F00800
#define APB_I2C1_BASE				0x00F00900
#define APB_TIMER_BASE				0x00F00A00
#define APB_XVER_BASE				0x00F10000
#define APB_CEVA_BASE				0x00F20000
#define BK2471_XVR_BASE_ADDR		0x00F10000
#define p_AHB0_ICU_BASE				(*((volatile unsigned long *)  0x00800000))
#define p_AHB1_CEVA_BASE			(*((volatile unsigned long *)  0x00801000))
#define p_AHB3_MFC_BASE				(*((volatile unsigned long *)  0x00803000))
#define p_AHB6_AHB2APB_BASE			(*((volatile unsigned long *)  0x00806000))

//=====================================================================================
#define REG32(x)            (*((volatile uint32 *)(x)))
#define GET_REG_ADDR(x)		(((uint32)(&(x))))
#endif
