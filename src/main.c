#include "main.h"

#define f_switching 50000
#define f_control 10000
#define Signal_array_elements 120

const uint32_t T_control = SysCoreClk/2/f_control - 1;
const uint32_t T_switching = SysCoreClk/2/f_switching - 1;
const uint8_t Dead_time = 50;
const uint32_t duty_max = SysCoreClk/2/f_switching - 1;
const uint32_t BaudRate = 115200;

uint16_t ADCConvertedValues[3] = {0 ,0, 0};

// Look-up table of dummy signal for communication test. Signal has 120 samples and represents sinewave.
uint16_t test_Samples[] = {
		2048, 2134, 2219, 2304, 2389, 2472, 2554, 2635, 2714, 2792, 2867, 2940,
		3011, 3079, 3144, 3207, 3266, 3321, 3373, 3422, 3467, 3508, 3545, 3578,
		3606, 3631, 3651, 3666, 3677, 3684, 3686, 3684, 3677, 3666, 3651, 3631,
		3606, 3578, 3545, 3508, 3467, 3422, 3373, 3321, 3266, 3207, 3144, 3079,
		3011, 2940, 2867, 2792, 2714, 2635, 2554, 2472, 2389, 2304, 2219, 2134,
		2048, 1962, 1877, 1792, 1707, 1624, 1542, 1461, 1382, 1304, 1229, 1156,
		1085, 1017, 952, 889, 830, 775, 723, 674, 629, 588, 551, 518, 490, 465,
		445, 430, 419, 412, 410, 412, 419, 430, 445, 465, 490, 518, 551, 588,
		629, 674, 723, 775, 830, 889, 952, 1017, 1085, 1156, 1229, 1304, 1382,
		1461, 1542, 1624, 1707, 1792, 1877, 1962};

// Counters which are used to simulate three-phase sinewave system.
uint16_t test_cnt_1 = 0;
uint16_t test_cnt_2 = 1*Signal_array_elements/3;
uint16_t test_cnt_3 = 2*Signal_array_elements/3;

int main(void){
	// Initialization of peripherals on STM32Discovery board
	DEMO_LED_INIT();
	DEMO_Taster_INIT();
	DEMO_LED_ON(LED_green);
	DEMO_LED_ON(LED_red);


	// Initialization of two serial communication peripherals.
	USART3_INIT(); // USART3 is used for monitoring via serial port monitor (GTKTerm).
	PERK_stm32f4_to_esp32_INIT(); // SPI1 is used for sending data from STM32 to ESP32.

	PWM_INIT(T_control, T_switching, Dead_time);

	NVIC_INIT();

	while(1){
		if (DEMO_Taster_Status(Taster_1)==1)
			DEMO_LED_TOGGLE(LED_blue);
	}
}

// Handler for TIM5, sending the data SPI
// Sending from STM32 to ESP32 16 samples, each of them corresponds to once channel of communication.
// At this point, code sends 16 separate values, which can be optimized by merging them into one long sequence.
// Timer 5 is chosen since it will not be used for PWM generation and its interrupt priority can be low.
// Later, SPI communication can be further optimized by using direct memory access (DMA).
void TIM5_IRQHandler(void){
	if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET){

		USART3_Send_Number(test_Samples[test_cnt_1]);
		USART3_Send_String("\n\r");

		SPI1_send(test_Samples[test_cnt_1]); // Dummy signal for channel 1
		SPI1_send(test_Samples[test_cnt_2]); // Dummy signal for channel 2
		SPI1_send(test_Samples[test_cnt_3]); // Dummy signal for channel 3

		SPI1_send(test_Samples[test_cnt_1]*test_Samples[test_cnt_2]); // Dummy signal for channel 4
		SPI1_send(test_Samples[test_cnt_2]*test_Samples[test_cnt_3]); // Dummy signal for channel 5
		SPI1_send(test_Samples[test_cnt_3]*test_Samples[test_cnt_1]); // Dummy signal for channel 6

		SPI1_send(800); 	// Dummy signal for channel 7
		SPI1_send(900); 	// Dummy signal for channel 8
		SPI1_send(1000); 	// Dummy signal for channel 9
		SPI1_send(1100); 	// Dummy signal for channel 10
		SPI1_send(1200);	// Dummy signal for channel 11
		SPI1_send(1300);	// Dummy signal for channel 12
		SPI1_send(1400);	// Dummy signal for channel 13
		SPI1_send(1500);	// Dummy signal for channel 14
		SPI1_send(1600);	// Dummy signal for channel 15
		SPI1_send(1700);	// Dummy signal for channel 16

		test_cnt_1 = test_cnt_1 + 1;
		if(test_cnt_1 >= Signal_array_elements)
			test_cnt_1 = 0;

		test_cnt_2 = test_cnt_2 + 1;
		if(test_cnt_2 >= Signal_array_elements)
			test_cnt_2 = 0;

		test_cnt_3 = test_cnt_3 + 1;
		if(test_cnt_3 >= Signal_array_elements)
			test_cnt_3 = 0;

		TIM_ClearFlag(TIM5, TIM_FLAG_Update);
	}
}
