#include "stm32f4xx_hal.h"
#include <stdio.h>

// UART1 �ʱ�ȭ �Լ� ����
void UART1_Init(void);

// ���ͷ�Ʈ�� �� �� ����Ǿ����� ��Ÿ���� ����
int COUNT = 0;

// GPIO �ʱ�ȭ �Լ�
void GPIOx_Init() {
    // GPIOA Ŭ�� Ȱ��ȭ
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    // GPIO ���� ����ü ����
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pull = GPIO_PULLUP;           // Ǯ�� ����
    GPIO_InitStruct.Pin = GPIO_PIN_0;             // ��Ʈ A�� 0�� �� ����
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;   // �ܺ� ���ͷ�Ʈ 0�� ��� �������� �߻��ϵ��� ����
    // GPIO_MODE_IT_FALLING; // (�ʿ��, �ϰ� ���� ����)
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// GPIO �ܺ� ���ͷ�Ʈ �ݹ� �Լ�
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == GPIO_PIN_0) {  // ���ͷ�Ʈ�� �߻��� ���� PA0���� Ȯ��
        COUNT++;  // ���ͷ�Ʈ ī��Ʈ ����
    }
}

int main() {
    // HAL ���̺귯�� �ʱ�ȭ
    HAL_Init();
    
    // GPIO �ʱ�ȭ
    GPIOx_Init();
    
    // UART1 �ʱ�ȭ
    UART1_Init();
    
    // ���ͷ�Ʈ �켱���� ����
    HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
    
    // �ܺ� ���ͷ�Ʈ 0 ���
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
    
    // ���ͷ�Ʈ ī��Ʈ �ʱ�ȭ
    COUNT = 0;
    
    while (1) {
        // ���� ���ͷ�Ʈ ī��Ʈ�� ���
        printf("Count is %d\r\n", COUNT);
        
        // 100ms ������
        HAL_Delay(100);
    }
}