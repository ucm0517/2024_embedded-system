#include "stm32f4xx_hal.h"

const char FONT[17] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,  // 0, 1, 2, 3, 4, 5
    0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C,  // 6, 7, 8, 9, A, b
    0x39, 0x5E, 0x79, 0x71, 0x00          // C, d, E, F, NULL
};

int main() {
    GPIO_InitTypeDef GPIO_InitStructure;
    HAL_Init();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // GPIOC initialization for output
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Pin = 0xFF;  // Initialize all pins
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

    // GPIOA initialization for input
    GPIO_InitStructure.Pin = GPIO_PIN_7;  // Setting only PIN_7 for input
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_NOPULL;  // Consider using GPIO_PULLUP
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

    int in_key, past_key = 0;
    int ss = 1;  // Start in "counting" mode
    int val = 0;

    while (1) {
        in_key = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);
        if ((past_key == 0) && (in_key != 0)) {
            ss = (ss + 1) % 2;  // Toggle the state
        }
        past_key = in_key;  // Update past_key

        if (ss == 1) {  // If not paused
            val = (val + 1) % 10;  // Increment value cyclically
            GPIOC->ODR = FONT[val];  // Directly write to output data register
        } else {
            // Optionally, hold the display at the current value
            GPIOC->ODR = FONT[val];
        }

        HAL_Delay(500);  // Delay to slow down the increment speed
    }
}






/*
int in_key, past_key = 0;
    int ss = 1;  // Start in "counting" mode
    int val = 0;

    while (1) {
        in_key = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);
        if ((past_key == 0) && (in_key != 0)) {
            ss = (ss + 1) % 2;  // Toggle the state
        }
        past_key = in_key;  // Update past_keyv

        if(ss == 1){
            HAL_GPIO_WritePin(GPIOC, FONT[val], GPIO_PIN_SET); // ‘5’ ?? ??
            HAL_Delay(500);
            HAL_GPIO_WritePin(GPIOC, FONT[val], GPIO_PIN_RESET);
            val =(val+1)%10;
    }
}
*/