#include "BK_Scheduler.h"
#include "..\bk2471\drivers\adc\adc.h"

#define BAT_C	4.58		//����100k/����51k
//#define BAT_C	4.75		//����100k/����47k
//#define BAT_C	7.23		//��ѹ��_6881
//#define BAT_C	6.16		//��ѹ��_6050

float lpf_bat[3]={1,-1.994,0.994012};
//��ѹ3.7V��Ӧ 3700
uint16 batVol;
void app_adc_task(void)
{
	int buf[1];
	float ret;	
	static float lpf_buf[3]={0,0,0};

	ADC_Samp(buf);

	if(lpf_buf[2]==0)
	{
		lpf_buf[1] =1e8;
		lpf_buf[0] =1e8;
	}
	lpf_buf[2] = lpf_buf[1];
	lpf_buf[1] = lpf_buf[0];
	
	lpf_buf[0] = buf[0] - lpf_buf[1] *lpf_bat[1] - lpf_buf[2] * lpf_bat[2];
	
	if (!isfinite(lpf_buf[0])) 		lpf_buf[0] = buf[0];
	
	ret = lpf_buf[0]*0.000012;
	
	batVol=(uint16)(ret*BAT_C);
}
