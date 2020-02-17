/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>

/* Standard Includes */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* Module Includes */
#include <LcdDriver/Crystalfontz128x128_ST7735.h>

#define BUFFER_SIZE 5

/** Initializes a graphics context used for drawing things to the screen */
Graphics_Context InitGraphics()
{
    Graphics_Context context;

    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
    Graphics_initContext(&context, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);

    Graphics_setFont(&context, &g_sFontFixed6x8);

    Graphics_setForegroundColor(&context, GRAPHICS_COLOR_BLACK);
    Graphics_setBackgroundColor(&context, GRAPHICS_COLOR_WHITE);
    Graphics_clearDisplay(&context);

    return context;
}

int main(void)
{
    /* Stop Watchdog  */
    WDT_A_holdTimer();

    Graphics_Context context = InitGraphics();

    int left = 0;
    int right = 0;

    char buffer[BUFFER_SIZE];

    while (true)
    {
        snprintf(buffer, BUFFER_SIZE, "%02d", left);
        Graphics_drawString(&context, (int8_t*) buffer, -1, 20, 20, true);

        snprintf(buffer, BUFFER_SIZE, "%02d", right);
        Graphics_drawString(&context, (int8_t*) buffer, -1, 100, 100, true);

    }
}
