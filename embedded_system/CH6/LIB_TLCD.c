#include	"LIB_TLCD.h"

void TLCD_GPIO_Init(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;

	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Pin = TLCD_RS|TLCD_RW|TLCD_E;
	HAL_GPIO_Init(P_CTL, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	HAL_GPIO_Init(P_DATA, &GPIO_InitStructure);
}

// LCD 에 모든 명령을 전송한후 반드시 Enable Pulse를 주어야 한다.
void TLCD_EnablePulse(void)
{
	HAL_GPIO_WritePin(P_CTL, TLCD_E, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(P_CTL, TLCD_E, GPIO_PIN_RESET);
}
  
// LCD에 데이터를 전송하는 함수이다   
void TLCD_SendData(unsigned char data)
{
	HAL_GPIO_WritePin(P_CTL, TLCD_RW, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(P_CTL, TLCD_RS, GPIO_PIN_SET);
	HAL_GPIO_WritePin(P_DATA, 0xFF, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(P_DATA, data, GPIO_PIN_SET);
	TLCD_EnablePulse();
	HAL_Delay(1);
} 

void TLCD_SendCommand(unsigned char data)
{
	HAL_GPIO_WritePin(P_CTL, TLCD_RW, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(P_CTL, TLCD_RS, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(P_DATA, 0xFF, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(P_DATA, data, GPIO_PIN_SET);
	TLCD_EnablePulse();
	HAL_Delay(1);
} 

// LCD 초기화 함수
void TLCD_Init(void)
{
	HAL_Delay(30);			//30 [ms] 시간 지연
	TLCD_SendCommand(0x38);		//function : 8bit data, 2Line, 5*7 dot
	TLCD_SendCommand(0x0c);		//Display ON 
	TLCD_SendCommand(0x01);		//Clear Screen 
	HAL_Delay(2);			//시간 지연 (2ms)
}

/******************************************
   lcd_char() : 1 문자를 디스플레이 하는 함수
*******************************************/
void TLCD_DispString(char *str)
{
	while(*str)
	{
		TLCD_SendData(*str);
		str++;
	}
}

void TLCD_Goto(int y, int x)
{
	int RamAddr;

	if(y==0) RamAddr=0x80 + x;	// line 1 D.D.RAM address
	else RamAddr=0xC0+x;	// line 2 D.D.RAM address
	
	TLCD_SendCommand((unsigned char)RamAddr);
}

void TLCD_Shift(char dir)
{
	unsigned char LCD_shift;

	if (dir==LEFT) LCD_shift=0x18;
	else if(dir==RIGHT) LCD_shift=0x1C;
	
	TLCD_SendCommand(LCD_shift);
}
