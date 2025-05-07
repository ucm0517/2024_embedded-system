#include "stm32f4xx_hal.h"
#include "LIB_TLCD.h"
#include "stdio.h"

#define TLCD_RS GPIO_PIN_0 // LCD RS 핀
#define TLCD_RW GPIO_PIN_1 // LCD RW 핀
#define TLCD_E GPIO_PIN_2  // LCD E 핀
#define P_DATA GPIOC       // LCD 데이터 포트
#define P_CTL GPIOB        // LCD 제어 포트

int main() {
    char buffer[5];          // 숫자를 문자열로 저장할 버퍼 (최대 4자리 + null)
    unsigned int i = 0;      // 카운터 변수

    HAL_Init();              // HAL 초기화
    TLCD_GPIO_Init();        // LCD GPIO 초기화
    TLCD_Init();             // LCD 초기화

    while(1) {
        TLCD_Goto(0, 6);                     // LCD 1행 7번째 칸으로 이동
        TLCD_DispString("Count");           // "Count" 문자열 출력

        TLCD_Goto(1, 7);                    // LCD 2행 8번째 칸으로 이동
        sprintf(buffer, "%4u", i);          // 숫자 i를 너비 4칸으로 포맷하여 buffer에 저장
        TLCD_DispString(buffer);            // 숫자 문자열 출력

        HAL_Delay(500);                     // 500ms 지연
        i++;                                // 카운터 증가
        if(i > 9999) 
            i = 0;                          // 9999를 넘으면 0으로 초기화
    }
}