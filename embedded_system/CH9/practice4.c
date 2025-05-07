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
    __HAL_RCC_TIM10_CLK_ENABLE();
    
    // GPIOA 초기화 (SW0 ~ SW3)
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // GPIOB 초기화 (PWM 출력)
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
    sConfigOC.Pulse = 0; // 초기값 0%
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim10, &sConfigOC, TIM_CHANNEL_1); // TIM10 채널 1 설정
    
    // TIM10 PWM 출력 시작
    HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
    
    // 변수 초기화
    int cv = 0;
    GPIO_PinState in_key;
    GPIO_PinState past_key = GPIO_PIN_RESET;

    while (1) {
        // SW0 핀 상태 읽기
        in_key = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
        
        // 스위치가 눌린 경우 처리할 작업
        if((past_key == GPIO_PIN_RESET) && (in_key != GPIO_PIN_RESET)) {
            // 듀티 사이클 변경
            cv = (cv + 1) % 5; // cv 값을 0에서 4까지 순환
            
            switch (cv) {
                case 0:
                    htim10.Instance->CCR1 = 0; // 0%
                    break;
                case 1:
                    htim10.Instance->CCR1 = 2500 - 1; // 25%
                    break;
                case 2:
                    htim10.Instance->CCR1 = 5000 - 1; // 50%
                    break;
                case 3:
                    htim10.Instance->CCR1 = 7500 - 1; // 75%
                    break;
                case 4:
                    htim10.Instance->CCR1 = 10000 - 1; // 100%
                    break;
            }
        }
        
        // 이전 키 상태 업데이트
        past_key = in_key;
        
        // 짧은 딜레이를 추가하여 CPU 사용률을 낮추고 디바운싱 효과
        HAL_Delay(10);
    }
}