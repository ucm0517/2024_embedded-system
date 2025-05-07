#include "stm32f4xx_hal.h"

#define TLCD_RS		GPIO_PIN_0                  // LCD RS 신호 
#define TLCD_RW		GPIO_PIN_1                  // LCD RW 신호 
#define TLCD_E		GPIO_PIN_2                  // LCD E 신호 
#define P_DATA		GPIOC                       // LCD DATA 포트
#define P_CTL			GPIOB                       // LCD CONTROL 포트
#define	LEFT	0
#define RIGHT	1

void TLCD_GPIO_Init(void);
void TLCD_EnablePulse(void);
void TLCD_SendData(unsigned char data);
void TLCD_SendCommand(unsigned char data);
void TLCD_Init(void);
void TLCD_DispString(char *str);
void TLCD_Goto(int y, int x);
void TLCD_Shift(char dir);
