#include <perk_pwm_control.h>

void TIM1_INIT(uint32_t T_switching, uint8_t Dead_time){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OC1;
	TIM_OCInitTypeDef TIM_OC2;
	TIM_OCInitTypeDef TIM_OC3;
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;

	TIM_TimeBaseStructure.TIM_Period = T_switching;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	/* 	Inicilajlizacija Output Compare 1, pinovi E8 i E9	*/
	TIM_OC1.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC1.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OC1.TIM_Pulse = 0;
	TIM_OC1.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OC1.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OC1.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);

	/* 	Inicilajlizacija Output Compare 2, pinovi E10 i E11	*/
	TIM_OC2.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC2.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC2.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OC2.TIM_Pulse = 0; // Starting duty ratio is 0%
	TIM_OC2.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC2.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OC2.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OC2.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);

	/* 	Inicilajlizacija Output Compare 3, pinovi E12 i E13	*/
	TIM_OC3.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC3.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC3.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OC3.TIM_Pulse = 0;
	TIM_OC3.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OC3.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OC3.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);


	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Disable;
	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Disable;
	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
	TIM_BDTRInitStructure.TIM_DeadTime = Dead_time;//185;
	TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
	TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
	TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);

	TIM_OC1Init(TIM1, &TIM_OC1);
	TIM_OC2Init(TIM1, &TIM_OC2);
	TIM_OC3Init(TIM1, &TIM_OC3);
}

void TIM2_INIT(uint32_t T_control, uint32_t T_switching){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_2;

	TIM_2.TIM_Period = T_control;
	TIM_2.TIM_Prescaler = 0;
	TIM_2.TIM_ClockDivision = 0;
	TIM_2.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_2);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}

void TIM3_INIT(uint32_t T_control, uint32_t T_switching){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_3;
	TIM_3.TIM_Period = T_switching/2;
	TIM_3.TIM_Prescaler = 0;
	TIM_3.TIM_ClockDivision = 0;
	TIM_3.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_3);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	TIM_Cmd(TIM1, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
}

void PWM_PINs_INIT(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 ;	// PINs PE8 PE9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	// Connect TIM pins to AF1
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);
}

void PWM_INIT(uint32_t T_control, uint32_t T_switching, uint8_t Dead_time){

	PWM_PINs_INIT();
	TIM1_INIT(T_switching, Dead_time);
	TIM2_INIT(T_control, T_switching);
	TIM3_INIT(T_control, T_switching);
}
