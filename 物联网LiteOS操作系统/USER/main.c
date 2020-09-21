#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "adc.h"
#include "dma.h"
#include "stm32f10x.h"

/*LiteOS����*/
/*LiteOSͷ�ļ�*/
#include "los_sys.h"
#include "los_task.ph"
#include "los_typedef.h"

/*����������*/
UINT32 Test1_Task_Handle;

/*��������*/
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
		delay_ms(300);	 //��ʱ300ms
		LED0=1;
		LED1=0;
		delay_ms(300);	//��ʱ300ms
		
		
	}
	
	

		



}



/*******************************************************************
 * @ ������ �� AppTaskCreate
 * @ ����˵���� ���񴴽���Ϊ�˷���������е����񴴽����������Է��������������
 * @ ���� �� ��
 * @ ����ֵ �� ��
*************************************************************/

static UINT32 AppTaskCreate(void)
{
	/*����һ���������ͱ�������ʼ��ΪLOS_OK*/
	UINT32 uwRet = LOS_OK;
	
	uwRet = Creat_Test1_Task();
	if(uwRet != LOS_OK)
	{
		printf("Test1_Task���񴴽�ʧ�ܣ�ʧ�ܴ���0x%X\n",uwRet);
		return uwRet;
	}
	return LOS_OK;
	
}


/******************************************************************
 * @ ������ �� Creat_Test1_Task
 * @ ����˵���� ���� Test1_Task ����
 * @ ���� ��
 * @ ����ֵ �� ��
******************************************************************/
static UINT32 Creat_Test1_Task()
{
	/*����һ����������ķ������ͣ���ʼ��Ϊ�����ɹ��ķ���ֵ*/
	UINT32 uwRet =LOS_OK;
	
	//����һ�����ڴ�������Ĳ����ṹ��
	TSK_INIT_PARAM_S task_init_param;
	
	task_init_param.usTaskPrio = 3;/*�������ȼ�����ֵԽС�����ȼ�Խ��*/
	task_init_param.pcName = "Test1_Task";/*������*/
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Test1_Task;/*���������*/
	task_init_param.uwStackSize = 1024;/*ջ��С*/
	
	uwRet = LOS_TaskCreate(&Test1_Task_Handle,&task_init_param);/*��������*/
	
 	return uwRet;

}

/******************************************************************
 * @ ������ �� Test1_Task
 * @ ����˵���� Test1_Task ����ʵ��
 * @ ���� �� NULL
 * @ ����ֵ �� NULL
 *****************************************************************/

static void Test1_Task(void)
{
	/*������һ������ѭ�������ܷ���*/
	while(1)
	{
		//LED2_TOGGLE;//?????????????????
		printf("����1�����У�ÿ1000ms��ӡһ����Ϣ\r\n");
		LOS_TaskDelay(1000);	
	}	
}
