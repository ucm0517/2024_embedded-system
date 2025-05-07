#include "stm32f4xx_hal.h"
#include <stdio.h>

// UART1 �ʱ�ȭ �Լ� ����
void UART1_Init(void);

// ���ͷ�Ʈ ��ȣ, ���ͷ�Ʈ ��, �� ���ͷ�Ʈ ���� ī��Ʈ�� �����ϴ� �迭 ����
int EINT_NO, EINT_VAL, COUNT[4] = {0, 0, 0, 0};

// GPIO �ܺ� ���ͷ�Ʈ �ݹ� �Լ�
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    // GPIO �� ��ȣ�� ���� ���ͷ�Ʈ ��ȣ�� ī��Ʈ�� ������Ŵ
    if (GPIO_Pin == GPIO_PIN_0) {
        EINT_NO = 0;
        COUNT[0]++;
    }
    if (GPIO_Pin == GPIO_PIN_1) {
        EINT_NO = 1;
        COUNT[1]++;
    }
    if (GPIO_Pin == GPIO_PIN_2) {
        EINT_NO = 2;
        COUNT[2]++;
    }
    if (GPIO_Pin == GPIO_PIN_3) {
        EINT_NO = 3;
        COUNT[3]++;
    }
}

// GPIO �ʱ�ȭ �Լ�
void GPIOx_Init() {
    // GPIOA Ŭ�� Ȱ��ȭ
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    // GPIO ���� ����ü ���� �� �ʱ�ȭ
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pull = GPIO_PULLUP;  // Ǯ�� ����
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;  // ��Ʈ A�� 0, 1, 2, 3�� �� ����
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;  // �ܺ� ���ͷ�Ʈ�� ��� �������� �߻��ϵ��� ����
    // GPIO_MODE_IT_FALLING; // (�ʿ��, �ϰ� ���� ����)
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

int main() {
    // HAL ���̺귯�� �ʱ�ȭ
    HAL_Init();
    
    // GPIO �ʱ�ȭ
    GPIOx_Init();
    
    // UART1 �ʱ�ȭ
    UART1_Init();
    
    // �ܺ� ���ͷ�Ʈ 0 �켱���� ���� �� ���ͷ�Ʈ ���
    HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
    
    // �ܺ� ���ͷ�Ʈ 1 �켱���� ���� �� ���ͷ�Ʈ ���
    HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);
    
    // �ܺ� ���ͷ�Ʈ 2 �켱���� ���� �� ���ͷ�Ʈ ���
    HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);
    
    // �ܺ� ���ͷ�Ʈ 3 �켱���� ���� �� ���ͷ�Ʈ ���
    HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);
    
    while (1) {
        // ���� ���ͷ�Ʈ ��ȣ�� �� ���� ī��Ʈ�� ���
        printf("INT:%d \t 0:%2d \t 1:%2d \t 2:%2d \t 3:%2d \r\n", EINT_NO, COUNT[0], COUNT[1], COUNT[2], COUNT[3]);
        
        // 100ms ������
        HAL_Delay(100);
    }
}