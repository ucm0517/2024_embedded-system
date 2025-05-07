#include "stm32f4xx_hal.h"

void segment ( int v ) {
unsigned char FONT[18] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07,
0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x08, 0x80};
static   char SCAN;
unsigned char n_thou, n_hund, n_ten, n_base ;
int buff ;
n_thou = v /1000; // ?????? ???? ?? ??? ??
buff = v % 1000 ;
n_hund = buff / 100 ; // ?????? ???? ???? ??
buff = buff % 100;
n_ten = buff /10 ; // ?????? ???? ?? ?? ??
n_base = buff % 10 ; // ?????? ???? ?? ?? ??


if( SCAN == 0 ) {
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC, FONT[n_thou], GPIO_PIN_SET);
HAL_Delay(1);
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC, FONT[n_thou], GPIO_PIN_RESET);
}
if( SCAN == 1) {
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC, FONT[n_hund], GPIO_PIN_SET);
HAL_Delay(1);
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC, FONT[n_hund], GPIO_PIN_RESET);
}
if( SCAN == 2) {
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC, FONT[n_ten], GPIO_PIN_SET);
HAL_Delay(1);
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC, FONT[n_ten], GPIO_PIN_RESET);
}
if( SCAN == 3) {
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOC, FONT[n_base], GPIO_PIN_SET);
HAL_Delay(1);
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOC, FONT[n_base], GPIO_PIN_RESET);
}
SCAN = (SCAN+1) % 4;
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
	
   GPIO_InitStructure.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
   HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_SET);
	
   GPIO_InitStructure.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|
   GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	
   HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
	
   GPIO_InitStructure.Mode = GPIO_MODE_INPUT; // A ?? ?? 8??? ???? ????.
   HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

   
   
		int step = 1, ss = 1, input_data, past_key = 0;
    unsigned int val = 0;
    while (1) {
        input_data = (GPIOA->IDR) & 0xFF;
        if ((past_key == 0) && (input_data != 0)) {
            if (input_data & 0x01) ss = (ss + 1) % 2; // Toggle start/stop
            if (input_data & 0x80) {
                val = 0; // Reset the stopwatch when S8 is pressed
                //step = 1; // Optional: Automatically start counting after reset
            }
        }
        past_key = input_data;
        if (ss == 1) {
            val = (val + step) % 10000;
        }

        for (int i = 0; i < 600; i++)
            segment(val);
    }
}