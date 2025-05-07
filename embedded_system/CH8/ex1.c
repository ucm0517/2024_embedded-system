#include "stm32f4xx_hal.h"
#include <stdio.h>

// UART1 �ʱ�ȭ �Լ� ����
void UART1_Init(void);

// GPIO �ʱ�ȭ �Լ�
void GPIOx_Init() {
    // GPIOA Ŭ�� Ȱ��ȭ
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    // GPIO ���� ����ü ���� �� �ʱ�ȭ
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = GPIO_PIN_0;              // ��Ʈ A�� 0�� �� ����
    GPIO_InitStruct.Pull = GPIO_PULLUP;            // Ǯ�� ����
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;        // Ǫ��Ǯ ��� ���
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;     // TIM2�� ��ü ������� ����
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);        // GPIOA �ʱ�ȭ
}

// TIM2 �ڵ鷯 �ܺ� ����
extern TIM_HandleTypeDef htim2;

// Ÿ�̸� �ʱ�ȭ �Լ�
void TIMx_Init() {
    // Ÿ�̸� Ŭ�� ���� ����ü ���� �� �ʱ�ȭ
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    
    // TIM2 Ŭ�� Ȱ��ȭ
    __HAL_RCC_TIM2_CLK_ENABLE();
    
    // TIM2 �ʱ�ȭ ����
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 0;                        // ���������Ϸ� ���� (Ŭ�� ���� ����)
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;     // ��ī���� ���
    htim2.Init.Period = 9999;                        // 0 ~ 9999 (ī���� �ֱ�)
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; // Ŭ�� ���� ����
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE; // �ڵ� ���ε� �����ε� ��Ȱ��ȭ
    HAL_TIM_Base_Init(&htim2);                       // TIM2 �ʱ�ȭ
    
    // Ÿ�̸� Ŭ�� �ҽ� ����
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_ETRMODE2; // �ܺ� Ʈ���� ��� 2 ����
    sClockSourceConfig.ClockPolarity = TIM_CLOCKPOLARITY_INVERTED; // Ŭ�� ����Ƽ ����
    sClockSourceConfig.ClockPrescaler = TIM_CLOCKPRESCALER_DIV1;   // Ŭ�� ���� ����
    sClockSourceConfig.ClockFilter = 15;                           // Ŭ�� ���� ���� (ä�͸� ����)
    HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig);        // TIM2 Ŭ�� �ҽ� ����
    
    // Ÿ�̸� ����
    HAL_TIM_Base_Start(&htim2);
}

int main() {
    int val;
    
    // HAL ���̺귯�� �ʱ�ȭ
    HAL_Init();
    
    // UART1 �ʱ�ȭ
    UART1_Init();
    
    // GPIO �ʱ�ȭ
    GPIOx_Init();
    
    // Ÿ�̸� �ʱ�ȭ
    TIMx_Init();
    
    while (1) {
        // TIM2�� ī���� �� �б�
        val = __HAL_TIM_GetCounter(&htim2); //TIM2->CNT;
        
        // ī���� �� ���
        printf("COUNTER VAL : %d\r\n", val);
        
        // 200ms ������
        HAL_Delay(200);
    }
}