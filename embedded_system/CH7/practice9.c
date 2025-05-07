#include "stm32f4xx_hal.h"
#include <stdio.h>

// UART1 초기화 함수 선언
void UART1_Init(void);

// 전역 변수 선언
char i = 0;            // LED의 위치를 나타내는 변수
int EINT_NO, EINT_VAL; // 인터럽트 번호와 값을 저장하는 변수

// GPIO 외부 인터럽트 콜백 함수
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == GPIO_PIN_0) {
        i = (i + 1) % 8;  // i 값 증가 (0부터 7까지 반복)
    }
		
    if (GPIO_Pin == GPIO_PIN_2) {
        i = 0;  // i 값을 0으로 초기화
    }
}

// GPIO 초기화 함수
void GPIOx_Init() {
    // GPIOA와 GPIOC 클럭 활성화
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    // GPIO 설정 구조체 선언 및 초기화
    GPIO_InitTypeDef GPIO_InitStruct;
    
    // GPIOA 설정 (핀 0과 2를 외부 인터럽트로 사용)
    GPIO_InitStruct.Pull = GPIO_PULLUP;          // 풀업 설정
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_2;  // 포트 A의 0, 2번 핀 설정
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;  // 상승 엣지에서 인터럽트 발생
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // GPIOC 설정 (핀 0-7을 출력 모드로 사용)
    GPIO_InitStruct.Pull = GPIO_NOPULL;          // 풀 없음
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
		GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;  // 포트 C의 0-7번 핀 설정
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  // 푸시풀 출력 모드
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // 낮은 속도
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

int main() {
    // HAL 라이브러리 초기화
    HAL_Init();
    
    // GPIO 초기화
    GPIOx_Init();
    
    // UART1 초기화
    UART1_Init();
    
    // 외부 인터럽트 0 우선순위 설정 및 인터럽트 허용
    HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
    
    // 외부 인터럽트 2 우선순위 설정 및 인터럽트 허용
    HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);
    
    while (1) {
        // GPIOC 포트의 출력 데이터 레지스터를 설정하여 LED 위치 변경
        GPIOC->ODR = 1 << i;
        
        // 100ms 딜레이
        HAL_Delay(100);
    }
}