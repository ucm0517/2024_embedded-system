#include "stm32f4xx_hal.h"
#include <stdio.h>

// UART1 초기화 함수 선언
void UART1_Init(void);

// 인터럽트 번호, 인터럽트 값, 각 인터럽트 핀의 카운트를 저장하는 배열 선언
int EINT_NO, EINT_VAL, COUNT[4] = {0, 0, 0, 0};

// GPIO 외부 인터럽트 콜백 함수
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    // GPIO 핀 번호에 따라 인터럽트 번호와 카운트를 증가시킴
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

// GPIO 초기화 함수
void GPIOx_Init() {
    // GPIOA 클럭 활성화
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    // GPIO 설정 구조체 선언 및 초기화
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pull = GPIO_PULLUP;  // 풀업 설정
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;  // 포트 A의 0, 1, 2, 3번 핀 설정
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;  // 외부 인터럽트를 상승 엣지에서 발생하도록 설정
    // GPIO_MODE_IT_FALLING; // (필요시, 하강 엣지 설정)
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

int main() {
    // HAL 라이브러리 초기화
    HAL_Init();
    
    // GPIO 초기화
    GPIOx_Init();
    
    // UART1 초기화
    UART1_Init();
    
    // 외부 인터럽트 0 우선순위 설정 및 인터럽트 허용
    HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
    
    // 외부 인터럽트 1 우선순위 설정 및 인터럽트 허용
    HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);
    
    // 외부 인터럽트 2 우선순위 설정 및 인터럽트 허용
    HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);
    
    // 외부 인터럽트 3 우선순위 설정 및 인터럽트 허용
    HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);
    
    while (1) {
        // 현재 인터럽트 번호와 각 핀의 카운트를 출력
        printf("INT:%d \t 0:%2d \t 1:%2d \t 2:%2d \t 3:%2d \r\n", EINT_NO, COUNT[0], COUNT[1], COUNT[2], COUNT[3]);
        
        // 100ms 딜레이
        HAL_Delay(100);
    }
}