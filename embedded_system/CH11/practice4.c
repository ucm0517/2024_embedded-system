#include "stm32f4xx_hal.h"

// Function declarations
void rotate_clockwise(void);
void rotate_counterclockwise(void);

int main() {
    // GPIO �ʱ�ȭ ����ü ���� �� �ʱ�ȭ
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    // HAL ���̺귯�� �ʱ�ȭ
    HAL_Init();

    // GPIOB �� GPIOA Ŭ�� Ȱ��ȭ
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE(); // ��ư �Է��� ���� GPIOA Ŭ�� Ȱ��ȭ

    // ���� ��� ���� GPIO �� ����: PB8, PB9, PB10, PB11
    GPIO_InitStructure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_NOPULL; // Ǯ��/Ǯ�ٿ� ��Ȱ��ȭ
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW; // ���� �ӵ� ����
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

    // ��ư �Է��� ���� GPIO �� ����: PA0, PA1
    GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

    // ��ư �Է� ���¸� ������ ����
    uint32_t input_data, past_key = 0;

    // ���� ����
    while(1) {
        // PA0�� PA1�� �Է� ���¸� ����
        input_data = (GPIOA->IDR) & 0x03;

        // ���� Ű ���°� 0�̰� ���� �Է��� ���� ��
        if ((past_key == 0) && (input_data != 0)) {
            if (input_data & 0x01) {
                // �ð�������� �� �� ȸ��
                rotate_clockwise();
            }
            if (input_data & 0x02) {
                // �ݽð�������� �� �� ȸ��
                rotate_counterclockwise();
            }
        }
        // ���� Ű ���¸� ���� Ű ���·� ����
        past_key = input_data;
    }
}

// �ð�������� ȸ���ϴ� �Լ�
void rotate_clockwise(void) {
    for (int i = 0; i < 12; i++) {
        GPIOB->ODR = 0x0100; // PB8 �� ��Ʈ (0x0100)
        HAL_Delay(5); // 5 ms ����
        GPIOB->ODR = 0x0200; // PB9 �� ��Ʈ (0x0200)
        HAL_Delay(5); // 5 ms ����
        GPIOB->ODR = 0x0400; // PB10 �� ��Ʈ (0x0400)
        HAL_Delay(5); // 5 ms ����
        GPIOB->ODR = 0x0800; // PB11 �� ��Ʈ (0x0800)
        HAL_Delay(5); // 5 ms ����
    }
}

// �ݽð�������� ȸ���ϴ� �Լ�
void rotate_counterclockwise(void) {
    for (int i = 0; i < 12; i++) {
        GPIOB->ODR = 0x0400; // PB10 �� ��Ʈ (0x0400)
        HAL_Delay(5); // 5 ms ����
        GPIOB->ODR = 0x0200; // PB9 �� ��Ʈ (0x0200)
        HAL_Delay(5); // 5 ms ����
        GPIOB->ODR = 0x0100; // PB8 �� ��Ʈ (0x0100)
        HAL_Delay(5); // 5 ms ����
        GPIOB->ODR = 0x0800; // PB11 �� ��Ʈ (0x0800)
        HAL_Delay(5); // 5 ms ����
    }
}