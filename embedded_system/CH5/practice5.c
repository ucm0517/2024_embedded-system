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
    GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7;  // Setting PIN_0, PIN_1, and PIN_7 for input
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_PULLUP;  // Using pull-up
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

    int in_keyS1, past_keyS1 = 0;
    int in_keyS2, past_keyS2 = 0;
    int in_keyS8, past_keyS8 = 0;
    int count = 5;  // Initial counter value set to 5

    while (1) {
        // Read state of PIN_0 (S1 switch for increment)
        in_keyS1 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
        if ((past_keyS1 == 0) && (in_keyS1 != 0)) {
            count = (count + 1) % 10;  // Increment count and rollover at 10
            GPIOC->ODR = FONT[count];  // Display count on the seven-segment display
        }
        past_keyS1 = in_keyS1;  // Update past_keyS1

        // Read state of PIN_1 (S2 switch for decrement)
        in_keyS2 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1);
        if ((past_keyS2 == 0) && (in_keyS2 != 0)) {
            count = (count - 1 + 10) % 10;  // Decrement count and rollover at 0
            GPIOC->ODR = FONT[count];  // Display count on the seven-segment display
        }
        past_keyS2 = in_keyS2;  // Update past_keyS2

        // Read state of PIN_7 (S8 switch for reset)
        in_keyS8 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);
        if ((past_keyS8 == 0) && (in_keyS8 != 0)) {
            count = 5;  // Reset count to 5
            GPIOC->ODR = FONT[count];  // Reset display to 5
        }
        past_keyS8 = in_keyS8;  // Update past_keyS8

        HAL_Delay(50);  // Debounce delay
    }
}

