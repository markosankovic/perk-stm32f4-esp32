#ifndef LED_H
#define LED_H

#include "stm32f4xx_conf.h"

#define LED_1  GPIO_Pin_13
#define LED_2  GPIO_Pin_14
#define LED_3  GPIO_Pin_11
#define LED_4  GPIO_Pin_12

void LED_INIT(void);
void LED_ON(uint16_t User_LED_no);
void LED_OFF(uint16_t User_LED_no);
void LED_TOGGLE(uint16_t User_LED_no);

#endif
