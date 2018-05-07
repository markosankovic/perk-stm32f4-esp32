#ifndef PERK_serial_INIT
#define PERK_serial_INIT

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_conf.h"

#define DBGU_RX_BUFFER_SIZE 256
#define TEST_BUFFERSIZE 128
#define UDP_NUM_PKT 10
#define SYSTICK_FREQUENCY_HZ       1000

void USART3_INIT(void);
void USART3_Send_String(char TxBuffer[]);
void USART3_Send_Number(int number);

#endif
