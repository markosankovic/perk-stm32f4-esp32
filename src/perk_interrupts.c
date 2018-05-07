#include "perk_interrupts.h"

// Interrupt table configuration
void NVIC_INIT(void){
	NVIC_InitTypeDef NVIC_TIM2;
	NVIC_InitTypeDef NVIC_TIM3;
	NVIC_InitTypeDef NVIC_TIM5;

	// Enable the TIM3 Update Interrupt and TIM10 global interrupt
	NVIC_TIM3.NVIC_IRQChannel =   TIM3_IRQn;
	NVIC_TIM3.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_TIM3.NVIC_IRQChannelSubPriority = 0;
	NVIC_TIM3.NVIC_IRQChannelCmd = ENABLE;

	// Enable the TIM2 global Interrupt
	NVIC_TIM2.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_TIM2.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_TIM2.NVIC_IRQChannelSubPriority = 0;
	NVIC_TIM2.NVIC_IRQChannelCmd = ENABLE;

	// Enable the TIM5 global Interrupt
	NVIC_TIM5.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_TIM5.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_TIM5.NVIC_IRQChannelSubPriority = 0;
	NVIC_TIM5.NVIC_IRQChannelCmd = ENABLE;

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	NVIC_Init(&NVIC_TIM2);
	NVIC_Init(&NVIC_TIM3);
	NVIC_Init(&NVIC_TIM5);
}
