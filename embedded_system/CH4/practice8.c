#include "stm32f4xx.h"

int main() {
	
	GPIO_InitTypeDef GPIO_InitStructure;
	HAL_Init();
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Pin = 0xFF;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = 0xFF;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT; // A ?? ?? 8??? ???? ????.
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	while(1) {
			unsigned char in_data;
		
		in_data = (GPIOA->IDR)&0xFF;
		switch(in_data) {
			case 0x01:
				GPIOC->ODR = 0x01;
			break;
			case 0x02:
				GPIOC->ODR = 0x03;
			break;
			case 0x04:
				GPIOC->ODR = 0x07;
			break;
			case 0x08:
				GPIOC->ODR = 0x0F;
			break;
			case 0x10:
				GPIOC->ODR = 0x1F;
			break;
			case 0x20:
				GPIOC->ODR = 0x3F;
			break;
			case 0x40:
				GPIOC->ODR = 0x7F;
			break;
			case 0x80:
				GPIOC->ODR = 0xFF;
			break;
			default:
				GPIOC->ODR = 0x00;
			break;
		}
	}
}
