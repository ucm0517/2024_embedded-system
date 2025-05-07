#include "stm32f4xx_hal.h"
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

	
	int input_data, past_key = 0;
	int no_key = 0;
	
	
	while (1) {
        
        input_data = (GPIOA->IDR) & 0xFF;
		
        if ((past_key == 0) && (input_data != 0)) {
            if( input_data & 0x01) {
							no_key++;
							GPIOC->ODR = ( 1 << no_key) -1;
						}
						if( (input_data & 0x08)  || no_key == 9) {
							
							GPIOC->ODR = 0x00;
							no_key = 0;
						}
						
					}
				past_key = input_data;
				}
				
			}
		
		
							

        


