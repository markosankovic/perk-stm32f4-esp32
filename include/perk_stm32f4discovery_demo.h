#ifndef PERK_DEMO
#define PERK_DEMO

#include "stm32f4xx_conf.h"

#define LED_green  GPIO_Pin_12
#define LED_orange  GPIO_Pin_13
#define LED_red  GPIO_Pin_14
#define LED_blue  GPIO_Pin_15
#define Taster_1  GPIO_Pin_0

void DEMO_Taster_INIT(void);
uint8_t DEMO_Taster_Status(uint16_t User_button);

void DEMO_LED_INIT(void);
void DEMO_LED_ON(uint16_t User_LED_no);
void DEMO_LED_OFF(uint16_t User_LED_no);
void DEMO_LED_TOGGLE(uint16_t User_LED_no);

#endif
