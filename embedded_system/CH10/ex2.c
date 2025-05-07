#include "stm32f4xx_hal.h"
#include <stdio.h>

// UART1 �ʱ�ȭ �Լ� ����
void UART1_Init(void);

int main(void) {
    // ADC ä�� ���� ����ü ����
    ADC_ChannelConfTypeDef sConfig;
    
    // ADC �ڵ鷯 �ܺ� ����
    extern ADC_HandleTypeDef hadc1;
    
    // HAL ���̺귯�� �ʱ�ȭ
    HAL_Init();
    
    // UART1 �ʱ�ȭ
    UART1_Init();
    
    // ADC1 Ŭ�� Ȱ��ȭ
    __HAL_RCC_ADC1_CLK_ENABLE();
    
    // ADC1 �ʱ�ȭ ����
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2; // ���������Ϸ� ���� (Ŭ�� ����)
    hadc1.Init.Resolution = ADC_RESOLUTION_12B; // 12��Ʈ �ػ�
    hadc1.Init.ScanConvMode = DISABLE; // ��ĵ ��ȯ ��� ��Ȱ��ȭ
    hadc1.Init.ContinuousConvMode = DISABLE; // ���� ��ȯ ��� ��Ȱ��ȭ
    hadc1.Init.DiscontinuousConvMode = DISABLE; // �ҿ��� ��ȯ ��� ��Ȱ��ȭ
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE; // �ܺ� Ʈ���� ���� ����
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START; // ����Ʈ���� Ʈ���� ����
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT; // ������ ���� ������
    hadc1.Init.NbrOfConversion = 1; // ��ȯ �� 1
    hadc1.Init.DMAContinuousRequests = DISABLE; // DMA ���� ��û ��Ȱ��ȭ
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV; // ���� ��ȯ �Ϸ� ����
    HAL_ADC_Init(&hadc1);
    
    // ADC ä�� ���� (�µ� ����)
    sConfig.Channel = ADC_CHANNEL_TEMPSENSOR; // ADC �µ� ���� ä�� ����
    sConfig.Rank = 1; // ���� ����
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES; // ���ø� �ð� ����
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);
    
    // ���� ����
    short int val, t_s;
    
    while (1) {
        // ADC ��ȯ ����
        HAL_ADC_Start(&hadc1);
        
        // ADC ��ȯ �Ϸ� ���
        HAL_ADC_PollForConversion(&hadc1, 1);
        
        // ��ȯ �Ϸ� ���� Ȯ��
        if ((HAL_ADC_GetState(&hadc1) & HAL_ADC_STATE_EOC_REG) != 0) {
            // ADC �� �б�
            t_s = HAL_ADC_GetValue(&hadc1) & 0xFFF;
            
            // �µ� ��ȯ ���� ����
            val = (short int)(((t_s * 3300.0 / 4095.0 - 760.0) / 2.5 + 25.0));
        }
        
        // �µ� �� ���
        printf("MCP temperature (in deg) : %03d\r\n", val);
        
        // �µ��� ���� GPIOB �� ����
        if (val > 25) {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET); // GPIOB �� 8�� HIGH�� ����
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET); // GPIOB �� 11�� LOW�� ����
        } else {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET); // GPIOB �� 8�� LOW�� ����
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET); // GPIOB �� 11�� HIGH�� ����
        }
    }
}