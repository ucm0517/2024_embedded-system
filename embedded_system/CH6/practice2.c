//6.2 ????? ???? ??? ??
#include "stm32f4xx_hal.h"
#include	"LIB_TLCD.h"
#include "stdio.h"

int main() {
   HAL_Init();
   TLCD_GPIO_Init();
   TLCD_Init();
   
   int i = 35;
   while(1){
      TLCD_Goto(0,i);
      TLCD_DispString("<Nice Day>You are a good student!");
      TLCD_Goto(1,i);
      TLCD_DispString("Hello! Our lecture is very Pleasure!");
      i--;
      if(i==0) 
				i=35;
   }
}