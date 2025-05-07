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
GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
while(1) {
unsigned char in_data;
in_data = (GPIOA->IDR) & 0x0003; //0000 0000 0000 0011
switch( in_data ) {
case 0x03 : 
GPIOC->ODR = 0x81;
break;
case 0x02 : 
GPIOC->ODR = 0x80;
break;
case 0x01 : 
GPIOC->ODR = 0x01;
break;
case 0x00 : 
GPIOC->ODR = 0x00;
break;
default :
GPIOC->ODR = 0xFF;
break;
}
}
}
