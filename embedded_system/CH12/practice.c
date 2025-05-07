#include "stm32f4xx_hal.h"
#include "stdio.h"

extern UART_HandleTypeDef huart1;

void UART1_Init(void);

int main() {
		HAL_Init();
		UART1_Init();
	
	
    int input_key, past_key, sw_count=0;

    GPIO_InitTypeDef GPIO_InitStructure;
    __HAL_RCC_GPIOA_CLK_ENABLE();


    GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
                             GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;

    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
		GPIO_InitStructure.Pull = GPIO_NOPULL;
		GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
		
    while (1) {
        input_key = GPIOA->IDR & 0x81;
				if((past_key ==0) && (input_key !=0)) {
						if(input_key == 0x80)  sw_count = 0;
						if(input_key == 0x01)  sw_count = (sw_count + 1) % 10;
						printf("%d\r\n", sw_count);
				}
		past_key = input_key;
		}
}