#include "stm32f4xx_hal.h"
#include <stdio.h>

// UART1 초기화 함수 선언
void UART1_Init(void);

// 전역 변수 선언
int t_cnt = 0, s_cnt = 0;
int led_idx = 0;  // 현재 LED 인덱스를 저장할 변수

// TIM7 핸들러 외부 선언
extern TIM_HandleTypeDef htim7;

// 타이머 기간 경과 콜백 함수
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM7) { // TIM7 인스턴스 확인
        HAL_GPIO_WritePin(GPIOC, 0xFFFF, GPIO_PIN_RESET);  // 모든 LED를 끔
        HAL_GPIO_WritePin(GPIOC, 1 << led_idx, GPIO_PIN_SET);  // 현재 인덱스의 LED만 켬
        led_idx = (led_idx + 1) % 10;  // 다음 LED 인덱스로 업데이트 (0~9까지 순환)
    }
}

// 타이머 초기화 함수
void TIMx_Init() {
    // TIM7 클럭 활성화
    __HAL_RCC_TIM7_CLK_ENABLE();
    
    // TIM7 초기화 설정
    htim7.Instance = TIM7;
    htim7.Init.Prescaler = 16000 - 1; // 프리스케일러 설정 (16MHz/16000 = 1kHz, 1ms)
    htim7.Init.Period = 999; // 타이머 주기 설정 (1000-1, 1초마다 인터럽트 발생)
    htim7.Init.CounterMode = TIM_COUNTERMODE_UP; // 업카운터 모드
    HAL_TIM_Base_Init(&htim7); // TIM7 초기화
    
    // TIM7 인터럽트 설정
    HAL_NVIC_ClearPendingIRQ(TIM7_IRQn); // 인터럽트 대기 플래그 클리어
    HAL_NVIC_SetPriority(TIM7_IRQn, 7, 0); // 인터럽트 우선순위 설정
    HAL_NVIC_EnableIRQ(TIM7_IRQn); // 인터럽트 허용
    HAL_TIM_Base_Start_IT(&htim7); // 타이머 인터럽트 모드 시작
}

// GPIO 초기화 함수
void GPIOx_Init() {
    // GPIOC 클럭 활성화
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    // GPIO 설정 구조체 선언 및 초기화
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // 푸시풀 출력 모드
    GPIO_InitStruct.Pull = GPIO_NOPULL; // 풀 없음
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // 낮은 속도
    GPIO_InitStruct.Pin = 0xFFFF; // 포트 C의 모든 핀 설정 (16비트, LED 0-15)
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct); // GPIOC 초기화
}

int main() {
    // HAL 라이브러리 초기화
    HAL_Init();
    
    // UART1 초기화
    UART1_Init();
    
    // GPIO 초기화
    GPIOx_Init();
    
    // 타이머 초기화
    TIMx_Init();
    
    while (1) {
        // 초 카운터 값을 출력
        printf("Timer in SEC : %4d\r", s_cnt);
    }
}