#include "stm32f4xx_hal.h"

// TIM10 �ڵ鷯 �ܺ� ����
extern TIM_HandleTypeDef htim10;

int main(void) {
    // GPIO ���� ����ü �� Ÿ�̸� ��� �� ���� ����ü ����
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_OC_InitTypeDef sConfigOC;
    
    // HAL ���̺귯�� �ʱ�ȭ
    HAL_Init();
    
    // GPIOB Ŭ�� Ȱ��ȭ
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    // TIM10 Ŭ�� Ȱ��ȭ
    __HAL_RCC_TIM10_CLK_ENABLE();
    
    // GPIOB �� 8�� TIM10�� ��ü ������� ����
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;  // Ǫ��Ǯ ��� ���
    GPIO_InitStruct.Pull = GPIO_NOPULL;      // Ǯ��/Ǯ�ٿ� ����
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  // ���� �ӵ�
    GPIO_InitStruct.Alternate = GPIO_AF3_TIM10;   // TIM10 ��ü ���
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);  // GPIOB �ʱ�ȭ
    
    // TIM10 �ʱ�ȭ ����
    htim10.Instance = TIM10;
    htim10.Init.Prescaler = 16 - 1;  // ���������Ϸ� ���� (16MHz/16 = 1MHz)
    htim10.Init.CounterMode = TIM_COUNTERMODE_UP;  // ��ī���� ���
    htim10.Init.Period = 17000 - 1;  // Ÿ�̸� �ֱ� ���� (60Hz)
    htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;  // Ŭ�� ���� ����
    htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;  // �ڵ� ���ε� �����ε� ��Ȱ��ȭ
    HAL_TIM_PWM_Init(&htim10);  // TIM10 �ʱ�ȭ
    
    // PWM ��� �� ����
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;  // �ʱ� �޽� �� ����
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim10, &sConfigOC, TIM_CHANNEL_1);  // TIM10 ä�� 1 ����
    
    // TIM10 PWM ��� ����
    HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
    
    while (1) {
        // ��Ƽ ����Ŭ�� õõ�� ��ȭ��Ű�� PWM ��ȣ ����
        for (int i = 0; i < 30000; i += 1000) {
            htim10.Instance->CCR1 = i;  // PWM ��Ƽ ����Ŭ ����
            __HAL_TIM_SET_COMPARE(&htim10, TIM_CHANNEL_1, i);  // TIM10 �� �������� ����
            HAL_Delay(100);  // 100ms ������
        }
    }
}