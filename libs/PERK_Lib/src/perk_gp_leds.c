#include <perk_gp_leds.h>

void LED_INIT(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = LED_1 | LED_2 | LED_3 | LED_4; // PINs PE11 - PE14
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOE, LED_1 | LED_2 | LED_3 | LED_4);
}

void LED_ON(uint16_t User_LED_no){
	GPIO_SetBits(GPIOE, User_LED_no);
}

void LED_OFF(uint16_t User_LED_no){
	GPIO_ResetBits(GPIOE, User_LED_no);
}

void LED_TOGGLE(uint16_t User_LED_no){
	if (GPIO_ReadInputDataBit(GPIOE, User_LED_no) == SET)
		GPIO_ResetBits(GPIOE, User_LED_no);
	else
		GPIO_SetBits(GPIOE, User_LED_no);
}
