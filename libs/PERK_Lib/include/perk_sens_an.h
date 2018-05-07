#ifndef ADC_SENSOR_READ_H
#define ADC_SENSOR_READ_H

#include "stm32f4xx_conf.h"

#define Sensor_1  ADC_Channel_0
#define Sensor_2  ADC_Channel_1
#define Sensor_3  ADC_Channel_2

void ADC_INIT(void);
void DMA_for_ADC_init(void);
void ADC_PINs_INIT(void);
void Sensor_INIT(void);
uint16_t Sensor_an_read(uint8_t Sensor_no);

#endif
