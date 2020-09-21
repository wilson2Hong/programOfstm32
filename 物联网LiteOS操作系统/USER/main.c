#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "adc.h"
#include "dma.h"
#include "stm32f10x.h"

/*LiteOS部分*/
/*LiteOS头文件*/
#include "los_sys.h"
#include "los_task.ph"
#include "los_typedef.h"

/*定义任务句柄*/
UINT32 Test1_Task_Handle;

/*函数声明*/
static UINT32 AppTaskCreate(void);
static UINT32 Creat_Test1_Task(void);

static void Test1_Task();


int main(void)
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	LED_Init();
	
	LOS_Start();
	
	while(1)
	{
		LED0=0;
		LED1=1;
		delay_ms(300);	 //延时300ms
		LED0=1;
		LED1=0;
		delay_ms(300);	//延时300ms
		
		
	}
	
	

		



}



/*******************************************************************
 * @ 函数名 ： AppTaskCreate
 * @ 功能说明： 任务创建，为了方便管理，所有的任务创建函数都可以放在这个函数里面
 * @ 参数 ： 无
 * @ 返回值 ： 无
*************************************************************/

static UINT32 AppTaskCreate(void)
{
	/*定义一个返回类型变量，初始化为LOS_OK*/
	UINT32 uwRet = LOS_OK;
	
	uwRet = Creat_Test1_Task();
	if(uwRet != LOS_OK)
	{
		printf("Test1_Task任务创建失败！失败代码0x%X\n",uwRet);
		return uwRet;
	}
	return LOS_OK;
	
}


/******************************************************************
 * @ 函数名 ： Creat_Test1_Task
 * @ 功能说明： 创建 Test1_Task 任务
 * @ 参数 ：
 * @ 返回值 ： 无
******************************************************************/
static UINT32 Creat_Test1_Task()
{
	/*定义一个创建任务的返回类型，初始化为创建成功的返回值*/
	UINT32 uwRet =LOS_OK;
	
	//定义一个用于创建任务的参数结构体
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 3;/*任务优先级，数值越小，优先级越高*/
	task_init_param.pcName = "Test1_Task";/*任务名*/
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Test1_Task;/*任务函数入口*/
	task_init_param.uwStackSize = 1024;/*栈大小*/
	
	uwRet = LOS_TaskCreate(&Test1_Task_Handle,&task_init_param);/*创建任务*/
	
 	return uwRet;

}

/******************************************************************
 * @ 函数名 ： Test1_Task
 * @ 功能说明： Test1_Task 任务实现
 * @ 参数 ： NULL
 * @ 返回值 ： NULL
 *****************************************************************/

static void Test1_Task(void)
{
	/*任务都是一个无限循环，不能返回*/
	while(1)
	{
		//LED2_TOGGLE;//?????????????????
		printf("任务1运行中，每1000ms打印一次信息\r\n");
		LOS_TaskDelay(1000);	
	}	
}
