#ifndef BUTTON_H
#define BUTTON_H

#include "stm32f4xx_conf.h"

#define Button_1  GPIO_Pin_0
#define Button_2  GPIO_Pin_1
#define Button_3  GPIO_Pin_2
#define Button_4  GPIO_Pin_3

void Buttons_INIT(void);
uint8_t Button_Status(uint16_t User_button);

#endif
