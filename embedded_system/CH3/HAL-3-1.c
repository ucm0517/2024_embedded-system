// stm32f4xx? 
#include "stm32f4xx_hal.h"
int main() {
  GPIO_InitTypeDef GPIO_InitStructure = {0};
  HAL_Init();
  __HAL_RCC_GPIOC_CLK_ENABLE();
	
  /*Configure GPIO pins : PC0 PC1 PC2 PC3 PC4 PC5 PC6 PC7 */
  GPIO_InitStructure.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
	char i=0;
  while(1) {
						GPIOC->ODR=1<<i;
						HAL_Delay(500);
						i = (i+1)%8;
  }
}
