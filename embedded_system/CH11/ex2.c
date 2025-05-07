// stm32f4xx�� �� �������͵��� ������ �������
#include "stm32f4xx_hal.h"

// GPIO �� ����
#define STEP_A GPIO_PIN_8
#define STEP_B GPIO_PIN_9
#define STEP_AN GPIO_PIN_10
#define STEP_BN GPIO_PIN_11
#define STEP_PORT GPIOB

// ������ ���� ���� ����
unsigned char STEP_M_STAT = 0;

// Ÿ�̸� �ڵ鷯 �ܺ� ����
extern TIM_HandleTypeDef htim2;

// Ÿ�̸� ���ͷ�Ʈ �ݹ� �Լ�
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    // TIM2 ���ͷ�Ʈ �߻� ��
    if (htim->Instance == TIM2) {
        // ������ ���� ���� ������Ʈ (0~3 ����Ŭ)
        STEP_M_STAT = (STEP_M_STAT + 1) % 4;
    }
}

// GPIO �ʱ�ȭ �Լ�
void GPIOx_Init() {
    // GPIO �ʱ�ȭ ����ü ���� �� �ʱ�ȭ
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    
    // GPIOB Ŭ�� Ȱ��ȭ
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    /* GPIO �� ����: PB8, PB9, PB10, PB11 */
    GPIO_InitStructure.Pin = STEP_A | STEP_B | STEP_AN | STEP_BN; // ����Ϸ��� �ɵ�
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; // ��� ��� ����
    GPIO_InitStructure.Pull = GPIO_NOPULL; // Ǯ��/Ǯ�ٿ� ��Ȱ��ȭ
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW; // �ӵ� ���� (���� �ӵ�)
    
    // GPIOB �ʱ�ȭ
    HAL_GPIO_Init(STEP_PORT, &GPIO_InitStructure);
}

// Ÿ�̸� �ʱ�ȭ �Լ�
void TIM2_Init() {
    // TIM2 Ŭ�� Ȱ��ȭ
    __HAL_RCC_TIM2_CLK_ENABLE();
    
    // Ÿ�̸� ����
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 16 - 1; // 1MHz
    htim2.Init.Period = 10000 - 1; // 100Hz
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP; // Ÿ�̸� ī���� ��� ����
    
    // Ÿ�̸� �ʱ�ȭ
    HAL_TIM_Base_Init(&htim2);
    
    // ���ͷ�Ʈ ����
    HAL_NVIC_ClearPendingIRQ(TIM2_IRQn);
    HAL_NVIC_SetPriority(TIM2_IRQn, 7, 0); // ���ͷ�Ʈ �켱���� ����
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
    
    // Ÿ�̸� ���ͷ�Ʈ ����
    HAL_TIM_Base_Start_IT(&htim2);
}

int main() {
    // HAL ���̺귯�� �ʱ�ȭ
    HAL_Init();
    
    // GPIO �ʱ�ȭ
    GPIOx_Init();
    
    // Ÿ�̸� �ʱ�ȭ
    TIM2_Init();
    
    // ���� ���� ����
    unsigned char c_stat;
    
    // ���� ����
    while(1) {
        // ���°� ����Ǿ��� ��
        if (c_stat != STEP_M_STAT) {
            // ��� ���� ���� (Low ���·� ����)
            HAL_GPIO_WritePin(STEP_PORT, 0xF << 8, GPIO_PIN_RESET);
            
            // ������ ���� ���¿� ���� �� ����
            if (STEP_M_STAT == 0) HAL_GPIO_WritePin(STEP_PORT, STEP_A | STEP_B, GPIO_PIN_SET);
            else if (STEP_M_STAT == 1) HAL_GPIO_WritePin(STEP_PORT, STEP_B | STEP_AN, GPIO_PIN_SET);
            else if (STEP_M_STAT == 2) HAL_GPIO_WritePin(STEP_PORT, STEP_AN | STEP_BN, GPIO_PIN_SET);
            else if (STEP_M_STAT == 3) HAL_GPIO_WritePin(STEP_PORT, STEP_BN | STEP_A, GPIO_PIN_SET);
            
            // ���� ���� ������Ʈ
            c_stat = STEP_M_STAT;
        }
        
        // 1 ms ����
        HAL_Delay(1);
    }
}