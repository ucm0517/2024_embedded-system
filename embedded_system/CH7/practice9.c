#include "stm32f4xx_hal.h"
#include <stdio.h>

// UART1 �ʱ�ȭ �Լ� ����
void UART1_Init(void);

// ���� ���� ����
char i = 0;            // LED�� ��ġ�� ��Ÿ���� ����
int EINT_NO, EINT_VAL; // ���ͷ�Ʈ ��ȣ�� ���� �����ϴ� ����

// GPIO �ܺ� ���ͷ�Ʈ �ݹ� �Լ�
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == GPIO_PIN_0) {
        i = (i + 1) % 8;  // i �� ���� (0���� 7���� �ݺ�)
    }
		
    if (GPIO_Pin == GPIO_PIN_2) {
        i = 0;  // i ���� 0���� �ʱ�ȭ
    }
}

// GPIO �ʱ�ȭ �Լ�
void GPIOx_Init() {
    // GPIOA�� GPIOC Ŭ�� Ȱ��ȭ
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    // GPIO ���� ����ü ���� �� �ʱ�ȭ
    GPIO_InitTypeDef GPIO_InitStruct;
    
    // GPIOA ���� (�� 0�� 2�� �ܺ� ���ͷ�Ʈ�� ���)
    GPIO_InitStruct.Pull = GPIO_PULLUP;          // Ǯ�� ����
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_2;  // ��Ʈ A�� 0, 2�� �� ����
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;  // ��� �������� ���ͷ�Ʈ �߻�
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // GPIOC ���� (�� 0-7�� ��� ���� ���)
    GPIO_InitStruct.Pull = GPIO_NOPULL;          // Ǯ ����
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
		GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;  // ��Ʈ C�� 0-7�� �� ����
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  // Ǫ��Ǯ ��� ���
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // ���� �ӵ�
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

int main() {
    // HAL ���̺귯�� �ʱ�ȭ
    HAL_Init();
    
    // GPIO �ʱ�ȭ
    GPIOx_Init();
    
    // UART1 �ʱ�ȭ
    UART1_Init();
    
    // �ܺ� ���ͷ�Ʈ 0 �켱���� ���� �� ���ͷ�Ʈ ���
    HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
    
    // �ܺ� ���ͷ�Ʈ 2 �켱���� ���� �� ���ͷ�Ʈ ���
    HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);
    
    while (1) {
        // GPIOC ��Ʈ�� ��� ������ �������͸� �����Ͽ� LED ��ġ ����
        GPIOC->ODR = 1 << i;
        
        // 100ms ������
        HAL_Delay(100);
    }
}