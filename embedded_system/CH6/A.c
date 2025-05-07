#include "stm32f4xx_hal.h"
#include	"LIB_TLCD.h"


int main() {
	HAL_Init();
	TLCD_GPIO_Init();
	TLCD_Init();
	TLCD_SendData('A'); 
}
