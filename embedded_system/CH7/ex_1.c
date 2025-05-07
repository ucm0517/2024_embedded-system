#include "stm32f4xx_hal.h"
#include <stdio.h>

// UART1 초기화 함수 선언
void UART1_Init(void);

// 인터럽트가 몇 번 수행되었는지 나타내는 변수
int COUNT = 0;

// GPIO 초기화 함수
void GPIOx_Init() {
    // GPIOA 클럭 활성화
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    // GPIO 설정 구조체 선언
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pull = GPIO_PULLUP;           // 풀업 설정
    GPIO_InitStruct.Pin = GPIO_PIN_0;             // 포트 A의 0번 핀 설정
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;   // 외부 인터럽트 0을 상승 엣지에서 발생하도록 설정
    // GPIO_MODE_IT_FALLING; // (필요시, 하강 엣지 설정)
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// GPIO 외부 인터럽트 콜백 함수
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == GPIO_PIN_0) {  // 인터럽트가 발생한 핀이 PA0인지 확인
        COUNT++;  // 인터럽트 카운트 증가
    }
}

int main() {
    // HAL 라이브러리 초기화
    HAL_Init();
    
    // GPIO 초기화
    GPIOx_Init();
    
    // UART1 초기화
    UART1_Init();
    
    // 인터럽트 우선순위 설정
    HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
    
    // 외부 인터럽트 0 허용
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
    
    // 인터럽트 카운트 초기화
    COUNT = 0;
    
    while (1) {
        // 현재 인터럽트 카운트를 출력
        printf("Count is %d\r\n", COUNT);
        
        // 100ms 딜레이
        HAL_Delay(100);
    }
}