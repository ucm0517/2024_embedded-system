#include "stm32f4xx_hal.h"
#include	"LIB_TLCD.h"
#include "stdio.h"

int main() {
	char buffer[5];
	unsigned int i =0;
	HAL_Init();
	TLCD_GPIO_Init();
	TLCD_Init();
	while(1) {
			TLCD_Goto(0, 5);
			TLCD_DispString("<Nice Day>");
			TLCD_Goto(1, 9);
			
      TLCD_DispString("Hello"); // ??? ??? ??

	}
}
