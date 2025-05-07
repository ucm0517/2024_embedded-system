#include "stm32f4xx_hal.h"
#include <stdio.h>

// UART1 초기화 함수 선언
void UART1_Init(void);

int main(void) {
	
	// ADC 채널 설정 구조체 선언
	ADC_ChannelConfTypeDef sConfig;
	
	// 외부 선언된 ADC 핸들러
	extern ADC_HandleTypeDef hadc1;
	
	// HAL 라이브러리 초기화
	HAL_Init();
	
	// UART1 초기화 함수 호출
	UART1_Init();
	
	// GPIO 초기화 구조체 선언 및 초기화
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	// GPIOA 클럭 활성화
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	// GPIOB 클럭 활성화
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	// PA0 핀을 아날로그 입력 모드로 설정
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	// PB8 및 PB11 핀을 푸시풀 출력 모드로 설정
	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	// ADC1 클럭 활성화
	__HAL_RCC_ADC1_CLK_ENABLE();
	
	// ADC1 설정 초기화
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DMAContinuousRequests = DISABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	HAL_ADC_Init(&hadc1);
	
	// ADC 채널 설정
	sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);
	
	// 변수 선언
	short int val, t_s;
	
	while (1) {
		// ADC 변환 시작
		HAL_ADC_Start(&hadc1);
		
		// ADC 변환 완료 대기
		HAL_ADC_PollForConversion(&hadc1, 1);
		
		// 변환이 완료되면 값 읽기
		if ((HAL_ADC_GetState(&hadc1) & HAL_ADC_STATE_EOC_REG) != 0) {
			t_s = HAL_ADC_GetValue(&hadc1) & 0xFFF;
			// 온도 변환 공식 적용
			val = (short int)(((t_s * 3300.0 / 4095.0 - 760.0) / 2.5 + 25.0));
		}
		
		// 변환된 온도 값을 터미널에 출력
		printf("MCP temperature (in deg) : %03d\r\n", val);
		
		// 온도가 24도 이상이면 PB8 핀을 HIGH, PB11 핀을 LOW로 설정
		if (val > 24) {
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
		}
		// 온도가 24도 이하이면 PB8 핀을 LOW, PB11 핀을 HIGH로 설정
		else {
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
		}
	}
}