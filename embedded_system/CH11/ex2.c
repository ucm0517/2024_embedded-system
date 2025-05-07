// stm32f4xx의 각 레지스터들을 정의한 헤더파일
#include "stm32f4xx_hal.h"

// GPIO 핀 정의
#define STEP_A GPIO_PIN_8
#define STEP_B GPIO_PIN_9
#define STEP_AN GPIO_PIN_10
#define STEP_BN GPIO_PIN_11
#define STEP_PORT GPIOB

// 스테핑 모터 상태 변수
unsigned char STEP_M_STAT = 0;

// 타이머 핸들러 외부 선언
extern TIM_HandleTypeDef htim2;

// 타이머 인터럽트 콜백 함수
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    // TIM2 인터럽트 발생 시
    if (htim->Instance == TIM2) {
        // 스테핑 모터 상태 업데이트 (0~3 사이클)
        STEP_M_STAT = (STEP_M_STAT + 1) % 4;
    }
}

// GPIO 초기화 함수
void GPIOx_Init() {
    // GPIO 초기화 구조체 선언 및 초기화
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    
    // GPIOB 클럭 활성화
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    /* GPIO 핀 설정: PB8, PB9, PB10, PB11 */
    GPIO_InitStructure.Pin = STEP_A | STEP_B | STEP_AN | STEP_BN; // 사용하려는 핀들
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; // 출력 모드 설정
    GPIO_InitStructure.Pull = GPIO_NOPULL; // 풀업/풀다운 비활성화
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW; // 속도 설정 (낮은 속도)
    
    // GPIOB 초기화
    HAL_GPIO_Init(STEP_PORT, &GPIO_InitStructure);
}

// 타이머 초기화 함수
void TIM2_Init() {
    // TIM2 클럭 활성화
    __HAL_RCC_TIM2_CLK_ENABLE();
    
    // 타이머 설정
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 16 - 1; // 1MHz
    htim2.Init.Period = 10000 - 1; // 100Hz
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP; // 타이머 카운터 모드 설정
    
    // 타이머 초기화
    HAL_TIM_Base_Init(&htim2);
    
    // 인터럽트 설정
    HAL_NVIC_ClearPendingIRQ(TIM2_IRQn);
    HAL_NVIC_SetPriority(TIM2_IRQn, 7, 0); // 인터럽트 우선순위 설정
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
    
    // 타이머 인터럽트 시작
    HAL_TIM_Base_Start_IT(&htim2);
}

int main() {
    // HAL 라이브러리 초기화
    HAL_Init();
    
    // GPIO 초기화
    GPIOx_Init();
    
    // 타이머 초기화
    TIM2_Init();
    
    // 현재 상태 변수
    unsigned char c_stat;
    
    // 무한 루프
    while(1) {
        // 상태가 변경되었을 때
        if (c_stat != STEP_M_STAT) {
            // 모든 핀을 리셋 (Low 상태로 설정)
            HAL_GPIO_WritePin(STEP_PORT, 0xF << 8, GPIO_PIN_RESET);
            
            // 스테핑 모터 상태에 따라 핀 설정
            if (STEP_M_STAT == 0) HAL_GPIO_WritePin(STEP_PORT, STEP_A | STEP_B, GPIO_PIN_SET);
            else if (STEP_M_STAT == 1) HAL_GPIO_WritePin(STEP_PORT, STEP_B | STEP_AN, GPIO_PIN_SET);
            else if (STEP_M_STAT == 2) HAL_GPIO_WritePin(STEP_PORT, STEP_AN | STEP_BN, GPIO_PIN_SET);
            else if (STEP_M_STAT == 3) HAL_GPIO_WritePin(STEP_PORT, STEP_BN | STEP_A, GPIO_PIN_SET);
            
            // 현재 상태 업데이트
            c_stat = STEP_M_STAT;
        }
        
        // 1 ms 지연
        HAL_Delay(1);
    }
}