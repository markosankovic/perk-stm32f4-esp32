#include "perk_gp_tasters.h"

uint8_t Button_status[8] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t Button_status_old[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void Buttons_INIT(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = Button_1 | Button_2 | Button_3 | Button_4; // PINs PE0 - PE3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

uint8_t Button_Status(const uint16_t User_button){
	uint8_t status = 0;
	Button_status[User_button] = GPIO_ReadInputDataBit(GPIOE, User_button);

	if( (Button_status_old[User_button] != Button_status[User_button]) && (Button_status[User_button] == 1) ){
		status = 1;
	}
	Button_status_old[User_button] = Button_status[User_button];
	return status;

}
