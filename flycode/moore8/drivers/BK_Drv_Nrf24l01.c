#include "BK_Drv_Nrf24l01.h"
#include "..\bk2471\includes\types.h"
#include "..\bk2471\drivers\rf24\bk24.h"
#include "BK_RC.h"

uint8 rxData[32];
uint8 bk2401_dataRdy=0;
void Bk2401_isr(){
	u8 sta = TRX_IRQ_STATUS;
	if(sta & (B_IRQ_RX_DR))
	{
		u8 rx_len = TRX_RX_RPL_WIDTH;		
		if(rx_len<33)
		{
			R_RX_PAYLOAD(rxData,rx_len);
			Data_Receive_Anl(rxData,rx_len);
			RF_CE(0);
			bk2401_dataRdy=1;
			//RF_StartRX(BK_DBG_RF_CHN);
		}
		else 
		{
			FLUSH_RX;
		}
	}
	if(sta & (B_IRQ_TX_DS))
	{}

	if(sta & (B_IRQ_MAX_RT))
	{
		FLUSH_TX;
	}
	
	TRX_IRQ_STATUS = sta;
}
