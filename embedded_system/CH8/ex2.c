#include "stm32f4xx_hal.h"
#include <stdio.h>

// UART1 �ʱ�ȭ �Լ� ����
void UART1_Init(void);

// Ÿ�̸ӿ� �� ī���� ���� ����
int t_cnt = 0, s_cnt = 0;

// TIM7 �ڵ鷯 �ܺ� ����
extern TIM_HandleTypeDef htim7;

// Ÿ�̸� �Ⱓ ��� �ݹ� �Լ�
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM7) { // TIM7 �ν��Ͻ� Ȯ��
        if ((++t_cnt) > 999) { // t_cnt�� 999�� �ʰ��ϸ�
            t_cnt = 0; // t_cnt�� 0���� �ʱ�ȭ
            s_cnt++; // �� ī���� ����
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_0); // GPIOC�� 0�� �� ���
        }
    }
}

// Ÿ�̸� �ʱ�ȭ �Լ�
void TIMx_Init() {
    // TIM7 Ŭ�� Ȱ��ȭ
    __HAL_RCC_TIM7_CLK_ENABLE();
    
    // TIM7 �ʱ�ȭ ����
    htim7.Instance = TIM7;
    htim7.Init.Prescaler = 16 - 1; // ���������Ϸ� ���� (16MHz/16 = 1MHz, 1us)
    htim7.Init.Period = 999; // Ÿ�̸� �ֱ� ���� (1000-1, 1ms)
    htim7.Init.CounterMode = TIM_COUNTERMODE_UP; // ��ī���� ���
    HAL_TIM_Base_Init(&htim7); // TIM7 �ʱ�ȭ
    
    // TIM7 ���ͷ�Ʈ ����
    HAL_NVIC_ClearPendingIRQ(TIM7_IRQn); // ���ͷ�Ʈ ��� �÷��� Ŭ����
    HAL_NVIC_SetPriority(TIM7_IRQn, 7, 0); // ���ͷ�Ʈ �켱���� ����
    HAL_NVIC_EnableIRQ(TIM7_IRQn); // ���ͷ�Ʈ ���
    HAL_TIM_Base_Start_IT(&htim7); // Ÿ�̸� ���ͷ�Ʈ ��� ����
}

// GPIO �ʱ�ȭ �Լ�
void GPIOx_Init() {
    // GPIOC Ŭ�� Ȱ��ȭ
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    // GPIO ���� ����ü ���� �� �ʱ�ȭ
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Ǫ��Ǯ ��� ���
    GPIO_InitStruct.Pull = GPIO_NOPULL; // Ǯ ����
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // ���� �ӵ�
    GPIO_InitStruct.Pin = 0xFF; // ��Ʈ C�� ��� �� ����
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct); // GPIOC �ʱ�ȭ
}

int main() {
    // HAL ���̺귯�� �ʱ�ȭ
    HAL_Init();
    
    // UART1 �ʱ�ȭ
    UART1_Init();
    
    // GPIO �ʱ�ȭ
    GPIOx_Init();
    
    // Ÿ�̸� �ʱ�ȭ
    TIMx_Init();
    
    while (1) {
        // �� ī���� ���� ���
        printf("Timer in SEC : %4d\r", s_cnt);
    }
}