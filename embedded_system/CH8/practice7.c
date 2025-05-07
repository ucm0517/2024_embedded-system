#include "stm32f4xx_hal.h"
#include <stdio.h>

// UART1 �ʱ�ȭ �Լ� ����
void UART1_Init(void);

// ���� ���� ����
int t_cnt = 0, s_cnt = 0;
int led_idx = 0;  // ���� LED �ε����� ������ ����

// TIM7 �ڵ鷯 �ܺ� ����
extern TIM_HandleTypeDef htim7;

// Ÿ�̸� �Ⱓ ��� �ݹ� �Լ�
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM7) { // TIM7 �ν��Ͻ� Ȯ��
        HAL_GPIO_WritePin(GPIOC, 0xFFFF, GPIO_PIN_RESET);  // ��� LED�� ��
        HAL_GPIO_WritePin(GPIOC, 1 << led_idx, GPIO_PIN_SET);  // ���� �ε����� LED�� ��
        led_idx = (led_idx + 1) % 10;  // ���� LED �ε����� ������Ʈ (0~9���� ��ȯ)
    }
}

// Ÿ�̸� �ʱ�ȭ �Լ�
void TIMx_Init() {
    // TIM7 Ŭ�� Ȱ��ȭ
    __HAL_RCC_TIM7_CLK_ENABLE();
    
    // TIM7 �ʱ�ȭ ����
    htim7.Instance = TIM7;
    htim7.Init.Prescaler = 16000 - 1; // ���������Ϸ� ���� (16MHz/16000 = 1kHz, 1ms)
    htim7.Init.Period = 999; // Ÿ�̸� �ֱ� ���� (1000-1, 1�ʸ��� ���ͷ�Ʈ �߻�)
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
    GPIO_InitStruct.Pin = 0xFFFF; // ��Ʈ C�� ��� �� ���� (16��Ʈ, LED 0-15)
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