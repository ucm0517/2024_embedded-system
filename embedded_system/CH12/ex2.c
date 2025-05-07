#include "stm32f4xx_hal.h"
#include <stdio.h>

extern UART_HandleTypeDef huart1;
void UART1_Init(void);

int main() {
	
HAL_Init();
UART1_Init();
printf("Test Terminal\r\n");
unsigned char c = 'A';
float f_val = 1.2;
	
while (1) {
printf("Send Character %c %f\r\n", c, f_val+=(float)0.1);
if( ++c > 'Z' ) c = 'A';
HAL_Delay(10);
}
}
