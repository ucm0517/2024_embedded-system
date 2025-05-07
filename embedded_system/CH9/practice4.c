#include "stm32f4xx_hal.h"

// TIM10 �ڵ鷯 �ܺ� ����
extern TIM_HandleTypeDef htim10;

int main(void) {
    // GPIO ���� ����ü �� Ÿ�̸� ��� �� ���� ����ü ����
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_OC_InitTypeDef sConfigOC;
    
    // HAL ���̺귯�� �ʱ�ȭ
    HAL_Init();
    
    // GPIOB�� GPIOA Ŭ�� Ȱ��ȭ
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_TIM10_CLK_ENABLE();
    
    // GPIOA �ʱ�ȭ (SW0 ~ SW3)
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // GPIOB �ʱ�ȭ (PWM ���)
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF3_TIM10;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    // TIM10 �ʱ�ȭ ����
    htim10.Instance = TIM10;
    htim10.Init.Prescaler = 16 - 1; // ���������Ϸ� ���� (16MHz/16 = 1MHz)
    htim10.Init.CounterMode = TIM_COUNTERMODE_UP; // ��ī���� ���
    htim10.Init.Period = 10000 - 1; // Ÿ�̸� �ֱ� ���� (10000-1)
    htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; // Ŭ�� ���� ����
    htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE; // �ڵ� ���ε� �����ε� ��Ȱ��ȭ
    HAL_TIM_PWM_Init(&htim10); // TIM10 �ʱ�ȭ
    
    // PWM ��� �� ����
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0; // �ʱⰪ 0%
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim10, &sConfigOC, TIM_CHANNEL_1); // TIM10 ä�� 1 ����
    
    // TIM10 PWM ��� ����
    HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
    
    // ���� �ʱ�ȭ
    int cv = 0;
    GPIO_PinState in_key;
    GPIO_PinState past_key = GPIO_PIN_RESET;

    while (1) {
        // SW0 �� ���� �б�
        in_key = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
        
        // ����ġ�� ���� ��� ó���� �۾�
        if((past_key == GPIO_PIN_RESET) && (in_key != GPIO_PIN_RESET)) {
            // ��Ƽ ����Ŭ ����
            cv = (cv + 1) % 5; // cv ���� 0���� 4���� ��ȯ
            
            switch (cv) {
                case 0:
                    htim10.Instance->CCR1 = 0; // 0%
                    break;
                case 1:
                    htim10.Instance->CCR1 = 2500 - 1; // 25%
                    break;
                case 2:
                    htim10.Instance->CCR1 = 5000 - 1; // 50%
                    break;
                case 3:
                    htim10.Instance->CCR1 = 7500 - 1; // 75%
                    break;
                case 4:
                    htim10.Instance->CCR1 = 10000 - 1; // 100%
                    break;
            }
        }
        
        // ���� Ű ���� ������Ʈ
        past_key = in_key;
        
        // ª�� �����̸� �߰��Ͽ� CPU ������ ���߰� ��ٿ�� ȿ��
        HAL_Delay(10);
    }
}