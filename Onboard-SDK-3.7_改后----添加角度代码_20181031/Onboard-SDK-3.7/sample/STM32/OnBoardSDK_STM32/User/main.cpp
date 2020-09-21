/*! @file main.cpp
 *  @version 3.3
 *  @date May 2017
 *
 *  @brief
 *  An exmaple program of DJI-onboard-SDK portable for stm32
 *
 *  @Copyright (c) 2016-2017 DJI
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *
 *
 *******************************************************************************
 *                                                                             *
 *          --------               --------                 --------           *
 *         |        |   USART2    |        |    USART3     |        |          *
 *         |   PC   | <---------> | stm32  |  <----------> |  M100  |          *
 *         |        | (USB-TTL)   |        |               |        |          *
 *         |        |             |        |               |        |          *
 *          --------               --------                 --------           *
 *                                                                             *
 *                                                                             *
 *******************************************************************************
 * */

#include "stm32f4xx.h"
#include "main.h"
#include "dji_mfio.hpp"
#include "sys.h"
#include "esc_control.hpp"
#include "adc_water.hpp"	
#include "qua_to_rpy.hpp"
#include "iwdg.hpp"
#include "led.hpp"
#include "inlet_outlet_valve.hpp"
#include "weather_station.hpp"

#define sample_flag 0;
#ifdef FLIGHT_CONTROL_SAMPLE
#define sample_flag 1
#elif HOTPOINT_MISSION_SAMPLE
#define sample_flag 2
#elif WAYPOINT_MISSION_SAMPLE
#define sample_flag 3
#elif CAMERA_GIMBAL_SAMPLE
#define sample_flag 4
#elif MOBILE_SAMPLE
#define sample_flag 5
#elif TELEMETRY_SAMPLE
#define sample_flag 6
#endif

const int sampleToRun = sample_flag;

/*-----------------------DJI_LIB VARIABLE-----------------------------*/
using namespace DJI::OSDK;

bool           threadSupport = false;
bool           isFrame       = false;
RecvContainer  receivedFrame;
RecvContainer* rFrame  = &receivedFrame;
Vehicle        vehicle = Vehicle(threadSupport);
Vehicle*       v       = &vehicle;

extern Vehicle  vehicle;
extern Vehicle* v;
using namespace DJI::OSDK::Telemetry;

extern TerminalCommand myTerminal;

extern int CHANNEL_1_PULSE_WIDE;									//TIM2_CH1 PWM OUT
extern int CHANNEL_2_PULSE_WIDE;									//TIM2_CH2 PWM OUT
extern int CHANNEL_3_PULSE_WIDE;									//TIM2_CH1 PWM OUT
extern int CHANNEL_4_PULSE_WIDE;									//TIM2_CH2 PWM OUT

extern u8  TIM5CH1_CAPTURE_STA;										//���벶��״̬		    				
extern u32	TIM5CH1_CAPTURE_VAL;									//���벶��ֵ  

extern int CHANNEL_1_ESC_WIDE,CHANNEL_2_ESC_WIDE;//�ֶ����Ʒ�ת���� ����������

extern	float x;
extern	float y;
extern	float z;
extern int rcYaw,rcThrottle;											//�ƽ������Ʋ���ֵ

extern int esc_control_flag;
int Tip_detection;
int i=0,change = 0;

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

int
main()
{	
  char     func[50];
  uint32_t runOnce = 1;

	long long temp=0; 
	double temp1;
	u16 adcx;
	
	esc_control_flag = 1;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	//����ϵͳ�ж����ȼ�����2
	
  delay_nms(5400);
	//delay_nms(5400);
 	TIM4_PWM_Init(2499,83);
	TIM3_CH1_Cap_Init(2499,83); 										//��400Khz��Ƶ�ʼ��� 
	TIM3_CH2_Cap_Init(2499,83); 										//��400Khz��Ƶ�ʼ��� 
	TIM3_CH3_Cap_Init(2499,83); 										//��1Mhz��Ƶ�ʼ��� 
	TIM3_CH4_Cap_Init(2499,83); 										//��1Mhz��Ƶ�ʼ��� 
  delay_nms(30);
	
	LED_Init();
	Beep_Init();
	FAN_Init();	
	LED0=0;
	LED1=0;
	BEEP = 1;
	Adc_Init();         														//��ʼ��ADC   

//��ѭ��
  delay_nms(5000);																//A3�ɿس�ʼ��֮���ٳ�ʼ������ͨ��
	BEEP = 0;
	BSPinit();
  delay_nms(30);
//  printf("STM32F4Discovery Board initialization finished!\r\n");

	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);
	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC2,ENABLE);

//********************************************��ѭ������**************************************************************//
  while (1)
  {
		  LED0 = !LED0;
  		delay_nms(2000);
			BEEP = !BEEP;
//			printf("��תͨ��: channel_7 value = %d\t\t",CHANNEL_3_PULSE_WIDE);
//			printf("���ͨ��: channel_8 value = %d\t\r\n",CHANNEL_4_PULSE_WIDE);

////*******************************************�ɿؼ�⡢��֤��ͨ�ų���*************************************************//		
//********************************************************************************************************************//
// One time automatic activation
    if (runOnce)
    {
      runOnce = 0;
      // Check USART communication
      if (!v->protocolLayer->getDriver()->getDeviceStatus())
      {
        printf("USART communication is not working.\r\n");
        delete (v);
        return -1;
      }

      printf("Sample App for STM32F4Discovery Board:\r\n");
      delay_nms(30);

      printf("\nPrerequisites:\r\n");
      printf("1. Vehicle connected to the Assistant and simulation is ON\r\n");
      printf("2. Battery fully chanrged\r\n");
      printf("3. DJIGO App connected (for the first time run)\r\n");
      printf("4. Gimbal mounted if needed\r\n");
      delay_nms(30);

      //! Initialize functional Vehicle components like
      //! Subscription, Broabcast, Control, Camera, etc
      v->functionalSetUp();
      delay_nms(500);

      // Check if the firmware version is compatible with this OSDK version
      if (v->getFwVersion() > 0 &&
				v->getFwVersion() < extendedVersionBase &&
	      v->getFwVersion() != Version::M100_31)
      {
	      printf("Upgrade firmware using Assistant software!\n");
        delete (v);
        return -1;
      }

      userActivate();															//�������
      delay_nms(500);
     // Verify subscription
      if (v->getFwVersion() != Version::M100_31)	//A3_31 A3_32 M100_31
      {
        v->subscribe->verify();
        delay_nms(500);
      }

      // Obtain Control Authority ��ȡ����Ȩ
      v->obtainCtrlAuthority();
      delay_nms(1000);
			//	open_valve();														//�򿪽�����
			//	delay_nms(2000);
		}		
//********************************************************************************************************************//

//******************************************��Ŀʵ��������ѭ��********************************************************//
		
//****************************************1����ˮ�����˻���������*****************************************************//
/*
/�ɻ���ˮ״̬�µ�ִ�г���:
*/		
while(Falling_water_detection())									//�ɻ���ˮ״̬��ˮʱ     //Falling_water_detection() = true
		{			
			//close_valve();														//�������ر�
			delay_nms(2000);

//***************************************************1.1**************************************************************//
/*
/�ɻ���ˮ������̬״̬�µ�ִ�г���:
*/
			while(Tipping_detection()==false)						//���ɻ���ת�����ۣ�״̬ʱ       //��TURE->�ɻ���̬����			false->�ɻ���̬������
					{
				//�����ܹرճ��� 
						if(CHANNEL_3_PULSE_WIDE<1460)					//ң����ͨ��7 �����Զ���ת���Ƶ�λ
						{
							esc_control_flag = 0;								//�л���·����ɵ��ٳ�ʼ����������
							CHANNEL_1_ESC_WIDE = 1224;					//�˴�����ֵΪ�ɻ�����״̬����ֵ
							CHANNEL_2_ESC_WIDE = 1224;					//10%����
							esc_control();	
							if(Tipping_detection())							//��תִ��״̬����̬���
							{
								esc_control_flag = 1;							//�л��ɿص������Ȩ
								esc_control();	
							break;
							}
							else if(CHANNEL_3_PULSE_WIDE>1460)	//ң����ͨ��7 �ر��Զ���ת����
							{
								esc_control_flag = 1;
								esc_control();	
							break;
							}
						}
						else if(CHANNEL_3_PULSE_WIDE>1660)		//ң����ͨ��7 �����ֶ����ƻ�����ת��λ
						{																			//�ɻ���ˮ��תͨ��7 A3-F2-D1
							esc_control_flag = 0;								//������·�����־ 1Ϊ�ɿؿ��� ����Ϊ������ֶ�����
							CHANNEL_1_ESC_WIDE = 1224;					//�˴�����ֵΪ�ɻ�����״̬����ֵ
							CHANNEL_2_ESC_WIDE = 1224;
							esc_control();											//�ɻ���ת����·�������
							if(CHANNEL_3_PULSE_WIDE<1660)				//ң����ͨ��7 �ر����ֶ���ת����
							{
								esc_control_flag = 1;
								esc_control();			
								break;
							}
						}
						else																	//ң����ͨ��7 �����м�λ�� ��ִ���κβ���
						{
								esc_control_flag = 1;	
							break;
						}
					}
//*********************************************1.1�����ָ���**********************************************************//					

//***************************************************1.2**************************************************************//
/*
/�ɻ���ˮ������̬״̬�µ�ִ�г���:
*/
			while(Tipping_detection()==true)						//���ɻ���̬����ʱ
				{
					if(channel_8_capture())									//ң����ͨ��8 ����һ����ɿ��Ƶ�λ �����������ȴ�1~2��  A3-F1-D2
					{
//						printf("�ɻ�״̬: ��ˮ״ִ̬��һ�����\r\n ");					
						BEEP = 1;
						monitoredTakeOff();										//�Զ���ɸ߶�1��
						BEEP = 0;
						//�жϵ�ǰ�߶� ����߶��Ѿ�Ϊ���״̬ �򿪽�����
						open_valve();
						delay_nms(2000);
						//		  moveByPositionOffset(0, 0, 3.5, 0);	//3.5����ɸ߶�
					}
					else if(channel_8_capture()==false)			//ң����ͨ��8 �ֶ���ɿ���
					{
						if(CHANNEL_3_PULSE_WIDE>1660)					//ң����ͨ��7 �����ֶ����ƻ�����ת��λ
						{																			//�ɻ���ˮ��תͨ��7 A3-F2-D1
							esc_control_flag = 0;								//������·�����־ 1Ϊ�ɿؿ��� ����Ϊ������ֶ�����
							CHANNEL_1_ESC_WIDE = 1224;					//�˴�����ֵΪ�ɻ�����״̬����ֵ
							CHANNEL_2_ESC_WIDE = 1224;
							esc_control();											//�ɻ���ת����·�������
							if(CHANNEL_3_PULSE_WIDE<1660)				//ͨ��7 ���м� �ر��ֶ���ת
							{
								esc_control_flag = 1;
								esc_control();			
								break;
							}
						}
						else																	//
						{
//***************************************************1.2.1************************************************************//							
/*
/�ɻ��ƽ�������ִ�г���:
*/								
								while(Propeller_channel_detection())				// ADC_CH2��� �����ƽ�������
									{										
										TIM_SetCompare3(TIM4,rcThrottle);				//�ƽ�������λ����
										TIM_SetCompare4(TIM4,rcYaw);						//�ƽ���ƫ������		
										if(Propeller_channel_detection() != true)	//����ƽ�������Ϊ�ر�״̬�����Ƴ��ƽ������Ƴ���
											break;
									}							
//**********************************************1.2.1�����ָ���*******************************************************//							
								esc_control_flag = 1;	
								esc_control();	
								if(change==0)
								{
									get_Meteorological_data();//��ȡ��������
											
							 // subscribeToData();
								change =1;
								}	
								else{
									getBroadcastData();//��ȡ�ɿ�����
									change =0;
								}
							break;
						}
					}
					
					
				}
//***********************************************1.2�����ָ���********************************************************//
	}
//************************************1����ˮ�����˻�������������ָ���***********************************************//		
	
//******************************************2��½�����˻���������*****************************************************//
	while(channel_8_capture()&&Tipping_detection())	//һ����� ͨ��8�����·� ��ת��̬���� δ��ˮ
	{
//		printf("�ɻ�״̬: һ�����\r\n");					
		BEEP = 1;
		monitoredTakeOff();														//�Զ���ɸ߶�1��
		//�жϵ�ǰ�߶� ����߶��Ѿ�Ϊ���״̬ �򿪽�����
	//	open_valve();
		BEEP = 0;
		delay_nms(2000);
	//	moveByPositionOffset(0, 0, 3.5, 0);					//3.5����ɸ߶�
		break;
	}
//*************************************2��½�����˻�������������ָ���************************************************//
	
//******************************************3�����˻��ش�ʵʱ����*****************************************************//
		if(change==0)
				{
					getBroadcastData();										//��ȡ�ɿ�����
			 // subscribeToData();
				change =1;
				}	
				else{
				get_Meteorological_data();								//��ȡ����վ����
					change =0;
				}
//**************************************3�����˻��ش�ʵʱ���ݽ����ָ���***********************************************//

//*******************************************4���ֶ���תִ�г���******************************************************//
while(CHANNEL_3_PULSE_WIDE>1660)									// ͨ��7��� ����(�ֶ�)��ת�������
	{
//		printf("��ת״̬: �ֶ���ת\r\n");							//�ɻ���ˮ��תͨ��7 A3-F2-D1
		esc_control_flag = 0;													//������·�����־ 1Ϊ�ɿؿ��� ����Ϊ������ֶ�����
		CHANNEL_1_ESC_WIDE = 1224;										//�˴�����ֵΪ�ɻ�����״̬����ֵ 940 1160(5%)
		CHANNEL_2_ESC_WIDE = 1224;
		esc_control();																//�ɻ���ת����·�������
		if(CHANNEL_3_PULSE_WIDE<1660)									//ͨ��7 ���м�
		{
			esc_control_flag = 1;
			esc_control();			
			break;
		}
	}
//**************************************4���ֶ���תִ�г�������ָ���*************************************************//
	
//****************************************5���ֶ��ƽ�������ִ�г���***************************************************//
while(Propeller_channel_detection())							// ADC_CH2��� �����ƽ�������
	{
		
		TIM_SetCompare3(TIM4,rcThrottle);							//�ƽ�������λ����
		TIM_SetCompare4(TIM4,rcYaw);									//�ƽ���ƫ������		
		if(Propeller_channel_detection() != true)			//����ƽ�������Ϊ�ر�״̬�����Ƴ��ƽ������Ƴ���
			break;
	}	
//*************************************5���ֶ��ƽ�������ִ�г�������ָ���********************************************//
	
  }																			
//******************************************��ѭ�����ƽ����ָ���******************************************************//
}																				
//********************************************�����������ָ���********************************************************//
	#ifdef __cplusplus
}
#endif //__cplusplus
