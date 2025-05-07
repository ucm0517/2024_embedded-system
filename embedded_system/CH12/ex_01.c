#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart1;

void UART1_Init(void);

int main() {
	
HAL_Init();
UART1_Init();
unsigned char c = 'A';
	
while (1) {
	
HAL_UART_Transmit(&huart1, &c, 1, 100);
if( ++c > 'Z' ) c = 'A';
HAL_Delay(10);
	
}
} 