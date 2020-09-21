#ifndef _I2C0_H_
#define _I2C0_H_
#include "..\..\includes\types.h"
#define	BASE_I2C0_PTR	\
		((HW_I2C*)0x00f00400)


#define	BASE_I2C1_PTR	\
		((HW_I2C*)0x00f00900)

//=====================================================================================
//IIC1
//=====================================================================================
#define REG_APB4_I2C1_CN                 (*((volatile unsigned long *)   (APB_I2C1_BASE + 0x00) ))
#define REG_APB4_I2C1_STAT               (*((volatile unsigned long *)   (APB_I2C1_BASE + 0x04) ))
#define REG_APB4_I2C1_DAT                (*((volatile unsigned long *)   (APB_I2C1_BASE + 0x08) ))

#define I2C1_INTR_BIT                    (0x01<<9)
#define I2C1_INTR_TX                     (0x01<<1)
//=====================================================================================
// I2C config register bit mapping
#define BIT_I2C_ENSMB                   31
#define BIT_I2C_INH                     30
#define BIT_I2C_SMBFTE                  29
#define BIT_I2C_SMBTOE                  28
#define BIT_I2C_SMBCS                   26
#define BIT_I2C_SLV_ADDR                16
#define BIT_I2C_FREQ_DIV                6
#define BIT_I2C_SCL_CR                  3
#define BIT_I2C_IDLE_CR                 0

#define I2C0 \
    0

#define I2C1 \
    1


#pragma anon_unions
typedef struct HW_I2C{
	union{
		uint32 cfg;
		struct{
			uint32 IDLE_CR:3;
			//SMBUS空闲检测门限值
			uint32 SCL_CR:3;
			//SCL低电平超时检测门限值
			uint32 FREQ_DIV:10;
			//SMBUS时钟分频系数配置
			uint32 SLV_ADDR:10;
			//SMBUS从地址
			uint32 SMBCS:2;
			//SMBCS：SMBus时钟源选择位，用于产生SMBus位速率。;00：定时器0溢出;01：定时器1溢出;10：定时器2溢出;11：内部分频时钟（分频比配置寄存器为FREQ_DIV）
			uint32 SMBTOE:1;
			//SCL低电平超时检测使能。;0：禁止SCL低电平超时检测；;1：允许SCL电平超时检测。;【注意】 当被置‘1’时，SMBUS检测SCL低电平是否超时（见寄存器SMB_TMCTL说明），超时后将触发中断。
			uint32 SMBFTE:1;
			//总线空闲检测使能;0：禁止总线空闲检测;1：允许总线空闲检测;【注意】若SMBUS需要作为Master使用时，该使能必须开启。
			uint32 INH:1;
			//SMBUS从禁止配置。当该位被设置为逻辑‘1’时，SMBus接口不产生从事件中断。这实际上相当于将SMBus从器件移出总线。主方式中断不受影响。;0：SMBus从方式使能。 ;1：SMBus 从方式禁止。
			uint32 ENSMB:1;
			//SMBus使能配置。该位使能/禁止SMBus接口。当被使能时，接口一直监视SDA和SCL引脚。;0：禁止SMBus接口。;1：使能SMBus接口。
		};
	};
	union{
		uint32 stat;
		struct{
			uint32 SI:1;
			//SMBus中断标志;0：没有中断需要响应;1：接收或发送完成，有中断需响应;【注意】SI只能用软件清除。当SI被置‘1’时， SCL被保持为低电平，SMBus被冻结。
			uint32 SCL_TMOT:1;
			//SCL低电平超时标志;0：没有发生SCL低电平超时;1：发生SCL低电平超时;【注意】SCL低电平超时后会上报中断，软件需要响应中断并复位SMBUS（关闭后重启）
			uint32 :1;
			uint32 ARBLOST:1;
			//多主竞争失败;0：没有发生竞争失败;1：发生竞争失败;【注意】上报历史值，由软件清除
			uint32 RXFIFO_EMPTY:1;
			//接收FIFO空标志（只读）
			uint32 TXFIFO_FULL:1;
			//发送FIFO满标志（只读）
			uint32 RXINT_MODE:1;
			//接收器中断产生方式;0：接收FIFO中超过1个数据产生中断（非empty）;1：接收FIFO中超过8个数据产生中断(almost_full);【注意】配置为’1’模式下需要预先将ACK置’1’，且保持8个byte的传输周期。主需要在发送完地址后准备ACK，从需要在接收完地址后准备ACK
			uint32 TXINT_MODE:1;
			//发送器中断产生方式;0：发送FIFO中少于1个数据产生中断（empty）;1：发送FIFO中少于8个数据产生中断（almost_empty）
			uint32 ACK:1;
			//SMBus应答标志。;写：（接收器有效）;0：发出“non-acknowledge”，;1：发出“acknowledge”。;【注意】：该位必须由软件清零。响应SI中断期间，若ACKRQ为’1’时软件需写该标志位，否则逻辑会自动发出“non-acknowledge”.;读：（发送器有效）;0：接收到“non-acknowledge”应答;1：接收到“acknowledge”应答
			uint32 STO:1;
			//SMBus停止标志，;写：（仅主方式有效）;0：不产生停止条件。;1：产生一个停止条件;读：（仅从方式有效）;0：未检测到停止条件;1：检测到停止条件（SI清除后由逻辑清零）
			uint32 STA:1;
			//SMBus起始标志，仅主方式有效;0：不产生起始条件。;1：待总线空闭时发送出一个起始条件。若总线忙时，将该比特置‘1’，在下一个ACK周期之后将产生一个重复起始条件。    【注意】该位必须由软件清除，否则逻辑会不停地产生重复起始条件。
			uint32 ADDR_MATCH:1;
			//从地址匹配成功标志，仅从方式有效（只读）;0：从地址匹配失败;1：从地址匹配成功;【注意】：7bit从地址时该位在START的第一个byte后更新，10bit从地址时该位在START的第二个byte后更新。SI清除后由逻辑清除。;从地址不匹配时，不会产生中断。而且从器件接收的地址不会写入FIFO中。
			uint32 ACKRQ:1;
			//SMBus应答请求，仅接收器方式有效（只读）;0：不需要发送ACK应答;1：需要发送ACK应答
			uint32 TXMODE:1;
			//SMBus发送方式标志（只读）;0：SMBus工作在接收器方式。;1：SMBus工作在发送器方式。
			uint32 MASTER:1;
			//MASTER：SMBus主/从标志（只读）;0：SMBus工作在从方式。;1：SMBus工作在主方式。
			uint32 BUSY:1;
			//SMBus忙状态标志（只读）;0：SMBUS处于空闲状态;1：SMBUS处于忙状态
			uint32 :16;
		};
	};
	union{
		uint32 fifo;
		struct{
			uint32 SMB_DAT:8;
			//SMBUS数据寄存器;【注意】对该寄存器的写操作对应写发送FIFO，读操作对应读接收FIFO。
			uint32 :24;
		};
	};
}HW_I2C;

typedef struct I2C_CtrlMsg{
	TCallback cbk;			////i2c传输成功结束回调函数
	TCallback fail_cbk;			////i2c传输失败结束回调函数
	uint32 Mode:1;			////0:Wirte, 1:Read
	uint32 BusyFlag:1;		////0:Idle, 1:In Used
	uint32 TransDone:1;	////0:In process, 1:Done
	uint32 WorkingState:4;	////0:Idle, 1:Start+Addr(W), 2:RegIndex, 3:Write Data, 4:Stop
	////5:Start+Addr(R), 6:Read Data, 7:Stop
	uint32 DataLength:6;	////Tx/Rx Data Length
	uint32 OpResult:3;		////0:Pass, 1:fail
	//uint32 reserved:2;
	uint32 SlaveAddr:8;	////Slave Address
	uint32 RegIndex:8;		//// Slave Register Index
	uint8 DataIndex;		////Index of buf
	uint8 *Rxbuf;			////Rx Data buf
	uint8 *Txbuf;			////Tx Data buf
} _I2C_CtrlMsg;

#define I2CM_CLK_SRC			16000000l
#define I2CM_TAR_FREQ		400000

#define I2CM_SEL_PN(pn) \
    (((pn)==I2C0)?(BASE_I2C0_PTR):(BASE_I2C1_PTR))

#define I2CM_SetupIO(pn) \
    {\
    GPIO_SetSF((((pn)==I2C0)?GPIOC : GPIOB),(((pn)==I2C0)?(BIT(2)|BIT(3)) : (BIT(6)|BIT(7))));\
	GPIO_EnablePU((((pn)==I2C0)?GPIOC : GPIOB),(((pn)==I2C0)?(BIT(2)|BIT(3)) : (BIT(6)|BIT(7))));\
    }


#define I2CM_OPEN_CLOCK(pn) \
	{BASE_ICU_PTR->i2c &= _BIT(pn*16);}

#define I2CM_CALC_PRES(freq) \
    ((I2CM_CLK_SRC/(freq)/3)-1)

#define I2CM_Setup(pn,freq) \
    {\
    I2CM_SEL_PN(pn)->FREQ_DIV = (I2CM_CALC_PRES(freq));\
	}

#define I2CM_Open(pn) \
    {\
    I2CM_SEL_PN(pn)->cfg |= BIT(31);\
    }

#define I2CM_CLOSE_CLOCK(pn) \
	{BASE_ICU_PTR->i2c |= BIT(pn*16);}

#define I2CM_CLOSE(pn) \
	{\
	I2CM_SEL_PN(pn)->cfg &= _BIT(31);\
	I2CM_CLOSE_CLOCK();\
	}

#define MAKE_TWI_MODE(devAddr,pn)	\
	MAKE_I2C_MODE(devAddr,pn)

#define MAKE_I2C_MODE(devAddr,pn)	\
	((0)|\
	BFD(devAddr,0,7)|	\
	BFD(pn,8,8)|		\
	0)
#define HwTwiRecieveData	\
	I2c_RcvBytes

#define HwTwiSendData		\
	I2c_SendBytes

// #ifdef __cplusplus  
// extern "C" {  
// #endif  

/*
 *函数名:
 *	I2c_Init
 *功能:
 *	初始化指定i2c
 *参数:
 *	1.pn:i2c号
 *	2.dr:指定i2c的datarate
 *返回:
 *	无
 *特殊:
 *	1.改变:
 *	2.stack:
*/
void I2c_Init(int pn,int dr);

/*
 *函数名:
 *	I2c_SendBytes
 *功能:
 *	使用指定的i2c进行数据发送
 *参数:
 *	1.md:i2c号+devAddr(使用MAKE_TWI_MODE生成参数)
 *	2.addr：寄存器地址
 *	3.buf，sz：将要发送的数据缓冲指针和大小
 *返回:
 *	无
 *特殊:
 *	1.改变:
 *	2.stack:
*/
void I2c_SendBytes(int md,uint32 addr,char*buf,uint32 sz);

/*
 *函数名:
 *	I2c_SendBytes
 *功能:
 *	使用指定的i2c进行数据读取
 *参数:
 *	1.md:i2c号+devAddr(使用MAKE_TWI_MODE生成参数)
 *	2.addr：寄存器地址
 *	3.buf，sz：将要读取的数据缓冲指针和大小
 *返回:
 *	无
 *特殊:
 *	1.改变:
 *	2.stack:
*/
void I2c_RcvBytes(int md,uint32 addr,char*buf,uint32 sz);

/*
 *函数名:
 *	I2c_StartRcvBytes
 *功能:
 *	启动指定的i2c进行数据接收
 *参数:
 *	1.md:i2c号+devAddr(使用MAKE_TWI_MODE生成参数)
 *	2.addr：寄存器地址
 *	3.buf，sz：将要读取的数据缓冲指针和大小
 *	4.cbk:i2c传输成功回调函数，如果是NULL，则不指定
 *	5.fail_cbk:i2c传输失败回调函数，如果是NULL，则不指定
 *返回:
 *	无
 *特殊:
 *	1.改变:
 *	2.stack:
*/
void I2c_StartRcvBytes(int md,uint32 addr,char*buf,uint32 sz,TCallback cbk,TCallback fail_cbk);

/*
 *函数名:
 *	I2c_StartSendBytes
 *功能:
 *	启动指定的i2c进行数据发送
 *参数:
 *	1.md:i2c号+devAddr(使用MAKE_TWI_MODE生成参数)
 *	2.addr：寄存器地址
 *	3.buf，sz：将要读取的数据缓冲指针和大小
 *	4.cbk:i2c传输成功回调函数，如果是NULL，则不指定
 *	5.fail_cbk:i2c传输失败回调函数，如果是NULL，则不指定
 *返回:
 *	无
 *特殊:
 *	1.改变:
 *	2.stack:
*/
void I2c_StartSendBytes(int md,uint32 addr,char*buf,uint32 sz,TCallback cbk,TCallback fail_cbk);

/*
 *函数名:
 *	I2c_WaitDone
 *功能:
 *	等待i2c传输结束
 *参数:
 *	1.pn:i2c号
 *返回:
 *	无
 *特殊:
 *	1.改变:
 *	2.stack:
*/
void I2c_WaitDone(int pn);

/*
 *函数名:
 *	I2c_GetErrorStatus
 *功能:
 *	获取i2c传输错误代码
 *参数:
 *	1.pn:i2c号
 *返回:
 *	错误代码：0=正常结束，>0=操作失败代码
 *特殊:
 *	1.改变:
 *	2.stack:
*/
int I2c_GetErrorStatus(int pn);
// #ifdef __cplusplus  
// }
// #endif  

#endif
