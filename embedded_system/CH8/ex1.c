#include "stm32f4xx_hal.h"
#include <stdio.h>

// UART1 초기화 함수 선언
void UART1_Init(void);

// GPIO 초기화 함수
void GPIOx_Init() {
    // GPIOA 클럭 활성화
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    // GPIO 설정 구조체 선언 및 초기화
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = GPIO_PIN_0;              // 포트 A의 0번 핀 설정
    GPIO_InitStruct.Pull = GPIO_PULLUP;            // 풀업 설정
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;        // 푸시풀 출력 모드
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;     // TIM2의 대체 기능으로 설정
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);        // GPIOA 초기화
}

// TIM2 핸들러 외부 선언
extern TIM_HandleTypeDef htim2;

// 타이머 초기화 함수
void TIMx_Init() {
    // 타이머 클럭 설정 구조체 선언 및 초기화
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    
    // TIM2 클럭 활성화
    __HAL_RCC_TIM2_CLK_ENABLE();
    
    // TIM2 초기화 설정
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 0;                        // 프리스케일러 설정 (클럭 분주 없음)
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;     // 업카운터 모드
    htim2.Init.Period = 9999;                        // 0 ~ 9999 (카운터 주기)
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; // 클럭 분주 없음
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE; // 자동 리로드 프리로드 비활성화
    HAL_TIM_Base_Init(&htim2);                       // TIM2 초기화
    
    // 타이머 클럭 소스 설정
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_ETRMODE2; // 외부 트리거 모드 2 설정
    sClockSourceConfig.ClockPolarity = TIM_CLOCKPOLARITY_INVERTED; // 클럭 폴라리티 반전
    sClockSourceConfig.ClockPrescaler = TIM_CLOCKPRESCALER_DIV1;   // 클럭 분주 없음
    sClockSourceConfig.ClockFilter = 15;                           // 클럭 필터 설정 (채터링 방지)
    HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig);        // TIM2 클럭 소스 설정
    
    // 타이머 시작
    HAL_TIM_Base_Start(&htim2);
}

int main() {
    int val;
    
    // HAL 라이브러리 초기화
    HAL_Init();
    
    // UART1 초기화
    UART1_Init();
    
    // GPIO 초기화
    GPIOx_Init();
    
    // 타이머 초기화
    TIMx_Init();
    
    while (1) {
        // TIM2의 카운터 값 읽기
        val = __HAL_TIM_GetCounter(&htim2); //TIM2->CNT;
        
        // 카운터 값 출력
        printf("COUNTER VAL : %d\r\n", val);
        
        // 200ms 딜레이
        HAL_Delay(200);
    }
}