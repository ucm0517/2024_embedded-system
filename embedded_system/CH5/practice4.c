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

    int in_keyS1, past_keyS1 = 0;
    int in_keyS8, past_keyS8 = 0;
    int count = 0;  // Counter for the number of button presses

    while (1) {
        // Read state of PIN_0 (S1 switch)
        in_keyS1 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
        if ((past_keyS1 == 0) && (in_keyS1 != 0)) {
            count = (count + 1) % 10;  // Increment count and rollover at 10
            GPIOC->ODR = FONT[count];  // Display count on the seven-segment display
        }
        past_keyS1 = in_keyS1;  // Update past_keyS1

        // Read state of PIN_7 (S8 switch)
        in_keyS8 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);
        if ((past_keyS8 == 0) && (in_keyS8 != 0)) {
            count = 0;  // Reset count
            GPIOC->ODR = FONT[count];  // Reset display to 0
        }
        past_keyS8 = in_keyS8;  // Update past_keyS8

        HAL_Delay(50);  // Debounce delay
    }
}
