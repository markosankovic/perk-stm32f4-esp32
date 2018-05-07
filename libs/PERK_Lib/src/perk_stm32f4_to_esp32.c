#include <perk_stm32f4_to_esp32.h>

void SPI1_send(uint16_t data){
	GPIO_SetBits(GPIOD, GPIO_Pin_13);
	SPI1->DR = data;
	while( !(SPI1->SR & SPI_I2S_FLAG_TXE) );
	while( !(SPI1->SR & SPI_I2S_FLAG_RXNE) );
	while( SPI1->SR & SPI_I2S_FLAG_BSY );
	GPIO_ResetBits(GPIOD, GPIO_Pin_13);
}

void GPIO_SPI1_INIT(void){
   GPIO_InitTypeDef GPIO_InitStructure;
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOD, ENABLE);
  
// PORTA configuration (SPI1 lines)
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_Init(GPIOA, &GPIO_InitStructure);

   GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

// PORTD configuration (chip select pin)
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void SPI1_INIT(void){
    SPI_InitTypeDef SPI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

    SPI_Cmd(SPI1, DISABLE);
    SPI_I2S_DeInit(SPI1);
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 0;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_Init(SPI1, &SPI_InitStructure);

    SPI_Cmd(SPI1, ENABLE);
}

// Timer 5 configuration
void TIM5_INIT(void){
	uint32_t fsend = 1500; 						// Frequency of sending data via SPI
	uint16_t send_prescaler = 0;			 	// Prescaler for sending data via SPI, value 83 means clock of 1MHz

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = (uint32_t) (SystemCoreClock/fsend/(send_prescaler + 1)/2/4 - 1);
	TIM_TimeBaseStructure.TIM_Prescaler = send_prescaler;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM5, ENABLE);
}

// DAC monitor initialization function.
void PERK_stm32f4_to_esp32_INIT(void){
	GPIO_SPI1_INIT();
	SPI1_INIT();
	TIM5_INIT();

}
