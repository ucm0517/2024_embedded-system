#include "stm32f4xx.h"

int main() {
    GPIO_InitTypeDef GPIO_InitStructure;
    HAL_Init();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    // GPIOC ?? (LED ??)
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Pin = 0xFF;  // ?? ? ??
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    // GPIOA ?? (?? ??)
    GPIO_InitStructure.Pin = 0xFF;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    int input_key = 0;  // ?? LED ??
    int input_keyS1, past_keyS1 = 0;
    int input_keyS3;
    
    while(1) {
        input_keyS3 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4);
        if (input_keyS3 == GPIO_PIN_SET) {
            input_key = 0; // ???
            GPIOC->ODR = 0x01; // ? ?? LED ??
        }

        input_keyS1 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
        if ((past_keyS1 == 0) && (input_keyS1 != 0)) {
            input_key++; // input_key ??
            if (input_key > 7) { // 7?? ?? (8?? LED? ?? ??)
                input_key = 0; // ?? ???
            }
            GPIOC->ODR = (1 << input_key); // ?? ??? LED ??
        }
        past_keyS1 = input_keyS1; // ?? ? ?? ??
    }
}

