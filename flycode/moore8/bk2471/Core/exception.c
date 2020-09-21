#include "..\drivers\gpio\gpio.h"
#include "..\drivers\icu\icu.h"
#include "..\drivers\flash\flash.h"

extern void Uart_isr(void);
extern void timer_isr(void);
extern void Bk2401_isr(void);
extern void Gpio_isr(void);
extern void I2C0_ExcetpionHandle(void);
extern void I2C1_ExcetpionHandle(void);
/*extern "C" */void FAST_CALL FIQ_Exception(void)
{
	unsigned int IntStat;
	HW_ICU *icu=BASE_ICU_PTR;
	IntStat = icu->INT_FLAG;
	//GPIO_OutputNeg(GPIO3,BIT(2));
	if(IntStat&BIT(PID_UART))          //Uart1 Int Assert
	{
		icu->INT_FLAG=BIT(4);
		Uart_isr();
		return;
	}
	icu->INT_FLAG = IntStat;
}

/*extern "C" */void FAST_CALL IRQ_Exception(void)
{
	unsigned int IntStat;
	HW_ICU *icu=BASE_ICU_PTR;
	IntStat = icu->INT_FLAG;

	if(IntStat&BIT(PID_TIMER)){		//timer int
		icu->INT_FLAG=BIT(12);
		timer_isr();
		return;
	}
	if(IntStat&BIT(PID_BK24)){			//bk2401 int
		Bk2401_isr();
	}
	if(IntStat&BIT(PID_GPIO)){
		int i=0;
		while(icu->INT_FLAG&BIT(PID_GPIO)){
			//处理gpio多次中断的问题：原因是gpio的srcclk为32K与cpu不同步
			i++;
			if(i>40)break;
			icu->INT_FLAG=BIT(PID_GPIO);
		}
		return;
	}
	if(IntStat&BIT(PID_I2C0)){
		I2C0_ExcetpionHandle();
		icu->INT_FLAG = BIT(PID_I2C0);
		return;
	}
	if(IntStat&BIT(PID_I2C1)){
		I2C1_ExcetpionHandle();
		icu->INT_FLAG = BIT(PID_I2C1);
		return;
	}
	icu->INT_FLAG = IntStat;
}

/*Do not change the function*/
__irq void FAST_ENTRY1 SYSirq_FIQ_Handler(void)
{
	__asm volatile
	{
		bl FIQ_Exception
	};
}

/*Do not change the function*/
__irq void FAST_ENTRY2 SYSirq_IRQ_Handler(void)
{
	__asm volatile
	{
		bl IRQ_Exception
	};
}
