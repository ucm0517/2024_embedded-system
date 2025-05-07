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
		in_data = (GPIOA->IDR) & 0xFF;
		
		switch(in_data) {
 			case 0x01:  // Assuming PIN 0 is connected to S1
				for(int i = 0; i <= 7; i++) {
					GPIOC->ODR = (1 << i);
					HAL_Delay(100);  // Small delay to visually see the LED shifting
				}
				break;
			case 0x02:  // Assuming PIN 1 is connected to S2
				for(int j = 0; j <= 7; j++) {
					GPIOC->ODR = (1 << (7 - j));
					HAL_Delay(100);  // Small delay to visually see the LED shifting
				}
				break;
		}
	}
}
