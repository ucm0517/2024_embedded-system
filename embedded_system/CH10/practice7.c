#include "stm32f4xx_hal.h"
#include <stdio.h>

// UART1 �ʱ�ȭ �Լ� ����
void UART1_Init(void);

int main(void) {
	
	// ADC ä�� ���� ����ü ����
	ADC_ChannelConfTypeDef sConfig;
	
	// �ܺ� ����� ADC �ڵ鷯
	extern ADC_HandleTypeDef hadc1;
	
	// HAL ���̺귯�� �ʱ�ȭ
	HAL_Init();
	
	// UART1 �ʱ�ȭ �Լ� ȣ��
	UART1_Init();
	
	// GPIO �ʱ�ȭ ����ü ���� �� �ʱ�ȭ
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	// GPIOA Ŭ�� Ȱ��ȭ
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	// GPIOB Ŭ�� Ȱ��ȭ
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	// PA0 ���� �Ƴ��α� �Է� ���� ����
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	// PB8 �� PB11 ���� Ǫ��Ǯ ��� ���� ����
	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	// ADC1 Ŭ�� Ȱ��ȭ
	__HAL_RCC_ADC1_CLK_ENABLE();
	
	// ADC1 ���� �ʱ�ȭ
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
	
	// ADC ä�� ����
	sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);
	
	// ���� ����
	short int val, t_s;
	
	while (1) {
		// ADC ��ȯ ����
		HAL_ADC_Start(&hadc1);
		
		// ADC ��ȯ �Ϸ� ���
		HAL_ADC_PollForConversion(&hadc1, 1);
		
		// ��ȯ�� �Ϸ�Ǹ� �� �б�
		if ((HAL_ADC_GetState(&hadc1) & HAL_ADC_STATE_EOC_REG) != 0) {
			t_s = HAL_ADC_GetValue(&hadc1) & 0xFFF;
			// �µ� ��ȯ ���� ����
			val = (short int)(((t_s * 3300.0 / 4095.0 - 760.0) / 2.5 + 25.0));
		}
		
		// ��ȯ�� �µ� ���� �͹̳ο� ���
		printf("MCP temperature (in deg) : %03d\r\n", val);
		
		// �µ��� 24�� �̻��̸� PB8 ���� HIGH, PB11 ���� LOW�� ����
		if (val > 24) {
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
		}
		// �µ��� 24�� �����̸� PB8 ���� LOW, PB11 ���� HIGH�� ����
		else {
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
		}
	}
}