#include "stm32f4xx_hal.h"

void segment(int v) {
    unsigned char FONT[18] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07,
                              0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x08, 0x80};
    static char SCAN;
    unsigned char digits[4] = {v % 10, (v / 10) % 10, (v / 100) % 10, (v / 1000) % 10};

    // Rotate digits based on SCAN position
    unsigned char display_digit = digits[SCAN];

    // Determine the GPIO pin based on SCAN
    uint16_t pin = GPIO_PIN_12 + SCAN; // Assume pins 12, 13, 14, 15 for FND 1, 2, 3, 4

    HAL_GPIO_WritePin(GPIOB, pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, FONT[display_digit], GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOB, pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, FONT[display_digit], GPIO_PIN_RESET);

    SCAN = (SCAN + 1) % 4;
}

int main() {
    GPIO_InitTypeDef GPIO_InitStructure;
    HAL_Init();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET);

    GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
                             GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

    int input_data, past_key = 0;
    unsigned int val = 0;
    while (1) {
        input_data = (GPIOA->IDR) & 0xFF;  // Read input from GPIOA
        val = input_data;  // Assign input value to val for display

        for (int i = 0; i < 100; i++)
            segment(val);  // Update display
    }
}

//???