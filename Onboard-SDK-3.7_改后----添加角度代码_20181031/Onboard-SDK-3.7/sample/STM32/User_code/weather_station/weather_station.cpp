#include "stm32f4xx.h"
#include "BspUsart.h"
#include "timer.h"
#include "weather_station.hpp"
#include "Receive.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

static uint8_t ack_BUF[8]={0x00,0x03,0x00,0x00,0x00,0x29,0x85,0xC5};
u8 t;
u8 len;	
float data = 0;

int printf_Flag = 0;
extern uint8_t StationData[87];
//测试数据
uint8_t StationData_test[87]={
0x01,0x03, 0x52, 0xA8, 0x2F, 0x01, 0x00, 0x75, 0x70, 0x3C, 0xED, 0xDD, 0xC0, 0x42, 0x01, 0x28, 0xC8, 0x41, 0xD3, 0xC6,
0x12,0x44, 0x79, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 
0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x92, 0x00, 0x00, 0x00, 
0x00,0x75, 0x70, 0x3C, 0xED, 0x88, 0x88};
uint16_t WeatherData[2]={0};
int WeatherData1[5]={0};
float Weather_Data[7]={0};
void get_Meteorological_data(void)
{
//	USART_ClearFlag(USART1,USART_FLAG_TC);
	Weather_station_response_request();//发送响应请求
	
		if(printf_Flag == 1)//气象站响应请求发送完毕
//  if(1)//气象站响应请求发送完毕
	{
		weather_data_process(StationData,WeatherData);//获取气象站各项数据
		weather_data_process1(StationData,WeatherData1);//获取气象站各项数据
		Weather_Data[0] = (float)WeatherData[0];//相对风向
		
		IEEE754_to_float(WeatherData1[4]);			//真实风向
		Weather_Data[1] = data;
		IEEE754_to_float(WeatherData1[0]);			//相对风速
		Weather_Data[2] = data;
		IEEE754_to_float(WeatherData1[1]);			//温度
		Weather_Data[3] = data;
		IEEE754_to_float(WeatherData1[2]);			//湿度
		Weather_Data[4] = data;
		IEEE754_to_float(WeatherData1[3]);			//气压
		Weather_Data[5] = data;
		
		Weather_Data[6] = (float)WeatherData[5];//电子罗盘
		printf_Flag = 0;
	}
	delay_nms(20);
	
	  printf("s%.2f %.2f %.2f %.2f %.2f!",Weather_Data[3],Weather_Data[4],Weather_Data[0],Weather_Data[5],Weather_Data[2]);
	
	
//	printf("---------------------------气象站回传数据---------------------------------\r\n");
//	printf("相对风向：%.2f°\t相对风速：%.2f m/s\t温度：%.2f℃\r\n    湿度：%.2f%%\t\t气压：%.2fPa\t\t电子罗盘：%.2f°\r\n",
//					Weather_Data[0],Weather_Data[2],Weather_Data[3],Weather_Data[4],Weather_Data[5],Weather_Data[6]);
}
void weather_data_process(const uint8_t *stationData, uint16_t *weatherData)		//将气象站传回的87字节的数据进行处理
{
		//风向
	weatherData[0]=(stationData[5]<<8)+stationData[6];	
		//电子罗盘
	weatherData[5]=(stationData[23]<<8)+stationData[24];
}
void weather_data_process1(const uint8_t *stationData, int *weatherData)		//将气象站传回的87字节的数据进行处理
{
		//相对风速
	weatherData[0]=(int)((stationData[9]<<24)+(stationData[10]<<16)+(stationData[7]<<8)+stationData[8]);
		//温度
	weatherData[1]=(int)((stationData[13]<<24)+(stationData[14]<<16)+(stationData[11]<<8)+stationData[12]);
		//湿度
	weatherData[2]=(int)((stationData[17]<<24)+(stationData[18]<<16)+(stationData[15]<<8)+stationData[16]);
		//气压
	weatherData[3]=(int)((stationData[21]<<24)+(stationData[22]<<16)+(stationData[19]<<8)+stationData[20]);
		//真实风向
	weatherData[4]=(int)((stationData[77]<<24)+(stationData[78]<<16)+(stationData[75]<<8)+stationData[76]);

}

void IEEE754_to_float(int hex)//二进制机器码转换成十进制浮点数
{
	float* fp=(float*)&hex;
	data = *fp;
}

void Weather_station_response_request(void)//气象站响应请求发送
{
	for(t=0;t<8;t++)//气象站
		{
				USART_SendData(USART1, ack_BUF[t]);         //向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			if(t==7)
				printf_Flag = 1;
		}
}


#ifdef __cplusplus
}
#endif //__cplusplus
	
