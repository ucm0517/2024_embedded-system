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
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    // Setup GPIOB for digit selection
    GPIO_InitStructure.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    // Setup GPIOC for segment control
    GPIO_InitStructure.Pin = 0xFF;  // Assume all pins of GPIOC are used for segments
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    // Setup GPIOA for button inputs
    GPIO_InitStructure.Pin = 0xFF;  // Assume pins 0-7 of GPIOA are used for buttons
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    unsigned int switch_state = 0;
    int displayed_number = 0;
    
    while(1) {
        switch_state = GPIOA->IDR & 0xFF;  // Read all 8 buttons from GPIOA
        
        // Update displayed number based on button press (S1 to S8 mapped to 1 to 8)
        for (int i = 0; i < 8; i++) {
            if (switch_state & (1 << i)) {
                displayed_number = i + 1;  // Set number to display based on button press
                break;
            }
        }
        
        segment(displayed_number);  // Display the number on the FND
        HAL_Delay(100);  // Delay to debounce and for stability
    }
}