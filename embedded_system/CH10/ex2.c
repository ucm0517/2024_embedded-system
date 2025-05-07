#include "stm32f4xx_hal.h"
#include <stdio.h>

// UART1 초기화 함수 선언
void UART1_Init(void);

int main(void) {
    // ADC 채널 설정 구조체 선언
    ADC_ChannelConfTypeDef sConfig;
    
    // ADC 핸들러 외부 선언
    extern ADC_HandleTypeDef hadc1;
    
    // HAL 라이브러리 초기화
    HAL_Init();
    
    // UART1 초기화
    UART1_Init();
    
    // ADC1 클럭 활성화
    __HAL_RCC_ADC1_CLK_ENABLE();
    
    // ADC1 초기화 설정
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2; // 프리스케일러 설정 (클럭 분주)
    hadc1.Init.Resolution = ADC_RESOLUTION_12B; // 12비트 해상도
    hadc1.Init.ScanConvMode = DISABLE; // 스캔 변환 모드 비활성화
    hadc1.Init.ContinuousConvMode = DISABLE; // 연속 변환 모드 비활성화
    hadc1.Init.DiscontinuousConvMode = DISABLE; // 불연속 변환 모드 비활성화
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE; // 외부 트리거 엣지 없음
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START; // 소프트웨어 트리거 시작
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT; // 데이터 정렬 오른쪽
    hadc1.Init.NbrOfConversion = 1; // 변환 수 1
    hadc1.Init.DMAContinuousRequests = DISABLE; // DMA 연속 요청 비활성화
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV; // 단일 변환 완료 선택
    HAL_ADC_Init(&hadc1);
    
    // ADC 채널 설정 (온도 센서)
    sConfig.Channel = ADC_CHANNEL_TEMPSENSOR; // ADC 온도 센서 채널 설정
    sConfig.Rank = 1; // 순위 설정
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES; // 샘플링 시간 설정
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);
    
    // 변수 선언
    short int val, t_s;
    
    while (1) {
        // ADC 변환 시작
        HAL_ADC_Start(&hadc1);
        
        // ADC 변환 완료 대기
        HAL_ADC_PollForConversion(&hadc1, 1);
        
        // 변환 완료 상태 확인
        if ((HAL_ADC_GetState(&hadc1) & HAL_ADC_STATE_EOC_REG) != 0) {
            // ADC 값 읽기
            t_s = HAL_ADC_GetValue(&hadc1) & 0xFFF;
            
            // 온도 변환 공식 적용
            val = (short int)(((t_s * 3300.0 / 4095.0 - 760.0) / 2.5 + 25.0));
        }
        
        // 온도 값 출력
        printf("MCP temperature (in deg) : %03d\r\n", val);
        
        // 온도에 따라 GPIOB 핀 설정
        if (val > 25) {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET); // GPIOB 핀 8을 HIGH로 설정
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET); // GPIOB 핀 11을 LOW로 설정
        } else {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET); // GPIOB 핀 8을 LOW로 설정
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET); // GPIOB 핀 11을 HIGH로 설정
        }
    }
}