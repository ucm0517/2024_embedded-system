// FOR OPEN405 
// stm32f4xx의 각 레지스터들을 정의한 헤더파일

#include "stm32f4xx_hal.h"

int main() {
   GPIO_InitTypeDef   GPIO_InitStructure = {0};

   HAL_Init();
    __HAL_RCC_GPIOB_CLK_ENABLE();

   /*Configure GPIO pins : PB0 PB1 PB2 PB3 */
   GPIO_InitStructure.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
   GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStructure.Pull = GPIO_NOPULL;
   GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
  
   while(1) {
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_SET);	     //PORTB->ODR = 0x000F;
      HAL_Delay(500); // 500 ms 지연

      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_RESET);  //PORTB->ODR = 0x0000;
      HAL_Delay(500); // 500 ms 지연
   }
}
