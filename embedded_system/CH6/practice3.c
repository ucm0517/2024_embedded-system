#include "stm32f4xx_hal.h"
#include "LIB_TLCD.h"
#include "stdio.h"

int main() {
    HAL_Init();
    TLCD_GPIO_Init();
    TLCD_Init();

    const char* line1 = "Good morning";
    const char* line2 = "Have a breakfast";

    int visible = 1; // ???? ??? ??, 1? ??, 0? ??

    while(1) {
        if (visible) {
            TLCD_Goto(0, 0);
            TLCD_DispString(line1); // ? ?? ?? ??? ??
            TLCD_Goto(1, 0);
            TLCD_DispString(line2); // ? ?? ?? ??? ??
        } else {
            TLCD_Goto(0, 0);
            TLCD_DispString("            "); // ? ?? ?? ???? ??
            TLCD_Goto(1, 0);
            TLCD_DispString("                "); // ? ?? ?? ???? ??
        }

        visible = !visible; // visible ??
        HAL_Delay(500); // 500ms ???? ??? ??
    }
}