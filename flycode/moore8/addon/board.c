#include <stdio.h>
#include "..\bk2471\includes\types.h"
#include "..\bk2471\drivers\timer\timer.h"
#include "..\bk2471\drivers\icu\icu.h"
#include "..\bk2471\drivers\flash\flash.h"
#include "..\bk2471\common\common.h"
#include "..\bk2471\drivers\i2c\i2c0.h"
#include "..\bk2471\drivers\uart\uart.h"
#include "..\bk2471\drivers\rf24\bk24.h"
#include "..\bk2471\drivers\adc\adc.h"

#include "board.h"

static volatile uint32_t usTicks = 0;				// cycles per microsecond
static volatile uint32_t sysTickUptime = 0;			// �δ�ʱ���������� ,49������

extern int8 fbStartUnlock;
extern int8 fbWaitThrHigh;
extern int8 fbWaitThrLow;

static void cycleCounterInit(void)
{
	Timer_SetTO_16M(TIMER1,TIMER_FREE_RUN,1);		//free run timer
	Timer_IE(1);
}

uint8_t ARMED;		//ң�ؽ�����ʶ
u16 failsafeCnt = 0;//ң��ʧ������

void Led_ON(void)
{
	GPIO_OutputHigh(BK_GPIO_LED,BK_Pin_LEDA|BK_Pin_LEDB);
}

void Led_OFF(void)
{
	GPIO_OutputLow(BK_GPIO_LED,BK_Pin_LEDA|BK_Pin_LEDB);
}

void Led_Init(void)
{
	GPIO_OutputSetup(BK_GPIO_LED,BK_Pin_LEDA|BK_Pin_LEDB);
	Led_ON();
}


//LEDָʾ����,3��״̬,У׼����,����������,δ��������
void Pilot_Light(void)
{
	static u8 cnt = 0;

	if(ARMED){
		cnt++;
		switch(cnt){
		case 1:
			Led_ON();
			break;
		case 100:
			Led_OFF();
			break;
		case 200:
			cnt = 0;
			break;
		}
	}
	else
	{
		if(Gyro_CALIBRATED)
		{
			cnt++;
			switch(cnt)
			{
				case 0:
					Led_ON();
					break;
				case 30:
					Led_OFF();
					break;
				case 60:
					Led_ON();
					cnt=0;
					break;
			}
		}
		else
		{
			Led_ON();
		}
	}
}

void flash_init_my(int mode_line)
{
	ICU_SetSysclk96M(0);			//��Ƶ������96M/(1+1)
	set_flash_qe();					//ʹ������ģʽ
	flash_set_line_mode(mode_line);	//������ģʽ
}

void rf_init_my(void)
{
	Rf_Init();						//��ʼ��RF
	RF_SetTxPower(RF_TXPWR_0dBm);	
	RF_SetupInterrupt(B_IRQ_RX_DR|B_IRQ_TX_DS|B_IRQ_MAX_RT);
}

//	CPU��ʼ��
void BK2471_Init(void)
{
	ICU_Initial();					//оƬ��Դ,ʱ��,RFӲ����ʼ��
	Beken_UART_Initial(115200);		//��ʼ��Uart1
//	printf("Beken_UART_Initial\r\n");

	rf_init_my();					//��ʼ��RF

	cycleCounterInit();				//��ʼ����ʱ��
	I2c_Init(I2C0,460000);			//��ʼ��I2C

	Pwm_out_Init(16000);			//��ʼ�����PWM
	Led_Init();

	flash_init_my(4);
}
