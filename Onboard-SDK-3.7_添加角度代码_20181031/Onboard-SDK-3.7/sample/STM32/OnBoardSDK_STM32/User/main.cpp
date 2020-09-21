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

extern u8  TIM5CH1_CAPTURE_STA;										//输入捕获状态		    				
extern u32	TIM5CH1_CAPTURE_VAL;									//输入捕获值  

extern int CHANNEL_1_ESC_WIDE,CHANNEL_2_ESC_WIDE;//手动控制翻转程序 电调脉宽控制

extern	float x;
extern	float y;
extern	float z;
extern int rcYaw,rcThrottle;											//推进器控制参数值

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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);	//设置系统中断优先级分组2
	
  delay_nms(5400);
	//delay_nms(5400);
 	TIM4_PWM_Init(2499,83);
	TIM3_CH1_Cap_Init(2499,83); 										//以400Khz的频率计数 
	TIM3_CH2_Cap_Init(2499,83); 										//以400Khz的频率计数 
	TIM3_CH3_Cap_Init(2499,83); 										//以1Mhz的频率计数 
	TIM3_CH4_Cap_Init(2499,83); 										//以1Mhz的频率计数 
  delay_nms(30);
	
	LED_Init();
	Beep_Init();
	FAN_Init();	
	LED0=0;
	LED1=0;
	BEEP = 1;
	Adc_Init();         														//初始化ADC   

//主循环
  delay_nms(5000);																//A3飞控初始化之后再初始化串口通信
	BEEP = 0;
	BSPinit();
  delay_nms(30);
//  printf("STM32F4Discovery Board initialization finished!\r\n");

	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);
	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC2,ENABLE);

//********************************************主循环控制**************************************************************//
  while (1)
  {
		  LED0 = !LED0;
  		delay_nms(2000);
			BEEP = !BEEP;
//			printf("翻转通道: channel_7 value = %d\t\t",CHANNEL_3_PULSE_WIDE);
//			printf("起飞通道: channel_8 value = %d\t\r\n",CHANNEL_4_PULSE_WIDE);

////*******************************************飞控检测、验证及通信程序*************************************************//		
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

      userActivate();															//激活程序
      delay_nms(500);
     // Verify subscription
      if (v->getFwVersion() != Version::M100_31)	//A3_31 A3_32 M100_31
      {
        v->subscribe->verify();
        delay_nms(500);
      }

      // Obtain Control Authority 获取控制权
      v->obtainCtrlAuthority();
      delay_nms(1000);
			//	open_valve();														//打开进气阀
			//	delay_nms(2000);
		}		
//********************************************************************************************************************//

//******************************************项目实现主控制循环********************************************************//
		
//****************************************1、落水后无人机动作程序*****************************************************//
/*
/飞机落水状态下的执行程序:
*/		
while(Falling_water_detection())									//飞机落水状态落水时     //Falling_water_detection() = true
		{			
			//close_valve();														//进气阀关闭
			delay_nms(2000);

//***************************************************1.1**************************************************************//
/*
/飞机落水倒扣姿态状态下的执行程序:
*/
			while(Tipping_detection()==false)						//当飞机翻转（倒扣）状态时       //（TURE->飞机姿态正常			false->飞机姿态倒翻）
					{
				//进气管关闭程序 
						if(CHANNEL_3_PULSE_WIDE<1460)					//遥控器通道7 拨到自动翻转控制挡位
						{
							esc_control_flag = 0;								//切换两路电调由怠速初始化参数控制
							CHANNEL_1_ESC_WIDE = 1224;					//此处脉宽值为飞机怠速状态脉宽值
							CHANNEL_2_ESC_WIDE = 1224;					//10%怠速
							esc_control();	
							if(Tipping_detection())							//翻转执行状态的姿态检测
							{
								esc_control_flag = 1;							//切换飞控电调控制权
								esc_control();	
							break;
							}
							else if(CHANNEL_3_PULSE_WIDE>1460)	//遥控器通道7 关闭自动翻转控制
							{
								esc_control_flag = 1;
								esc_control();	
							break;
							}
						}
						else if(CHANNEL_3_PULSE_WIDE>1660)		//遥控器通道7 拨到手动控制机器翻转档位
						{																			//飞机落水翻转通道7 A3-F2-D1
							esc_control_flag = 0;								//控制两路电调标志 1为飞控控制 否则为程序或手动控制
							CHANNEL_1_ESC_WIDE = 1224;					//此处脉宽值为飞机怠速状态脉宽值
							CHANNEL_2_ESC_WIDE = 1224;
							esc_control();											//飞机翻转的两路电调控制
							if(CHANNEL_3_PULSE_WIDE<1660)				//遥控器通道7 关闭自手动翻转控制
							{
								esc_control_flag = 1;
								esc_control();			
								break;
							}
						}
						else																	//遥控器通道7 处于中间位置 不执行任何操作
						{
								esc_control_flag = 1;	
							break;
						}
					}
//*********************************************1.1结束分隔符**********************************************************//					

//***************************************************1.2**************************************************************//
/*
/飞机落水正常姿态状态下的执行程序:
*/
			while(Tipping_detection()==true)						//当飞机姿态正常时
				{
					if(channel_8_capture())									//遥控器通道8 拨到一键起飞控制挡位 并持续拨档等待1~2秒  A3-F1-D2
					{
//						printf("飞机状态: 落水状态执行一键起飞\r\n ");					
						BEEP = 1;
						monitoredTakeOff();										//自动起飞高度1米
						BEEP = 0;
						//判断当前高度 如果高度已经为起飞状态 打开进气阀
						open_valve();
						delay_nms(2000);
						//		  moveByPositionOffset(0, 0, 3.5, 0);	//3.5米起飞高度
					}
					else if(channel_8_capture()==false)			//遥控器通道8 手动起飞控制
					{
						if(CHANNEL_3_PULSE_WIDE>1660)					//遥控器通道7 拨到手动控制机器翻转档位
						{																			//飞机落水翻转通道7 A3-F2-D1
							esc_control_flag = 0;								//控制两路电调标志 1为飞控控制 否则为程序或手动控制
							CHANNEL_1_ESC_WIDE = 1224;					//此处脉宽值为飞机怠速状态脉宽值
							CHANNEL_2_ESC_WIDE = 1224;
							esc_control();											//飞机翻转的两路电调控制
							if(CHANNEL_3_PULSE_WIDE<1660)				//通道7 拨中间 关闭手动翻转
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
/飞机推进器控制执行程序:
*/								
								while(Propeller_channel_detection())				// ADC_CH2检测 用于推进器控制
									{										
										TIM_SetCompare3(TIM4,rcThrottle);				//推进器油门位控制
										TIM_SetCompare4(TIM4,rcYaw);						//推进器偏航控制		
										if(Propeller_channel_detection() != true)	//检测推进器控制为关闭状态，则推出推进器控制程序
											break;
									}							
//**********************************************1.2.1结束分隔符*******************************************************//							
								esc_control_flag = 1;	
								esc_control();	
								if(change==0)
								{
									get_Meteorological_data();//获取气象数据
											
							 // subscribeToData();
								change =1;
								}	
								else{
									getBroadcastData();//获取飞控数据
									change =0;
								}
							break;
						}
					}
					
					
				}
//***********************************************1.2结束分隔符********************************************************//
	}
//************************************1、落水后无人机动作程序结束分隔符***********************************************//		
	
//******************************************2、陆地无人机动作程序*****************************************************//
	while(channel_8_capture()&&Tipping_detection())	//一键起飞 通道8拨向下方 翻转姿态正常 未落水
	{
//		printf("飞机状态: 一键起飞\r\n");					
		BEEP = 1;
		monitoredTakeOff();														//自动起飞高度1米
		//判断当前高度 如果高度已经为起飞状态 打开进气阀
	//	open_valve();
		BEEP = 0;
		delay_nms(2000);
	//	moveByPositionOffset(0, 0, 3.5, 0);					//3.5米起飞高度
		break;
	}
//*************************************2、陆地无人机动作程序结束分隔符************************************************//
	
//******************************************3、无人机回传实时数据*****************************************************//
		if(change==0)
				{
					getBroadcastData();										//获取飞控数据
			 // subscribeToData();
				change =1;
				}	
				else{
				get_Meteorological_data();								//获取气象站数据
					change =0;
				}
//**************************************3、无人机回传实时数据结束分隔符***********************************************//

//*******************************************4、手动翻转执行程序******************************************************//
while(CHANNEL_3_PULSE_WIDE>1660)									// 通道7检测 用于(手动)翻转程序控制
	{
//		printf("翻转状态: 手动翻转\r\n");							//飞机落水翻转通道7 A3-F2-D1
		esc_control_flag = 0;													//控制两路电调标志 1为飞控控制 否则为程序或手动控制
		CHANNEL_1_ESC_WIDE = 1224;										//此处脉宽值为飞机怠速状态脉宽值 940 1160(5%)
		CHANNEL_2_ESC_WIDE = 1224;
		esc_control();																//飞机翻转的两路电调控制
		if(CHANNEL_3_PULSE_WIDE<1660)									//通道7 拨中间
		{
			esc_control_flag = 1;
			esc_control();			
			break;
		}
	}
//**************************************4、手动翻转执行程序结束分隔符*************************************************//
	
//****************************************5、手动推进器控制执行程序***************************************************//
while(Propeller_channel_detection())							// ADC_CH2检测 用于推进器控制
	{
		
		TIM_SetCompare3(TIM4,rcThrottle);							//推进器油门位控制
		TIM_SetCompare4(TIM4,rcYaw);									//推进器偏航控制		
		if(Propeller_channel_detection() != true)			//检测推进器控制为关闭状态，则推出推进器控制程序
			break;
	}	
//*************************************5、手动推进器控制执行程序结束分隔符********************************************//
	
  }																			
//******************************************主循环控制结束分隔符******************************************************//
}																				
//********************************************主函数结束分隔符********************************************************//
	#ifdef __cplusplus
}
#endif //__cplusplus
