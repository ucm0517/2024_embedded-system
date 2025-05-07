// stm32f4xx�� �� �������͵��� ������ �������
#include "stm32f4xx_hal.h"
int main() 
{
    // GPIO �ʱ�ȭ ����ü ���� �� �ʱ�ȭ
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    // HAL ���̺귯�� �ʱ�ȭ
    HAL_Init();

    // GPIOB Ŭ�� Ȱ��ȭ
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /* GPIO �� ����: PB8, PB9, PB10, PB11 */
    // GPIO �� ������ ���� ����ü �ʱ�ȭ
    GPIO_InitStructure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11; // ����Ϸ��� �ɵ�
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; // ��� ��� ����
    GPIO_InitStructure.Pull = GPIO_NOPULL; // Ǯ��/Ǯ�ٿ� ��Ȱ��ȭ
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW; // �ӵ� ���� (���� �ӵ�)
    
    // GPIOB �ʱ�ȭ
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
    // ���� ����
		while(1) 
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
			HAL_Delay(10); // 10 ms ����
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
			HAL_Delay(10); // 10 ms ����
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
			HAL_Delay(10); // 10 ms ����
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
			HAL_Delay(10); // 10 ms ����
		}
}