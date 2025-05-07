// stm32f4xx의 각 레지스터들을 정의한 헤더파일
#include "stm32f4xx_hal.h"
int main() 
{
    // GPIO 초기화 구조체 선언 및 초기화
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    // HAL 라이브러리 초기화
    HAL_Init();

    // GPIOB 클럭 활성화
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /* GPIO 핀 설정: PB8, PB9, PB10, PB11 */
    // GPIO 핀 설정을 위한 구조체 초기화
    GPIO_InitStructure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11; // 사용하려는 핀들
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; // 출력 모드 설정
    GPIO_InitStructure.Pull = GPIO_NOPULL; // 풀업/풀다운 비활성화
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW; // 속도 설정 (낮은 속도)
    
    // GPIOB 초기화
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
    // 무한 루프
		while(1) 
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
			HAL_Delay(10); // 10 ms 지연
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
			HAL_Delay(10); // 10 ms 지연
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
			HAL_Delay(10); // 10 ms 지연
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
			HAL_Delay(10); // 10 ms 지연
		}
}