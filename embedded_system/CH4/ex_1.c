#include "stm32f4xx_hal.h"
int main() {
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
GPIO_InitStructure.Mode = GPIO_MODE_INPUT; 
HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
while(1) {
GPIOC->ODR = (GPIOA->IDR) & 0x000F;
}
}
