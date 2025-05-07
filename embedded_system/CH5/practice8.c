#include "stm32f4xx_hal.h"

void segment ( int n )  // Segment ?? ??
{
	// 7-???? ??? ??? ????.
	static unsigned char FONT[18] = {0x3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7C, 0X07,
														0X7F, 0X67, 0X77, 0X7C, 0X39, 0X5E, 0X79, 0X71, 0X08, 0X80};
	static char SCAN=0;
	
	unsigned char n_thou, n_hund, n_ten, n_base ;
	int	tmp ;

	n_thou = n / 1000;  // ?????? ???? ?? ??? ??
	tmp = n % 1000 ;
	n_hund = tmp / 100 ; // ?????? ???? ???? ??
	tmp = tmp % 100;
	n_ten = tmp  /10 ;     // ?????? ???? ?? ?? ??
	n_base =  tmp % 10 ;    // ?????? ???? ?? ?? ??      

//	HAL_GPIO_WritePin(GPIOB, 0xF000, GPIO_PIN_SET);	//?? ???? OFF
//	HAL_GPIO_WritePin(GPIOC, 0x00FF, GPIO_PIN_RESET);
	if( SCAN == 0 ) {
//		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOC, FONT[n_thou], GPIO_PIN_SET); // ?? ? ?? ????? ON??, ?? ??  ??? ??? ?? 
		GPIOB->ODR = (GPIOB->ODR & 0x0FFF) | 0xE000;
		GPIOC->ODR = (GPIOC->ODR & 0xFF00) | FONT[n_thou];
	}
	if( SCAN == 1 ) {
//		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOC, FONT[n_hund], GPIO_PIN_SET); // ?? ? ?? ????? ON??, ?? ??  ??? ??? ?? 
		GPIOB->ODR = (GPIOB->ODR & 0x0FFF) | 0xD000;
		GPIOC->ODR = (GPIOC->ODR & 0xFF00) | FONT[n_hund];
	}
	if( SCAN == 2 ) {
//		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOC, FONT[n_ten], GPIO_PIN_SET); // ?? ? ?? ????? ON??, ?? ??  ??? ??? ?? 
		GPIOB->ODR = (GPIOB->ODR & 0x0FFF) | 0xB000;
		GPIOC->ODR = (GPIOC->ODR & 0xFF00) | FONT[n_ten];
	}
	if( SCAN == 3 ) {
//		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOC, FONT[n_base], GPIO_PIN_SET); // ?? ? ?? ????? ON??, ?? ??  ??? ??? ?? 
		GPIOB->ODR = (GPIOB->ODR & 0x0FFF) | 0x7000;
		GPIOC->ODR = (GPIOC->ODR & 0xFF00) | FONT[n_base];
	}

	HAL_Delay(1);
	SCAN = (SCAN+1) % 4;
}

void display(int number, int position) {
    // ??? ?? ?? ??? ?????.
    int n_thou = number / 1000;
    int n_hund = (number % 1000) / 100;
    int n_ten = (number % 100) / 10;
    int n_unit = number % 10;

    // ??? ?? ??? ??? ?????.
    int display_number;
    switch (position) {
        case 0: display_number = n_thou; break;
        case 1: display_number = n_hund; break;
        case 2: display_number = n_ten; break;
        case 3: display_number = n_unit; break;
    }

    // FND? ??? ?????.
    segment(display_number);
}


int main() {
    GPIO_InitTypeDef GPIO_InitStructure;
    HAL_Init();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET);

    GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
                             GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

    int input_data;
    unsigned int val = 0;
    unsigned int shift_register = 0; // shift_register 0
    int position = 0; // start position 0

    while (1) {
        input_data = (GPIOA->IDR) & 0xFF;  // Read input from GPIOA
        val = input_data;  // Assign input value to val for display

        // FND output switch shift
        if (position == 0) {
            shift_register = val; // input data shift_register save
        } else {
            shift_register = (shift_register * 10) % 10000; // left shift
        }

        // present location number FND output
        display(shift_register, position);

        // ?? ??? ?????.
        position = (position + 1) % 4;
        HAL_Delay(1000); // 1s number left shift
    }
}

//???