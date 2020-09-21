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
			//SMBUS���м������ֵ
			uint32 SCL_CR:3;
			//SCL�͵�ƽ��ʱ�������ֵ
			uint32 FREQ_DIV:10;
			//SMBUSʱ�ӷ�Ƶϵ������
			uint32 SLV_ADDR:10;
			//SMBUS�ӵ�ַ
			uint32 SMBCS:2;
			//SMBCS��SMBusʱ��Դѡ��λ�����ڲ���SMBusλ���ʡ�;00����ʱ��0���;01����ʱ��1���;10����ʱ��2���;11���ڲ���Ƶʱ�ӣ���Ƶ�����üĴ���ΪFREQ_DIV��
			uint32 SMBTOE:1;
			//SCL�͵�ƽ��ʱ���ʹ�ܡ�;0����ֹSCL�͵�ƽ��ʱ��⣻;1������SCL��ƽ��ʱ��⡣;��ע�⡿ �����á�1��ʱ��SMBUS���SCL�͵�ƽ�Ƿ�ʱ�����Ĵ���SMB_TMCTL˵��������ʱ�󽫴����жϡ�
			uint32 SMBFTE:1;
			//���߿��м��ʹ��;0����ֹ���߿��м��;1���������߿��м��;��ע�⡿��SMBUS��Ҫ��ΪMasterʹ��ʱ����ʹ�ܱ��뿪����
			uint32 INH:1;
			//SMBUS�ӽ�ֹ���á�����λ������Ϊ�߼���1��ʱ��SMBus�ӿڲ��������¼��жϡ���ʵ�����൱�ڽ�SMBus�������Ƴ����ߡ�����ʽ�жϲ���Ӱ�졣;0��SMBus�ӷ�ʽʹ�ܡ� ;1��SMBus �ӷ�ʽ��ֹ��
			uint32 ENSMB:1;
			//SMBusʹ�����á���λʹ��/��ֹSMBus�ӿڡ�����ʹ��ʱ���ӿ�һֱ����SDA��SCL���š�;0����ֹSMBus�ӿڡ�;1��ʹ��SMBus�ӿڡ�
		};
	};
	union{
		uint32 stat;
		struct{
			uint32 SI:1;
			//SMBus�жϱ�־;0��û���ж���Ҫ��Ӧ;1�����ջ�����ɣ����ж�����Ӧ;��ע�⡿SIֻ��������������SI���á�1��ʱ�� SCL������Ϊ�͵�ƽ��SMBus�����ᡣ
			uint32 SCL_TMOT:1;
			//SCL�͵�ƽ��ʱ��־;0��û�з���SCL�͵�ƽ��ʱ;1������SCL�͵�ƽ��ʱ;��ע�⡿SCL�͵�ƽ��ʱ����ϱ��жϣ������Ҫ��Ӧ�жϲ���λSMBUS���رպ�������
			uint32 :1;
			uint32 ARBLOST:1;
			//��������ʧ��;0��û�з�������ʧ��;1����������ʧ��;��ע�⡿�ϱ���ʷֵ����������
			uint32 RXFIFO_EMPTY:1;
			//����FIFO�ձ�־��ֻ����
			uint32 TXFIFO_FULL:1;
			//����FIFO����־��ֻ����
			uint32 RXINT_MODE:1;
			//�������жϲ�����ʽ;0������FIFO�г���1�����ݲ����жϣ���empty��;1������FIFO�г���8�����ݲ����ж�(almost_full);��ע�⡿����Ϊ��1��ģʽ����ҪԤ�Ƚ�ACK�á�1�����ұ���8��byte�Ĵ������ڡ�����Ҫ�ڷ������ַ��׼��ACK������Ҫ�ڽ������ַ��׼��ACK
			uint32 TXINT_MODE:1;
			//�������жϲ�����ʽ;0������FIFO������1�����ݲ����жϣ�empty��;1������FIFO������8�����ݲ����жϣ�almost_empty��
			uint32 ACK:1;
			//SMBusӦ���־��;д������������Ч��;0��������non-acknowledge����;1��������acknowledge����;��ע�⡿����λ������������㡣��ӦSI�ж��ڼ䣬��ACKRQΪ��1��ʱ�����д�ñ�־λ�������߼����Զ�������non-acknowledge��.;��������������Ч��;0�����յ���non-acknowledge��Ӧ��;1�����յ���acknowledge��Ӧ��
			uint32 STO:1;
			//SMBusֹͣ��־��;д����������ʽ��Ч��;0��������ֹͣ������;1������һ��ֹͣ����;���������ӷ�ʽ��Ч��;0��δ��⵽ֹͣ����;1����⵽ֹͣ������SI��������߼����㣩
			uint32 STA:1;
			//SMBus��ʼ��־��������ʽ��Ч;0����������ʼ������;1�������߿ձ�ʱ���ͳ�һ����ʼ������������æʱ�����ñ����á�1��������һ��ACK����֮�󽫲���һ���ظ���ʼ������    ��ע�⡿��λ�������������������߼��᲻ͣ�ز����ظ���ʼ������
			uint32 ADDR_MATCH:1;
			//�ӵ�ַƥ��ɹ���־�����ӷ�ʽ��Ч��ֻ����;0���ӵ�ַƥ��ʧ��;1���ӵ�ַƥ��ɹ�;��ע�⡿��7bit�ӵ�ַʱ��λ��START�ĵ�һ��byte����£�10bit�ӵ�ַʱ��λ��START�ĵڶ���byte����¡�SI��������߼������;�ӵ�ַ��ƥ��ʱ����������жϡ����Ҵ��������յĵ�ַ����д��FIFO�С�
			uint32 ACKRQ:1;
			//SMBusӦ�����󣬽���������ʽ��Ч��ֻ����;0������Ҫ����ACKӦ��;1����Ҫ����ACKӦ��
			uint32 TXMODE:1;
			//SMBus���ͷ�ʽ��־��ֻ����;0��SMBus�����ڽ�������ʽ��;1��SMBus�����ڷ�������ʽ��
			uint32 MASTER:1;
			//MASTER��SMBus��/�ӱ�־��ֻ����;0��SMBus�����ڴӷ�ʽ��;1��SMBus����������ʽ��
			uint32 BUSY:1;
			//SMBusæ״̬��־��ֻ����;0��SMBUS���ڿ���״̬;1��SMBUS����æ״̬
			uint32 :16;
		};
	};
	union{
		uint32 fifo;
		struct{
			uint32 SMB_DAT:8;
			//SMBUS���ݼĴ���;��ע�⡿�ԸüĴ�����д������Ӧд����FIFO����������Ӧ������FIFO��
			uint32 :24;
		};
	};
}HW_I2C;

typedef struct I2C_CtrlMsg{
	TCallback cbk;			////i2c����ɹ������ص�����
	TCallback fail_cbk;			////i2c����ʧ�ܽ����ص�����
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
 *������:
 *	I2c_Init
 *����:
 *	��ʼ��ָ��i2c
 *����:
 *	1.pn:i2c��
 *	2.dr:ָ��i2c��datarate
 *����:
 *	��
 *����:
 *	1.�ı�:
 *	2.stack:
*/
void I2c_Init(int pn,int dr);

/*
 *������:
 *	I2c_SendBytes
 *����:
 *	ʹ��ָ����i2c�������ݷ���
 *����:
 *	1.md:i2c��+devAddr(ʹ��MAKE_TWI_MODE���ɲ���)
 *	2.addr���Ĵ�����ַ
 *	3.buf��sz����Ҫ���͵����ݻ���ָ��ʹ�С
 *����:
 *	��
 *����:
 *	1.�ı�:
 *	2.stack:
*/
void I2c_SendBytes(int md,uint32 addr,char*buf,uint32 sz);

/*
 *������:
 *	I2c_SendBytes
 *����:
 *	ʹ��ָ����i2c�������ݶ�ȡ
 *����:
 *	1.md:i2c��+devAddr(ʹ��MAKE_TWI_MODE���ɲ���)
 *	2.addr���Ĵ�����ַ
 *	3.buf��sz����Ҫ��ȡ�����ݻ���ָ��ʹ�С
 *����:
 *	��
 *����:
 *	1.�ı�:
 *	2.stack:
*/
void I2c_RcvBytes(int md,uint32 addr,char*buf,uint32 sz);

/*
 *������:
 *	I2c_StartRcvBytes
 *����:
 *	����ָ����i2c�������ݽ���
 *����:
 *	1.md:i2c��+devAddr(ʹ��MAKE_TWI_MODE���ɲ���)
 *	2.addr���Ĵ�����ַ
 *	3.buf��sz����Ҫ��ȡ�����ݻ���ָ��ʹ�С
 *	4.cbk:i2c����ɹ��ص������������NULL����ָ��
 *	5.fail_cbk:i2c����ʧ�ܻص������������NULL����ָ��
 *����:
 *	��
 *����:
 *	1.�ı�:
 *	2.stack:
*/
void I2c_StartRcvBytes(int md,uint32 addr,char*buf,uint32 sz,TCallback cbk,TCallback fail_cbk);

/*
 *������:
 *	I2c_StartSendBytes
 *����:
 *	����ָ����i2c�������ݷ���
 *����:
 *	1.md:i2c��+devAddr(ʹ��MAKE_TWI_MODE���ɲ���)
 *	2.addr���Ĵ�����ַ
 *	3.buf��sz����Ҫ��ȡ�����ݻ���ָ��ʹ�С
 *	4.cbk:i2c����ɹ��ص������������NULL����ָ��
 *	5.fail_cbk:i2c����ʧ�ܻص������������NULL����ָ��
 *����:
 *	��
 *����:
 *	1.�ı�:
 *	2.stack:
*/
void I2c_StartSendBytes(int md,uint32 addr,char*buf,uint32 sz,TCallback cbk,TCallback fail_cbk);

/*
 *������:
 *	I2c_WaitDone
 *����:
 *	�ȴ�i2c�������
 *����:
 *	1.pn:i2c��
 *����:
 *	��
 *����:
 *	1.�ı�:
 *	2.stack:
*/
void I2c_WaitDone(int pn);

/*
 *������:
 *	I2c_GetErrorStatus
 *����:
 *	��ȡi2c����������
 *����:
 *	1.pn:i2c��
 *����:
 *	������룺0=����������>0=����ʧ�ܴ���
 *����:
 *	1.�ı�:
 *	2.stack:
*/
int I2c_GetErrorStatus(int pn);
// #ifdef __cplusplus  
// }
// #endif  

#endif
