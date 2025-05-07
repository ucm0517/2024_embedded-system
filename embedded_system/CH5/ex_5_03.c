#include "stm32f4xx_hal.h"
const char FONT[17] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, //0, 1, 2, 3, 4, 5
0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, //6, 7, 8, 9, A, b
0x39, 0x5E, 0x79, 0x71, 0x00 };//b, C, d, E, F, NULL
int main() {
GPIO_InitTypeDef GPIO_InitStructure;
HAL_Init();
__HAL_RCC_GPIOB_CLK_ENABLE();
__HAL_RCC_GPIOC_CLK_ENABLE();
GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
GPIO_InitStructure.Pull = GPIO_NOPULL;
GPIO_InitStructure.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|
GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
HAL_GPIO_WritePin(GPIOC, 0xFF, GPIO_PIN_RESET);
// B??? 12~15 ?? ?? ‘0’?? ?????? 7-???? 4?? ? ??.
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET); 
unsigned char i;
while(1) {
for(i=0; i<17; i++) {
HAL_GPIO_WritePin(GPIOC, FONT[i], GPIO_PIN_SET);
HAL_Delay(500);
HAL_GPIO_WritePin(GPIOC, FONT[i], GPIO_PIN_RESET);
}
}
}
