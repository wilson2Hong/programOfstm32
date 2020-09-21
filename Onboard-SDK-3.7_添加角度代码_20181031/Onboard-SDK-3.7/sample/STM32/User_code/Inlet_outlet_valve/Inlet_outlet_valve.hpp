#ifndef __INLET_OUTLET_VALVE_H
#define __INLET_OUTLET_VALVE_H

#include "sys.h" 
#include "stm32f4xx_adc.h" 
#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
#define FAN PAout(1)	// ·çÉÈ¶Ë¿Ú
void FAN_Init(void);	 
void open_valve();
void close_valve();	 
	 
#ifdef __cplusplus
}
#endif //__cplusplus

#endif 