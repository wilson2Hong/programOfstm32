#include "TelemetrySample.h"
#include "qua_to_rpy.hpp"
#include "math.h"
#include "stm32f4xx.h"
#include "main.h"

#include "dji_telemetry.hpp"
extern Vehicle  vehicle;
extern Vehicle* v;

using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;

/*************************用四元数判断飞机姿态*****************************************************************/
extern	float x;
extern	float y;
extern	float z;
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
bool Tipping_detection()//倾翻检测 true->未翻转 false->翻转
{
	Telemetry::Quaternion     quaternion;
    quaternion     = v->broadcast->getQuaternion();
	getBroadcastData();	
	x = quaternion.q1;
	y =	quaternion.q2;
	printf("飞机角度: X轴角度 %f\tY轴角度 %f\r\n",x,y);
	 if((x<=-0.7)||(x>=0.7)||(y<=-0.7)||(y>=0.7))
	{
		printf("飞机姿态: 向下\r\n");
		return false;		
	}
	else if((-0.7< x)&&(x < 0.7) && (y > -0.7)&&(y < 0.7))
	{	
		printf("飞机姿态: 向上\r\n");
		return true;
	}
}
#ifdef __cplusplus
}
#endif //__cplusplus

