#include "stm32f4xx_hal.h"

// TIM2�� TIM4 �ڵ鷯 �ܺ� ����
extern TIM_HandleTypeDef htim2, htim4;

int main(void) {
    // GPIO ���� ����ü �� Ÿ�̸� ��� �� ���� ����ü ����
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_OC_InitTypeDef sConfigOC;
    
    // HAL ���̺귯�� �ʱ�ȭ
    HAL_Init();
    
    // GPIOB�� GPIOA Ŭ�� Ȱ��ȭ
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    // TIM2�� TIM4 Ŭ�� Ȱ��ȭ
    __HAL_RCC_TIM2_CLK_ENABLE();
    __HAL_RCC_TIM4_CLK_ENABLE();
    
    // GPIOA �� 0-3�� �Է� ���� ����
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // GPIOB �� 8-9�� TIM4�� ��ü ������� ����
    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    // GPIOB �� 10-11�� TIM2�� ��ü ������� ����
    GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    // TIM2 �ʱ�ȭ ����
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 15;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 10000 - 1;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_PWM_Init(&htim2);
    
    // TIM4 �ʱ�ȭ ����
    htim4.Instance = TIM4;
    htim4.Init.Prescaler = 15;
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim4.Init.Period = 10000 - 1;
    htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_PWM_Init(&htim4);
    
    // PWM ��� �� ����
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
		sConfigOC.Pulse = 2500 - 1;
    HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3);
    sConfigOC.Pulse = 5000 - 1;
    HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4);
    sConfigOC.Pulse = 7500 - 1;
    HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);
    sConfigOC.Pulse = 10000 - 1;
    HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4);
    
    while (1) {
        // GPIOA �� 0 ���� Ȯ�� �� TIM4 ä�� 3 PWM ����/����
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
            HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
            HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
        
        // GPIOA �� 1 ���� Ȯ�� �� TIM4 ä�� 4 PWM ����/����
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_SET)
            HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
            HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
        
        // GPIOA �� 2 ���� Ȯ�� �� TIM2 ä�� 3 PWM ����/����
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_SET)
            HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
            HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
        
        // GPIOA �� 3 ���� Ȯ�� �� TIM2 ä�� 4 PWM ����/����
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_SET)
            HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
            HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
        
        // 100ms ������
        HAL_Delay(100);
    }
}