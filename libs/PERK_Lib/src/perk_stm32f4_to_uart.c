#include <perk_stm32f4_to_usart.h>

void USART3_INIT(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3); 	//    Connect PXx to USARTx_Tx
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3); 	//     Connect PXx to USARTx_Rx

	//     Configure USART Tx as alternate function
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//     Configure USART Rx as alternate function
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//     USART configuration
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART3, ENABLE);
}


void USART3_Send_String(char TxBuffer[]){
	u8 TxCounter = 0;
	while(TxCounter <= strlen(TxBuffer)){
		if(TxBuffer[TxCounter] != 0x00) USART_SendData(USART3, TxBuffer[TxCounter]);
		while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
		TxCounter++;
	}
}

void USART3_Send_Number(int number){
	u8 TxBufferSize;
	u8 TxBuffer[65];
	u8 i = 0;
	u8 neg = 0;

	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);

	if (number == 0){
		TxBuffer[i] = 0x30;
		i++;
	}

	else{
		if (number < 0){
			number = -1*number;
			neg = 1;
		}

		while(number > 0){
			TxBuffer[i] = ( (number%10) + 0x30 );
			number = number/10;
			i++;
		}
	}

	if (neg){
		TxBuffer[i] = 0x2D;
		i++;
	}

	TxBuffer[i] = 0x00;
	TxBufferSize = i;
	i = 0;

	while(i <= TxBufferSize){
		if(TxBuffer[TxBufferSize - i] != 0x00){
			USART_SendData(USART3, TxBuffer[TxBufferSize - i]);
			while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
		}
		i++;
	}
}
