#include<stdio.h>
#include "i2c0.h"
#include "..\gpio\gpio.h"
#include "..\icu\icu.h"

_I2C_CtrlMsg s_I2C0_CtrlMsg;
_I2C_CtrlMsg s_I2C1_CtrlMsg;

void I2C0_IE(int inte){
	HW_ICU *icu=BASE_ICU_PTR;
	if(inte){
		icu->i2c0_int_en= 1;
	}else {
		icu->i2c0_int_en = 0;
	}
	icu->i2c0_wakeup_en= 0;
	////Clr Int Flag
	icu->INT_FLAG  |= BIT(8);
}

void I2C_IE(int pn,int inte){
	HW_ICU *icu=BASE_ICU_PTR;
	uint32 p;
	if(pn==I2C0)p=PID_I2C0;
	else p=PID_I2C1;
	if(inte){
		icu->INT_EN |= BIT(p);
	}else {
		icu->INT_EN &= _BIT(p);
	}
	icu->INT_EN &= ~((BIT(PID_I2C0)|BIT(PID_I2C1))<<16);

	////Clr Int Flag
	icu->INT_FLAG  = BIT(p);
}

void I2c_Init(int pn,int dr){
	HW_I2C*i2c= I2CM_SEL_PN(pn);
	I2CM_SetupIO(pn);			//设定i2c相关io
	I2CM_OPEN_CLOCK(pn);		//打开i2c时钟
	i2c->cfg =
		BFD(I2CM_CALC_PRES(dr), 6, 10)|//波特率
		BFD(1, 29, 1)|		//smb从模式开关
		BFD(1, 28, 1)|		//smb空闲检测开关
		BFD(3, 26, 2)|		//scl时钟源:0-2=定时器n溢出信号,3=内部分频
		BFD(0, 16, 10)|		//slave地址:master无效
		BFD(4, 3, 3)|		//scl低电平超时
		BFD(3, 0, 3);		//idle条件
	//启动i2c
	i2c->cfg |= (0x80000000);
	
	i2c->stat = BFD(3,6,2);
}

void I2c_SendBytes(int md,uint32 addr,char*buf,uint32 sz){
	I2c_StartSendBytes(md,addr,buf,sz,NULL,NULL);
	I2c_WaitDone(GET_BFD(md,8,8));
}

void I2c_RcvBytes(int md,uint32 addr,char*buf,uint32 sz){
	I2c_StartRcvBytes(md,addr,buf,sz,NULL,NULL);
	I2c_WaitDone(GET_BFD(md,8,8));
}

#if 0
void I2c_SendBytes(int md,uint32 addr,char*buf,uint32 sz){
	volatile HW_I2C *i2c=(volatile HW_I2C*)I2CM_SEL_PN(GET_BFD(md,8,8));
	uint32 devAddr7=GET_BFD(md,0,7);
	uint32 i,stat;
	//2471的I2C支持16B的FIFO
	i2c->stat &= _BFD(3, 6, 2);
	i2c->stat |= BFD(3, 6, 2);
	i2c->SMB_DAT = (devAddr7<<1);
	i2c->STA = 1;
	while(i2c->SI==0);
	i2c->STA = 0;
	i2c->cfg &= _BIT(26);//将TIMER2作为切换的SCL的时钟源，为解最高位从1变0的硬件bug
	i2c->SMB_DAT = addr;
	i2c->SI = 0;
	i2c->cfg |= BIT(26);//将内部时钟作为切换的SCL的时钟源，为解最高位从1变0的硬件bug

	for(i=0;i<sz;i++){
		i2c->SMB_DAT = buf[i];
	}

	for(i=0;i<=sz;i++){
		while(i2c->SI==0);
		i2c->cfg &= _BIT(26);//将TIMER2作为切换的SCL的时钟源，为解最高位从1变0的硬件bug
		stat = i2c->stat;
		if(i==sz){
			stat |=BIT(9);
		}
		stat &=_BIT(0);
		i2c->stat = stat;
		i2c->cfg |= BIT(26);//将内部时钟作为切换的SCL的时钟源，为解最高位从1变0的硬件bug
	}
}

void I2c_RcvBytes(int md,uint32 addr,char*buf,uint32 sz){
	volatile HW_I2C *i2c=(volatile HW_I2C*)I2CM_SEL_PN(GET_BFD(md,8,8));
	uint32 devAddr7=GET_BFD(md,0,7);
	//uint32 i;
	uint32 stat;
	//注:STA为1时，i2c总线空闲时，master就发送SB。
	//发送:SB|AD+W|
	i2c->stat &= _BFD(3, 6, 2);
	i2c->stat |= BFD(3, 6, 2);
	i2c->SMB_DAT = ((devAddr7<<1));
	i2c->STA = 1;
	while(i2c->SI==0);
	i2c->cfg &= _BIT(26);//将TIMER2作为切换的SCL的时钟源，为解最高位从1变0的硬件bug
	//stat =i2c->stat;

	i2c->STA = 0;
	//发送|RA|
	i2c->SMB_DAT = addr;
	i2c->SI = 0;
	i2c->cfg |= BIT(26);//将内部时钟作为切换的SCL的时钟源，为解最高位从1变0的硬件bug
	while(i2c->SI==0);
	stat = i2c->stat;
	//发送SB|AD+R|
	i2c->SMB_DAT =((devAddr7<<1)|1);
	stat |= (BIT(10)|BIT(8));
	stat &= _BIT(0);
	i2c->stat = stat;

	i2c->STA = 0;

	while(i2c->SI==0);
	stat = i2c->stat;
	stat |= BFD(3, 6, 2);
	if(stat & BIT(12)){
		stat |= BIT(8);
	}
	stat &= (~(BIT(10)|BIT(0)));
	i2c->stat =stat;

	while(sz){
		while(i2c->SI==0);
		stat= i2c->stat;
		if(sz==1){
			stat &= _BIT(8);
			stat |=BIT(9);
		}else{
			stat |=BIT(8);
		}
		stat &=_BIT(0);
		i2c->stat = stat;
		*buf++ = i2c->SMB_DAT ;
		sz--;
	}
}
#endif
#if 0
//BUG：该版本下，2471在某些情况下字节的最高位会从1变0
void I2c_SendBytes(int md,uint32 addr,char*buf,uint32 sz){
	volatile HW_I2C *i2c=(volatile HW_I2C*)I2CM_SEL_PN(GET_BFD(md,8,8));
	uint32 devAddr7=GET_BFD(md,0,7);
	uint32 i,stat;
	//2471的I2C支持16B的FIFO
	i2c->stat &= _BFD(3, 6, 2);
	i2c->stat |= BFD(3, 6, 2);
	i2c->SMB_DAT = (devAddr7<<1);
	i2c->SMB_DAT = addr;
	i2c->STA = 1;
	while(i2c->SI==0);
	for(i=0;i<sz;i++){
		i2c->SMB_DAT = buf[i];
	}
	i2c->STA = 0;
	i2c->SI = 0;

	for(i=0;i<=sz;i++){
		while(i2c->SI==0);
		stat = i2c->stat;
		if(i==sz){
			stat |=BIT(9);
		}
		stat &=_BIT(0);
		i2c->stat = stat;
	}
}

void I2c_RcvBytes(int md,uint32 addr,char*buf,uint32 sz){
	volatile HW_I2C *i2c=(volatile HW_I2C*)I2CM_SEL_PN(GET_BFD(md,8,8));
	uint32 devAddr7=GET_BFD(md,0,7);
	uint32 i;
	uint32 stat;
	//注:STA为1时，i2c总线空闲时，master就发送SB。
	//发送:SB|AD+W|
	i2c->stat &= _BFD(3, 6, 2);
	i2c->stat |= BFD(3, 6, 2);
	i2c->SMB_DAT = ((devAddr7<<1));
	i2c->STA = 1;
	while(i2c->SI==0);
	//stat =i2c->stat;

	i2c->STA = 0;
	//发送|RA|
	i2c->SMB_DAT = addr;
	i2c->SI = 0;
	while(i2c->SI==0);
	stat = i2c->stat;
	//发送SB|AD+R|
	i2c->SMB_DAT =((devAddr7<<1)|1);
	stat |= (BIT(10)|BIT(8));
	stat &= _BIT(0);
	i2c->stat = stat;

	i2c->STA = 0;

	while(i2c->SI==0);
	stat = i2c->stat;
	stat |= BFD(3, 6, 2);
	if(stat & BIT(12)){
		stat |= BIT(8);
	}
	stat &= (~(BIT(10)|BIT(0)));
	i2c->stat =stat;

	while(sz){
		while(i2c->SI==0);
		stat= i2c->stat;
		if(sz==1){
			stat &= _BIT(8);
			stat |=BIT(9);
		}else{
			stat |=BIT(8);
		}
		stat &=_BIT(0);
		i2c->stat = stat;
		*buf++ = i2c->SMB_DAT ;
		sz--;
	}
}
#endif

void I2c_StartSendBytes(int md,uint32 addr,char*buf,uint32 sz,TCallback cbk,TCallback fail_cbk){
	int pn=GET_BFD(md,8,8);
	volatile HW_I2C *i2c=(volatile HW_I2C*)I2CM_SEL_PN(pn);
	_I2C_CtrlMsg *pmsg=((pn==I2C0)?&s_I2C0_CtrlMsg:&s_I2C1_CtrlMsg);

	////If have to check bus busy first ????
	//I2C0_IE(0);
	I2C_IE(pn,0);
	pmsg->cbk=cbk;
	pmsg->fail_cbk=fail_cbk;
	pmsg->BusyFlag = 1;
	pmsg->DataIndex = 0;
	pmsg->DataLength = sz;
	pmsg->Mode = 0;	////write
	pmsg->RegIndex = (uint8)addr;
	pmsg->SlaveAddr = (uint8)GET_BFD(md,0,7)/*md*/;
	pmsg->Rxbuf = (uint8 *)buf;
	pmsg->Txbuf = (uint8 *)buf;
	pmsg->OpResult = 0;	////Pass
	pmsg->TransDone = 0;
	pmsg->WorkingState=1;
	i2c->SI = 0;
	//I2C0_IE(1);
	I2C_IE(pn,1);
	i2c->stat &= _BFD(3, 6, 2);
	i2c->stat |= BFD(3, 6, 2);
	i2c->fifo = ((pmsg->SlaveAddr<<1));
	i2c->STA = 1;		////Generate START + Addr(W)
}

void I2c_StartRcvBytes(int md,uint32 addr,char*buf,uint32 sz,TCallback cbk,TCallback fail_cbk){
	int pn=GET_BFD(md,8,8);
	volatile HW_I2C *i2c=(volatile HW_I2C*)I2CM_SEL_PN(pn);
	_I2C_CtrlMsg *pmsg=((pn==I2C0)?&s_I2C0_CtrlMsg:&s_I2C1_CtrlMsg);

	////If have to check bus busy first ????
	//I2C0_IE(0);
	I2C_IE(pn,0);
	pmsg->cbk=cbk;
	pmsg->fail_cbk=fail_cbk;
	pmsg->BusyFlag = 1;
	pmsg->DataIndex = 0;
	pmsg->DataLength = sz;
	pmsg->Mode = 1;	////Read
	pmsg->RegIndex = (uint8)addr;
	pmsg->SlaveAddr = (uint8)GET_BFD(md,0,7)/*md*/;
	pmsg->Rxbuf = (uint8 *)buf;
	pmsg->Txbuf = (uint8 *)buf;
	pmsg->OpResult = 0;	////Pass
	pmsg->TransDone = 0;
	pmsg->WorkingState=1;
	i2c->SI = 0;
	//I2C0_IE(1);
	I2C_IE(pn,1);
	i2c->stat &= _BFD(3, 6, 2);
	i2c->stat |= BFD(3, 6, 2);
	i2c->fifo = ((pmsg->SlaveAddr<<1));
	i2c->STA = 1;		////Generate START + Addr(W)
}
void I2c_isr(int pn){
	volatile HW_I2C*i2c=((pn==I2C0)?BASE_I2C0_PTR:BASE_I2C1_PTR);
	_I2C_CtrlMsg *pmsg=((pn==I2C0)?&s_I2C0_CtrlMsg:&s_I2C1_CtrlMsg);
	//volatile HW_I2C *i2c=BASE_I2C0_PTR;
	i2c->cfg&=_BIT(26);
	uint32 state = i2c->stat;
	switch(pmsg->WorkingState)
	{
	case 1:		////Start+Addr(W)
		if(i2c->ACK==1){////Rx Slave Ack
			i2c->fifo = pmsg->RegIndex;
			////Clr STA,  SI and trigger
			state&=0xFFFFFBFE;
			i2c->stat = state;
			pmsg->DataIndex = 0;
			pmsg->WorkingState = 2;
		}else{//// No Slave Ack
			pmsg->OpResult = 1;
		}
		break;

	case 2:		////RegIndex
		if(i2c->ACK==1)	{////Rx Slave Ack
			if(pmsg->Mode==0){////Write
				if(pmsg->DataIndex == pmsg->DataLength){
					pmsg->WorkingState = 4;
					////Set STO
					state |= BIT(9);
				}else{
					pmsg->WorkingState = 3;
					i2c->fifo = pmsg->Txbuf[pmsg->DataIndex];
					pmsg->DataIndex++;
				}
			}else{////Read
				i2c->fifo = (pmsg->SlaveAddr<<1)+1;
				pmsg->WorkingState = 5;
				////Set STA
				state |= (BIT(10)|BIT(8));
			}
			////Clr SI & trigger
			state &= _BIT(0);
			i2c->stat = state;
		}else{//// No Slave Ack
			pmsg->OpResult = 2;
		}
		break;

	case 3:		////WriteData
		if(i2c->ACK==1){////Rx Slave Ack
			if(pmsg->DataIndex == pmsg->DataLength){
// 				pmsg->WorkingState = 4;
				pmsg->BusyFlag = 0;
				pmsg->TransDone = 1;
				I2C0_IE(0);
				////Set STO
				state |= BIT(9);
			}else{
				i2c->fifo = pmsg->Txbuf[pmsg->DataIndex];
				pmsg->DataIndex++;
			}
			////Clr SI & trigger
			state &= _BIT(0);
			i2c->stat = state;
		}else{//// No Slave Ack
			pmsg->OpResult = 3;
		}
		break;

	case 4:		////Stop
		////Clr STA, STO, SI
		i2c->stat &= 0xFFFFF9FE;
		pmsg->BusyFlag = 0;
		pmsg->TransDone = 1;
		I2C_IE(pn,0);
		break;

	case 5:		////Start+Addr(R)
		if(i2c->ACK==1){////Rx Slave Ack
			pmsg->DataIndex = 0;
			////How To Trigger Read ???
// 			if( (0 == pmsg->DataLength)
// 				|| ((pmsg->DataIndex+1) == pmsg->DataLength)){////Last Byte
// 				pmsg->WorkingState = 7;
// 				////Set STO
// 				//state &=_BIT(8);
// 				state |= BIT(9);
// 			}else{
// 				pmsg->WorkingState = 6;
// 				if((i2c->stat) & BIT(12)){////Request Ack
// 					////Set ACK
// 					state |= BIT(8);
// 				}
// 			}
// 			////Clr STA, SI & trigger
// 			state &= ~(BIT(10)|BIT(0));
// 			i2c->stat = state;

			pmsg->WorkingState = 6;
			state = i2c->stat;
			state |= BFD(3, 6, 2);
			if(state & BIT(12)){
				state |= BIT(8);
			}
			state &= (~(BIT(10)|BIT(0)));
			i2c->stat =state;
		}else{//// No Slave Ack
			pmsg->OpResult = 4;
		}
		break;

	case 6:		////Read Data
		if(i2c->ACKRQ==1){////Rx Ack request
			if((pmsg->DataIndex+1) == pmsg->DataLength){
				pmsg->BusyFlag = 0;
				pmsg->TransDone = 1;
				////Stop I2C0 INT
				I2C_IE(pn,0);
				//// Clr  ACK
				state &= _BIT(8);
				////Set STO
				state |= BIT(9);
			}else{
				////Set ACK
				state |= BIT(8);
			}
			////Clr SI & trigger
			state &= _BIT(0);
			i2c->stat = state;
			pmsg->Rxbuf[pmsg->DataIndex] = GET_BFD(i2c->fifo,0,8);
			//printf("rx=%.2x\r\n",pmsg->Rxbuf);
			pmsg->DataIndex++;
			//printf("")
		}else{//// No  Ack request  ==> Other INT ==>  How to handle it ??
			pmsg->OpResult = 5;
		}
		break;

	case 7:		////Stop
		////Clr STA, STO, SI
		i2c->stat &= 0xFFFFF9FE;
		pmsg->BusyFlag = 0;
		pmsg->TransDone = 1;
		////Stop I2C0 INT
		I2C_IE(pn,0);
		break;

	default:
		////Clr STA, STO, SI
		i2c->stat &= 0xFFFFF9FE;
		pmsg->OpResult = 7;

	}
	if(pmsg->OpResult > 0){
		////Clr STA, STO, SI
		state |= BIT(9);
		state &= ~(BIT(0)|BIT(10)|BIT(11));
		i2c->stat = state;
		//i2c->stat &= 0xFFFFF9FE;
		////Generate STO ??
		//i2c->stat |= BIT(9);
		pmsg->BusyFlag = 0;
		pmsg->WorkingState = 0;
		pmsg->TransDone = 1;
		I2C_IE(pn,0);
	}
	i2c->cfg|=BIT(26);
	if(pmsg->TransDone==1){
		if(pmsg->OpResult>0){
			if(pmsg->fail_cbk!=NULL)pmsg->fail_cbk();
		}else{
			if(pmsg->cbk!=NULL)pmsg->cbk();
		}
	}
}

void I2C0_ExcetpionHandle(void)
{
	I2c_isr(I2C0);
}

void I2C1_ExcetpionHandle(void)
{
	I2c_isr(I2C1);
}

void I2c_WaitDone(int pn){
	volatile _I2C_CtrlMsg *pmsg=((pn==I2C0)?&s_I2C0_CtrlMsg:&s_I2C1_CtrlMsg);	
	while(pmsg->TransDone==0);
	//printf("ptr =%.8x\tind=%d\tsm=%d\tres=%d\r\n",(uint32)pmsg->Rxbuf,pmsg->DataIndex,pmsg->WorkingState,pmsg->OpResult);
}
int I2c_GetErrorStatus(int pn){
	volatile _I2C_CtrlMsg *pmsg=((pn==I2C0)?&s_I2C0_CtrlMsg:&s_I2C1_CtrlMsg);	
	return(pmsg->OpResult);
}
