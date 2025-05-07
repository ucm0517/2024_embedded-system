#include "stm32f4xx_hal.h"

// TIM10 핸들러 외부 선언
extern TIM_HandleTypeDef htim10;

int main(void) {
    // GPIO 설정 구조체 및 타이머 출력 비교 설정 구조체 선언
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_OC_InitTypeDef sConfigOC;
    
    // HAL 라이브러리 초기화
    HAL_Init();
    
    // GPIOB 클럭 활성화
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    // TIM10 클럭 활성화
    __HAL_RCC_TIM10_CLK_ENABLE();
    
    // GPIOB 핀 8을 TIM10의 대체 기능으로 설정
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;  // 푸시풀 출력 모드
    GPIO_InitStruct.Pull = GPIO_NOPULL;      // 풀업/풀다운 없음
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  // 낮은 속도
    GPIO_InitStruct.Alternate = GPIO_AF3_TIM10;   // TIM10 대체 기능
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);  // GPIOB 초기화
    
    // TIM10 초기화 설정
    htim10.Instance = TIM10;
    htim10.Init.Prescaler = 16 - 1;  // 프리스케일러 설정 (16MHz/16 = 1MHz)
    htim10.Init.CounterMode = TIM_COUNTERMODE_UP;  // 업카운터 모드
    htim10.Init.Period = 17000 - 1;  // 타이머 주기 설정 (60Hz)
    htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;  // 클럭 분주 없음
    htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;  // 자동 리로드 프리로드 비활성화
    HAL_TIM_PWM_Init(&htim10);  // TIM10 초기화
    
    // PWM 출력 비교 설정
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;  // 초기 펄스 값 설정
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim10, &sConfigOC, TIM_CHANNEL_1);  // TIM10 채널 1 설정
    
    // TIM10 PWM 출력 시작
    HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
    
    while (1) {
        // 듀티 사이클을 천천히 변화시키며 PWM 신호 생성
        for (int i = 0; i < 30000; i += 1000) {
            htim10.Instance->CCR1 = i;  // PWM 듀티 사이클 설정
            __HAL_TIM_SET_COMPARE(&htim10, TIM_CHANNEL_1, i);  // TIM10 비교 레지스터 설정
            HAL_Delay(100);  // 100ms 딜레이
        }
    }
}