#include "i2c0.h"
#include "gpio.h"
#include "icu.h"

#define SCL0_HIGH()		GPIO_Output(GPIOC)|=BIT(2)
#define SCL0_LOW()		GPIO_Output(GPIOC)&=_BIT(2)
#define SDA0_HIGH()		GPIO_Output(GPIOC)|=BIT(3)
#define SDA0_LOW()		GPIO_Output(GPIOC)&=_BIT(3)
#define SDA0_SetInput()	GPIO_InputSetup(GPIOC,BIT(3),BIT(3),0)
#define SDA0_SetOutput()	GPIO_OutputSetup(GPIOC,BIT(3))
#define SDA0_READ()		GPIO_Input(GPIOC)&BIT(3)
void delay(int dly){
	while(dly--);
}
void I2c_Init(int pn){
	GPIO_OutputSetup(GPIOC,BIT(2)|BIT(3));
}

void __i2cs_SB(){
	SDA0_HIGH();
	SCL0_HIGH();
	delay(10);
	SDA0_LOW();
	delay(10);
	SCL0_LOW();
}

void __i2cs_STP(){
	SDA0_LOW();
	delay(3);
	SCL0_HIGH();
	SDA0_HIGH();
}

int __i2c_tx_byte(char d){
	int i;
	for(i=0;i<8;i++){
		if(d&BIT(7)){
			SDA0_HIGH();
		}else{
			SDA0_LOW();
		}
		SCL0_HIGH();
		//delay(2);
		SCL0_LOW();
		//delay(1);
		d<<=1;
	}
	SDA0_SetInput();
	SCL0_HIGH();
	//delay(1);
	i=SDA0_READ();
	//delay(1);
	SCL0_LOW();
	SDA0_SetOutput();
	return(i==0);
}
int __i2c_rx_byte(){
	int i;
	int r=0;
	SDA0_SetInput();
	delay(1);
	for(i=0;i<8;i++){
		SCL0_HIGH();
		//delay(1);
		r<<=1;
		if(SDA0_READ()){
			r|=1;
		}
		//delay(1);
		SCL0_LOW();
		//delay(1);
	}
	SDA0_SetOutput();
	SDA0_LOW();
	SCL0_HIGH();
	delay(1);
	SCL0_LOW();
	SDA0_SetInput();
	return(r);
}

void I2c_SendBytes(int pn,uint32 devAddr7,uint32 addr,char*buf,uint32 sz){
	int i;
	__i2cs_SB();
	__i2c_tx_byte(devAddr7<<1);
	__i2c_tx_byte(addr);
	for(i=0;i<sz;i++){
		__i2c_tx_byte(*buf++);
	}
	__i2cs_STP();
}

void I2c_RcvBytes(int pn,uint32 devAddr7,uint32 addr,char*buf,uint32 sz){
	int i;
	__i2cs_SB();
	__i2c_tx_byte(devAddr7<<1);
	__i2c_tx_byte(addr);
	__i2cs_SB();
	__i2c_tx_byte((devAddr7<<1)+1);
	for(i=0;i<sz;i++){
		*buf++=__i2c_rx_byte();
	}
	SDA0_SetOutput();
	__i2cs_STP();
}