#include	"segment.h"

void segment ( int n )  // Segment 함수 선언
{
	// 7-세그먼트 폰트를 배열로 지정한다.
	static unsigned char FONT[18] = {0x3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7C, 0X07,
														0X7F, 0X67, 0X77, 0X7C, 0X39, 0X5E, 0X79, 0X71, 0X08, 0X80};
	static char SCAN=0;
	
	unsigned char n_thou, n_hund, n_ten, n_base ;
	int	tmp ;

	n_thou = n / 1000;  // 세그먼트에서 사용하는 천의 자리를 추출
	tmp = n % 1000 ;
	n_hund = tmp / 100 ; // 세그먼트에서 사용하는 백의자리 추출
	tmp = tmp % 100;
	n_ten = tmp  /10 ;     // 세그먼트에서 사용하는 십의 자리 추출
	n_base =  tmp % 10 ;    // 세그먼트에서 사용하는 일의 자리 추출      

//	HAL_GPIO_WritePin(GPIOB, 0xF000, GPIO_PIN_SET);	//모든 세그먼트 OFF
//	HAL_GPIO_WritePin(GPIOC, 0x00FF, GPIO_PIN_RESET);
	if( SCAN == 0 ) {
//		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOC, FONT[n_thou], GPIO_PIN_SET); // 왼쪽 첫 번째 세그먼트를 ON하고, 천의 자리  숫자를 출력해 준다 
		GPIOB->ODR = (GPIOB->ODR & 0x0FFF) | 0xE000;
		GPIOC->ODR = (GPIOC->ODR & 0xFF00) | FONT[n_thou];
	}
	if( SCAN == 1 ) {
//		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOC, FONT[n_hund], GPIO_PIN_SET); // 왼쪽 두 번째 세그먼트를 ON하고, 천의 자리  숫자를 출력해 준다 
		GPIOB->ODR = (GPIOB->ODR & 0x0FFF) | 0xD000;
		GPIOC->ODR = (GPIOC->ODR & 0xFF00) | FONT[n_hund];
	}
	if( SCAN == 2 ) {
//		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOC, FONT[n_ten], GPIO_PIN_SET); // 왼쪽 세 번째 세그먼트를 ON하고, 천의 자리  숫자를 출력해 준다 
		GPIOB->ODR = (GPIOB->ODR & 0x0FFF) | 0xB000;
		GPIOC->ODR = (GPIOC->ODR & 0xFF00) | FONT[n_ten];
	}
	if( SCAN == 3 ) {
//		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOC, FONT[n_base], GPIO_PIN_SET); // 왼쪽 네 번째 세그먼트를 ON하고, 천의 자리  숫자를 출력해 준다 
		GPIOB->ODR = (GPIOB->ODR & 0x0FFF) | 0x7000;
		GPIOC->ODR = (GPIOC->ODR & 0xFF00) | FONT[n_base];
	}

	HAL_Delay(1);
	SCAN = (SCAN+1) % 4;
}
