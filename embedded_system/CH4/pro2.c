#include "stm32f4xx_hal.h"
int main() {
	int no_key = 0; // S1 ??? ?? ??
  int in_key_s1, past_key_s1 = 0;
  int in_key_s4;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	HAL_Init();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|
	GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT; // A ?? ?? 8??? ???? ????.
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	while (1) {
        
        in_key_s4 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4);
        if (in_key_s4 == GPIO_PIN_SET ||no_key == 9) {
            no_key = 0; // ??? ???
            GPIOC->ODR = 0x00; // ?? LED ??
        }

        
        in_key_s1 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0|GPIO_PIN_1);
        if ((past_key_s1 == 0) && (in_key_s1 != 0)) { 
							

                no_key++; 
                GPIOC->ODR = (1 <<  (no_key)) - 1; 
            
        }
        past_key_s1 = in_key_s1;
    }
}


