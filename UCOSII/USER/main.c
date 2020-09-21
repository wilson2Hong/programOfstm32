#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
 #include "includes.h"
 
//START����
//�������ȼ�
#define START_TASK_PRIO 10 //��ʼ��������ȼ�Ϊ���
//���������ջ��С
#define START_STK_SIZE 128
//�����ջ
OS_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *pdata);



//LED0 ����
//�����������ȼ�
#define LED0_TASK_PRIO 7
//���������ջ��С
#define LED0_STK_SIZE 64
//�����ջ
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
//������
void led0_task(void *pdata);


//LED1 ����
//�����������ȼ�
#define LED1_TASK_PRIO 6
//���������ջ��С
#define LED1_STK_SIZE 128
//�����ջ
OS_STK LED1_TASK_STK[LED1_STK_SIZE];
//������
void led1_task(void *pdata);


//������� ����
//�����������ȼ�
#define FLOAT_TASK_PRIO 5
//���������ջ��С
#define FLOAT_STK_SIZE 128
//�����ջ
//���������ʹ��printf����ӡ�������ݵĻ���һ��Ҫ8�ֽڶ���
__align(8) OS_STK FLOAT_TASK_STK[FLOAT_STK_SIZE];

//������
void float_task(void *pdata);



 int main(void)
 {	
	delay_init();	    //��ʱ������ʼ��	  
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�ж�����
	 uart_init(115200); //���ڲ���������
	 LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	 
	 OSInit();//UCOS��ʼ��
	 OSTaskCreate(start_task,(void*)0,(OS_STK*)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO);//������ʼ����
	 
	 OSStart();//��ʼ����
	
 }
 
 //��ʼ����
 void start_task(void *pdata)
 {
		OS_CPU_SR cpu_sr=0;
	 pdata=pdata;
	 OSStatInit();//��ʼͳ������
	 
	 OS_ENTER_CRITICAL();//�����ٽ������ر��жϣ�
	 //����LED0����
	  OSTaskCreate(led0_task,(void*)0,(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],LED0_TASK_PRIO);//����LED0����
	 
  //����LED1����
	 OSTaskCreate(led1_task,(void*)0,(OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1],LED1_TASK_PRIO);//����LED1����
 
	 //���������������
	 OSTaskCreate(float_task,(void*)0,(OS_STK*)&FLOAT_TASK_STK[FLOAT_STK_SIZE-1],FLOAT_TASK_PRIO);//����FLOAT����
 
	 OSTaskSuspend(START_TASK_PRIO);//����ʼ����
	 
	 OS_EXIT_CRITICAL();//�˳��ٽ��������жϣ�
	 
 }
 
 //LED0����
 void led0_task(void *pdata)
 {
	 while(1)
	 {
		 LED0=0;
		 delay_ms(80);
		 LED0=1;
		 delay_ms(400);
		 
	 };//???
 
 }
 
 //LED1����
 void led1_task(void *pdata)
 {
		while(1)
		{
		 LED1=0;
		 delay_ms(300);
		 LED1=1;
		 delay_ms(300);
		 
		};//???
 }

//�����������
 void float_task(void *pdata)
 {
	 OS_CPU_SR cpu_sr=0;//??????
	 static float float_num=0.01;
	 while(1)
	 {
		 float_num+=0.01f;
		 OS_ENTER_CRITICAL();//�����ٽ������ر��жϣ�		 
  	 printf("float_num��ֵΪ��%.4f\r\n",float_num);//���ڴ�ӡ���	 
		 OS_EXIT_CRITICAL();//�˳��ٽ��������жϣ�
		 delay_ms(500);
		 
	 }
 
 }
 
 

