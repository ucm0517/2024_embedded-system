#include "stm32f4xx_hal.h"
#include	"LIB_TLCD.h"
#define TLCD_RS GPIO_PIN_0 // LCD RS 핀
#define TLCD_RW GPIO_PIN_1 // LCD RW 핀
#define TLCD_E GPIO_PIN_2  // LCD E 핀
#define P_DATA GPIOC       // LCD DATA 포트
#define P_CTL GPIOB        // LCD CONTROL 포트



int main() {
    HAL_Init();            // HAL 초기화
    TLCD_GPIO_Init();      // LCD용 GPIO 초기화
    TLCD_Init();           // LCD 초기화

    // LCD에 문자열 출력
    TLCD_Goto(0,2);        // 1행 3번째 위치로 커서 이동
    TLCD_DispString("Happy Day"); 
    TLCD_Goto(1,4);        // 2행 5번째 위치로 커서 이동
    TLCD_DispString("Welcome !");
}
