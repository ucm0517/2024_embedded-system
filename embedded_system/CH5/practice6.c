#include "stm32f4xx_hal.h"

const char FONT[6] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20 }; //0, 1, 2, 3, 4, 5



int main() {
    GPIO_InitTypeDef GPIO_InitStructure;
    HAL_Init();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    // Setup GPIOC for segment control
    GPIO_InitStructure.Pin = 0xFF;  // Assume all pins of GPIOC are used for segments
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
		HAL_GPIO_WritePin(GPIOC, 0xFF, GPIO_PIN_RESET);
    
    // Setup GPIOA for button inputs
    GPIO_InitStructure.Pin = 0xFF;  // Assume pins 0-7 of GPIOA are used for buttons
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		int in_key, past_key, val =0;
	
		while(1) {
				in_key = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_7);  // Read S1 and S2 and S8 simultaneously
				// Check if S1 (pin 0) is pressed
				if((past_key && GPIO_PIN_0 == 0) && (in_key &&GPIO_PIN_0 != 0)) {
						if ( val>=5) 
							val =0;
						else 
							val++;

				}
				if((past_key && GPIO_PIN_1 == 0) && (in_key &&GPIO_PIN_0 != 0)) {  // Check if S2 (pin 1) is pressed 
						if ( val<=0) 
							val =5;
						else 
							val--;

				}
				// Check if S8 (pin 7) is pressed
				if ((past_key & GPIO_PIN_7) == 0 && (in_key & GPIO_PIN_7) != 0) {
            val = 0;  // Reset count to 5 if S8 is pressed
        }
				// Update the seven-segment display with the current count
        HAL_GPIO_WritePin(GPIOC, 0xFF, GPIO_PIN_RESET);  // Reset all segments
        HAL_GPIO_WritePin(GPIOC, FONT[val], GPIO_PIN_SET);  // Display current count

        past_key = in_key;  // Update past_key to the current in_key
    
		}
			
}