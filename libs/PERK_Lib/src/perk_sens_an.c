#include "perk_sens_an.h"

extern uint16_t ADCConvertedValues[3];

void ADC_INIT(void){

	ADC_InitTypeDef       ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;

	/* ADC Common Init **********************************************************/
	    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	    ADC_CommonInit(&ADC_CommonInitStructure);

	    /* ADC1 Init ****************************************************************/
	    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
//	    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T4_CC4;
	    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	    ADC_InitStructure.ADC_NbrOfConversion = 3;
	    ADC_Init(ADC1, &ADC_InitStructure);

	    /* ADC1 regular channel configuration ******************************/
	    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_3Cycles); // PA0
	    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_3Cycles); // PA1
	    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_3Cycles); // PA2

	    /* Enable DMA request after last transfer (Single-ADC mode) */
	    ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

	    /* Enable ADC1 DMA */
	    ADC_DMACmd(ADC1, ENABLE);

	    /* Enable ADC1 **************************************************************/
	    ADC_Cmd(ADC1, ENABLE);

	    /* Start ADC1 Software Conversion */
	    ADC_SoftwareStartConv(ADC1);
}

void DMA_for_ADC_init(void){
	DMA_InitTypeDef       DMA_InitStructure;

	/* DMA2_Stream0 channel0 configuration **************************************/
	DMA_DeInit(DMA2_Stream0);
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADCConvertedValues[0];
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = 3;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);

	/* DMA2_Stream0 enable */
	DMA_Cmd(DMA2_Stream0, ENABLE);
}

void ADC_PINs_INIT(void){
	GPIO_InitTypeDef GPIO_initStructre; //Structure for analogue input pin
	GPIO_initStructre.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2; // PINs PA0 - PA2
	GPIO_initStructre.GPIO_Mode = GPIO_Mode_AN;
	GPIO_initStructre.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_initStructre);
}

void Sensor_INIT(void){
//Clock configuration
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_DMA2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	DMA_for_ADC_init();
	ADC_PINs_INIT();
	ADC_INIT();

}

uint16_t Sensor_an_read(uint8_t Sensor_no){
	return ADCConvertedValues[Sensor_no-1];
}
