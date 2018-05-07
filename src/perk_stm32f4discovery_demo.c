#include "perk_stm32f4discovery_demo.h"

uint8_t DEMO_Taster_status = 0;
uint8_t DEMO_Taster_status_old = 0;

void DEMO_LED_INIT(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = LED_green | LED_orange | LED_red | LED_blue; // PINs PD12 - PE15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOD, LED_green | LED_orange | LED_red | LED_blue);
}


void DEMO_Taster_INIT(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = Taster_1; // PINs PA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //GPIO_Speed_25MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void DEMO_LED_ON(uint16_t User_LED_no){
	GPIO_SetBits(GPIOD, User_LED_no);
}

void DEMO_LED_OFF(uint16_t User_LED_no){
	GPIO_ResetBits(GPIOD, User_LED_no);
}

void DEMO_LED_TOGGLE(uint16_t User_LED_no){
	if (GPIO_ReadInputDataBit(GPIOD, User_LED_no) == SET)
		GPIO_ResetBits(GPIOD, User_LED_no);
	else
		GPIO_SetBits(GPIOD, User_LED_no);
}

uint8_t DEMO_Taster_Status(const uint16_t DEMO_Taster){
	uint8_t status = 0;
	DEMO_Taster_status = GPIO_ReadInputDataBit(GPIOA, DEMO_Taster);

	if( (DEMO_Taster_status_old != DEMO_Taster_status) && (DEMO_Taster_status == 1) ){
		status = 1;
	}
	DEMO_Taster_status_old = DEMO_Taster_status;
	return status;

}
