#include "stm32f4xx_hal.h"
#include	<stdio.h>

extern	UART_HandleTypeDef huart1;
void UART1_Init() {
	__HAL_RCC_USART1_CLK_ENABLE();

	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	HAL_UART_Init(&huart1);
	
	GPIO_InitTypeDef   GPIO_InitStruct;
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;			//	PA9     ------> USART1_TX
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;						//	PA10    ------> USART1_RX 
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

int fputc(int ch, FILE *f) {
	/* write a character to the uart1 and Loop until the end of transmission */
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 10); 
	return ch;
}
