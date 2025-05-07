#include "stm32f4xx_hal.h"

int main() {
	GPIO_InitTypeDef GPIO_InitStructure = {0};
	HAL_Init();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	/*Configure GPIO pins : PC0 PC1 PC2 PC3 PC4 PC5 PC6 PC7 */
	GPIO_InitStructure.Pin = 0xFFFF;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	char i = 0;
  int direction = 1; // ??? 1, ??? -1? ??

    while(1) {
        GPIOC->ODR = 1 << i;  // ?? ??? i? ?? HIGH ??? ??
        HAL_Delay(500);       // 500 ??? ?? ??

        if ((i == 15 && direction == 1) || (i == 0 && direction == -1)) {
            direction = -direction;  // ?? ??
        }

        i += direction;  // ??? ?? ??? ?? ?? ??
    }
}
