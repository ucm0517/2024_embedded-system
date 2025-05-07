#include "stm32f4xx_hal.h"

// TIM10 핸들러 외부 선언
extern TIM_HandleTypeDef htim10;

int main(void) {
    // GPIO 설정 구조체 및 타이머 출력 비교 설정 구조체 선언
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_OC_InitTypeDef sConfigOC;
    
    // HAL 라이브러리 초기화
    HAL_Init();
    
    // GPIOB와 GPIOA 클럭 활성화
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    // TIM10 클럭 활성화
    __HAL_RCC_TIM10_CLK_ENABLE();
    
    // GPIOA 핀 0-3을 입력 모드로 설정
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // GPIOB 핀 8을 TIM10의 대체 기능으로 설정
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF3_TIM10;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    // TIM10 초기화 설정
    htim10.Instance = TIM10;
    htim10.Init.Prescaler = 16 - 1; // 프리스케일러 설정 (16MHz/16 = 1MHz)
    htim10.Init.CounterMode = TIM_COUNTERMODE_UP; // 업카운터 모드
    htim10.Init.Period = 10000 - 1; // 타이머 주기 설정 (10000-1)
    htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; // 클럭 분주 없음
    htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE; // 자동 리로드 프리로드 비활성화
    HAL_TIM_PWM_Init(&htim10); // TIM10 초기화
    
    // PWM 출력 비교 설정
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 5000 - 1; // 50% 듀티 사이클 (5000/10000)
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim10, &sConfigOC, TIM_CHANNEL_1); // TIM10 채널 1 설정
    
    // TIM10 PWM 출력 시작
    HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
    
    while (1) {
        // PA0 핀 상태 확인 및 CCR1 값 설정 (25% 듀티 사이클)
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
            htim10.Instance->CCR1 = 2500 - 1;
        
        // PA1 핀 상태 확인 및 CCR1 값 설정 (50% 듀티 사이클)
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_SET)
            htim10.Instance->CCR1 = 5000 - 1;
        
        // PA2 핀 상태 확인 및 CCR1 값 설정 (75% 듀티 사이클)
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_SET)
            htim10.Instance->CCR1 = 7500 - 1;
        
        // PA3 핀 상태 확인 및 CCR1 값 설정 (100% 듀티 사이클)
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_SET)
            htim10.Instance->CCR1 = 10000 - 1;
    }
}