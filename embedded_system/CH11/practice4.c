#include "stm32f4xx_hal.h"

// Function declarations
void rotate_clockwise(void);
void rotate_counterclockwise(void);

int main() {
    // GPIO 초기화 구조체 선언 및 초기화
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    // HAL 라이브러리 초기화
    HAL_Init();

    // GPIOB 및 GPIOA 클럭 활성화
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE(); // 버튼 입력을 위한 GPIOA 클럭 활성화

    // 모터 제어를 위한 GPIO 핀 설정: PB8, PB9, PB10, PB11
    GPIO_InitStructure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_NOPULL; // 풀업/풀다운 비활성화
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW; // 낮은 속도 설정
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 버튼 입력을 위한 GPIO 핀 설정: PA0, PA1
    GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 버튼 입력 상태를 저장할 변수
    uint32_t input_data, past_key = 0;

    // 무한 루프
    while(1) {
        // PA0와 PA1의 입력 상태를 읽음
        input_data = (GPIOA->IDR) & 0x03;

        // 이전 키 상태가 0이고 현재 입력이 있을 때
        if ((past_key == 0) && (input_data != 0)) {
            if (input_data & 0x01) {
                // 시계방향으로 한 번 회전
                rotate_clockwise();
            }
            if (input_data & 0x02) {
                // 반시계방향으로 한 번 회전
                rotate_counterclockwise();
            }
        }
        // 현재 키 상태를 이전 키 상태로 저장
        past_key = input_data;
    }
}

// 시계방향으로 회전하는 함수
void rotate_clockwise(void) {
    for (int i = 0; i < 12; i++) {
        GPIOB->ODR = 0x0100; // PB8 핀 세트 (0x0100)
        HAL_Delay(5); // 5 ms 지연
        GPIOB->ODR = 0x0200; // PB9 핀 세트 (0x0200)
        HAL_Delay(5); // 5 ms 지연
        GPIOB->ODR = 0x0400; // PB10 핀 세트 (0x0400)
        HAL_Delay(5); // 5 ms 지연
        GPIOB->ODR = 0x0800; // PB11 핀 세트 (0x0800)
        HAL_Delay(5); // 5 ms 지연
    }
}

// 반시계방향으로 회전하는 함수
void rotate_counterclockwise(void) {
    for (int i = 0; i < 12; i++) {
        GPIOB->ODR = 0x0400; // PB10 핀 세트 (0x0400)
        HAL_Delay(5); // 5 ms 지연
        GPIOB->ODR = 0x0200; // PB9 핀 세트 (0x0200)
        HAL_Delay(5); // 5 ms 지연
        GPIOB->ODR = 0x0100; // PB8 핀 세트 (0x0100)
        HAL_Delay(5); // 5 ms 지연
        GPIOB->ODR = 0x0800; // PB11 핀 세트 (0x0800)
        HAL_Delay(5); // 5 ms 지연
    }
}