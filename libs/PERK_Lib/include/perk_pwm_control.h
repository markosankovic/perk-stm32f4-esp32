#ifndef PWM_H
#define PWM_H

#include "stm32f4xx_conf.h"

#define PWM_mode 1
#define SysCoreClk 168000000

void TIM1_INIT(uint32_t T_switching, uint8_t Dead_time);
void TIM2_INIT(uint32_t T_control, uint32_t T_switching);
void TIM3_INIT(uint32_t T_control, uint32_t T_switching);
void PWM_INIT(uint32_t T_control, uint32_t T_switching, uint8_t Dead_time);
void PWM_PINs_INIT(void);

#endif
