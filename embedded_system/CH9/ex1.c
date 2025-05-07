#include "stm32f4xx_hal.h"

// TIM2와 TIM4 핸들러 외부 선언
extern TIM_HandleTypeDef htim2, htim4;

int main(void) {
    // GPIO 설정 구조체 및 타이머 출력 비교 설정 구조체 선언
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_OC_InitTypeDef sConfigOC;
    
    // HAL 라이브러리 초기화
    HAL_Init();
    
    // GPIOB와 GPIOA 클럭 활성화
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    // TIM2와 TIM4 클럭 활성화
    __HAL_RCC_TIM2_CLK_ENABLE();
    __HAL_RCC_TIM4_CLK_ENABLE();
    
    // GPIOA 핀 0-3을 입력 모드로 설정
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // GPIOB 핀 8-9을 TIM4의 대체 기능으로 설정
    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    // GPIOB 핀 10-11을 TIM2의 대체 기능으로 설정
    GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    // TIM2 초기화 설정
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 15;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 10000 - 1;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_PWM_Init(&htim2);
    
    // TIM4 초기화 설정
    htim4.Instance = TIM4;
    htim4.Init.Prescaler = 15;
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim4.Init.Period = 10000 - 1;
    htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_PWM_Init(&htim4);
    
    // PWM 출력 비교 설정
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
		sConfigOC.Pulse = 2500 - 1;
    HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3);
    sConfigOC.Pulse = 5000 - 1;
    HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4);
    sConfigOC.Pulse = 7500 - 1;
    HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);
    sConfigOC.Pulse = 10000 - 1;
    HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4);
    
    while (1) {
        // GPIOA 핀 0 상태 확인 및 TIM4 채널 3 PWM 시작/중지
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
            HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
            HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
        
        // GPIOA 핀 1 상태 확인 및 TIM4 채널 4 PWM 시작/중지
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_SET)
            HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
            HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
        
        // GPIOA 핀 2 상태 확인 및 TIM2 채널 3 PWM 시작/중지
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_SET)
            HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
            HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
        
        // GPIOA 핀 3 상태 확인 및 TIM2 채널 4 PWM 시작/중지
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_SET)
            HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
            HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
        
        // 100ms 딜레이
        HAL_Delay(100);
    }
}