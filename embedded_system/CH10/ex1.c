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
    
    // ADC ä�� ����
    sConfig.Channel = ADC_CHANNEL_0; // ADC ä�� 0 ����
    sConfig.Rank = 1; // ���� ����
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES; // ���ø� �ð� ����
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);
    
    // GPIO ���� ����ü ���� �� �ʱ�ȭ
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    // GPIOA Ŭ�� Ȱ��ȭ
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    // ��Ʈ ���� (PA0)
    GPIO_InitStruct.Pin = GPIO_PIN_0; // GPIOA �� 0 ����
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; // �Ƴ��α� ���
    GPIO_InitStruct.Pull = GPIO_PULLUP; // Ǯ�� ����
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); // GPIOA �ʱ�ȭ
    
    int val;
    
    while (1) {
        // ADC ��ȯ ����
        HAL_ADC_Start(&hadc1);
        
        // ADC ��ȯ �Ϸ� ���
        HAL_ADC_PollForConversion(&hadc1, 1);
        
        // ��ȯ �Ϸ� ���� Ȯ��
        if ((HAL_ADC_GetState(&hadc1) & HAL_ADC_STATE_EOC_REG) != 0) {
            // ADC �� �б�
            val = HAL_ADC_GetValue(&hadc1);
        }
        
        // ADC �� ���
        printf("ADC value : %4d\r\n", val);
    }
}