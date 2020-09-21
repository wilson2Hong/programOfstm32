#ifndef _WEATHER_STATION_H
#define _WEATHER_STATION_H
#ifdef __cplusplus
#include "stm32f4xx.h"
extern "C" {
#endif //__cplusplus
void get_Meteorological_data(void);
void IEEE754_to_float(int hex);
void weather_data_process(const uint8_t *stationData, uint16_t *weatherData);
void weather_data_process1(const uint8_t *stationData, int *weatherData);
void Weather_station_response_request(void);
#ifdef __cplusplus
}
#endif //__cplusplus

#endif