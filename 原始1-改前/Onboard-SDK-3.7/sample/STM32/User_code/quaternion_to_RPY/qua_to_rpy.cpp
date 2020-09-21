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

/*************************”√Àƒ‘™ ˝≈–∂œ∑…ª˙◊ÀÃ¨*****************************************************************/
extern	float x;
extern	float y;
extern	float z;
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
bool Tipping_detection()//«„∑≠ºÏ≤‚ true->Œ¥∑≠◊™ false->∑≠◊™
{
	Telemetry::Quaternion     quaternion;
    quaternion     = v->broadcast->getQuaternion();
	getBroadcastData();	
	x = quaternion.q1;
	y =	quaternion.q2;
	printf("Ω«∂»≤‚ ‘ %f  %f  ",x,y);
	 if((x<=-0.7)||(x>=0.7)||(y<=-0.7)||(y>=0.7))
	{
		printf("\r\nAircraft posture: posture down\r\n");
		return false;		
	}
	else if((-0.7< x)&&(x < 0.7) && (y > -0.7)&&(y < 0.7))
	{	
		printf("\r\nAircraft posture: normal posture\r\n");
		return true;
	}
}
#ifdef __cplusplus
}
#endif //__cplusplus

