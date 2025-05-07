#include "stm32f4xx_hal.h"

int main() {
    HAL_Init(); // HAL ????? ???
    __HAL_RCC_GPIOC_CLK_ENABLE(); // GPIOC ?? ?? ???

    // GPIOC ?? ??? ??? ? ??
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.Pin = GPIO_PIN_All; // ?? ? ???
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; // ?? ??? ??
    GPIO_InitStructure.Pull = GPIO_NOPULL; // ??/??? ?? ??
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW; // ?? ??? ??
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructure); // GPIOC ???
		char i=0;
		
    while(1) {
        GPIOC->ODR = 1 << i | 1 << (15-i); //every get 1 but not i            
				HAL_Delay(500);
				i=(i+1)%8;
			
				if (i == 0) {
            for (char j = 7; j > 0; j--) {
                GPIOC->ODR = (1 << j) | (1 << ( 15- j)); // ?? ??? LED ??
                HAL_Delay(500); // 500ms ??
						}
        }
    }
	}

/*
char i=0;
while(1) {
   GPIOC->ODR = 1 << i || 1<<(7-i); //every get 1 but not i            
   HAL_Delay(500);
   i=(i+1)%4;
 }
}
*/