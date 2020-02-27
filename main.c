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

// According to the schematics on page 37 of the Launchpad user guide,
// left button (button 1) is connected to pin 1 (bit1)
#define LEFT_BUTTON BIT1

// According to the schematics on page 37 of the Launchpad user guide,
// left LED (LED 1) is connected to pin 0 (bit0)
#define LEFT_LED BIT0

// According to the schematics on page 37 of the Launchpad user guide,
// When a button is pressed, it is grounded (logic 0)
#define PRESSED 0

// This initializes all the peripherals
void init_Launchpad_LED1();
void initialize();
void TurnOn_Launchpad_LED1();
void TurnOff_Launchpad_LED1();
char SwitchStatus_Launchpad_Button1();

void init_Launchpad_LED1()
{
    // step 3.1: write a 0 to PxDIR for the specific bit you want
    P1DIR &= ~LEFT_BUTTON;

    // step 3.2: write a 1 to PxREB for the specific bit you want
    P1REN |= LEFT_BUTTON;

    // step 3.3: write a 1 to PxOUT for the specific bit you want
    P1OUT |= LEFT_BUTTON;  // select pull-up

}

void TurnOn_Launchpad_LED1()
{
    //GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
    P1OUT = P1OUT |  LEFT_LED;
}

void TurnOff_Launchpad_LED1()
{
    //GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    P1OUT = P1OUT & ~LEFT_LED;
}

char SwitchStatus_Launchpad_Button1()
{
    //return (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1));
    return P1IN & LEFT_BUTTON;
}

//start of initialization of RIGHT button and LED2

// According to the schematics on page 37 of the Launchpad user guide,
// Right button (button 2) is connected to pin 1 (bit4)
#define RIGHT_BUTTON BIT4
#define RIGHT_LED_RED BIT0
#define RIGHT_LED_GREEN BIT1
#define RIGHT_LED_BLUE BIT2
#define SETTER 0xF8


// This function initializes all the peripherals
void init_Launchpad_LED2();
void TurnOn_Launchpad_LED2_RED();
void TurnOff_Launchpad_LED2_RED();
void TurnOn_Launchpad_LED2_GREEN();
void TurnOff_Launchpad_LED2_GREEN();
void TurnOn_Launchpad_LED2_BLUE();
void TurnOff_Launchpad_LED2_BLUE();
char SwitchStatus_Launchpad_Button2();
void init_Launchpad_Right_Button();
void init_Launchpad_Left_Button();

void init_Launchpad_Left_Button()
{
    // step 3.1: write a 0 to PxDIR for the specific bit you want
    P1DIR &= ~LEFT_BUTTON;

    // step 3.2: write a 1 to PxREB for the specific bit you want
    P1REN |= LEFT_BUTTON;

    // step 3.3: write a 1 to PxOUT for the specific bit you want
    P1OUT |= LEFT_BUTTON;  // select pull-up

}
void init_Launchpad_Right_Button()
{
    // step 3.1: write a 0 to PxDIR for the specific bit you want
    P1DIR &= ~RIGHT_BUTTON;

    // step 3.2: write a 1 to PxREB for the specific bit you want
    P1REN |= RIGHT_BUTTON;

    // step 3.3: write a 1 to PxOUT for the specific bit you want
    P1OUT |= RIGHT_BUTTON;  // select pull-up

}

void init_Launchpad_LED2()
{
    // step 3.1: write a 0 to PxDIR for the specific bit you want
    P2DIR &= ~SETTER;

    P1REN |= SETTER;

    // step 3.3: write a 1 to PxOUT for the specific bit you want
    P2OUT |= SETTER;  // select pull-up

}

void TurnOn_Launchpad_LED2_RED()
{
    P2DIR = P2DIR & SETTER;
    P2DIR = P2DIR | RIGHT_LED_RED;
    P2OUT = P2OUT | RIGHT_LED_RED;

}

void TurnOff_Launchpad_LED2_RED()
{
    P2OUT = P2OUT & ~RIGHT_LED_RED;
}

void TurnOn_Launchpad_LED2_GREEN()
{
    P2DIR = P2DIR & SETTER;
    P2DIR = P2DIR | RIGHT_LED_GREEN;
    P2OUT = P2OUT | RIGHT_LED_GREEN;
}

void TurnOff_Launchpad_LED2_GREEN()
{
    P2OUT = P2OUT & ~RIGHT_LED_GREEN;
}

void TurnOn_Launchpad_LED2_BLUE()
{
    P2DIR = P2DIR & SETTER;
    P2DIR = P2DIR | RIGHT_LED_BLUE;
    P2OUT = P2OUT | RIGHT_LED_BLUE;
}

void TurnOff_Launchpad_LED2_BLUE()
{
    P2OUT = P2OUT & ~RIGHT_LED_BLUE;
}
char SwitchStatus_Launchpad_Button2()
{

    return P1IN & RIGHT_BUTTON;
}

//Start of the initialization for Buttons S1, S2 and LEDs on Booster pack

// This initializes all the peripherals
void init_Boosterpack_LED();
void TurnOn_Boosterpack_RED();
void TurnOff_Boosterpack_RED();
void TurnOn_Boosterpack_GREEN();
void TurnOff_Boosterpack_GREEN();
void TurnOn_Boosterpack_BLUE();
void TurnOff_Boosterpack_BLUE();
void init_Boosterpack_Top_Button();
void init_Boosterpack_Bottom_Button();
void TurnOn_Boosterpack_Yellow();
void TurnOff_Boosterpack_Yellow();
char SwitchStatus_Boosterpack_Button1();
char SwitchStatus_Boosterpack_Button2();

//Define what is needed
#define BUTTON_S1 BIT1
#define BUTTON_S2 BIT5
#define BOOSTER_REDLED BIT6
#define SETTER_BOOSTER 0xAF
#define BOOSTER_LED_RED BIT6
#define BOOSTER_LED_GREEN BIT4
#define BOOSTER_LED_BLUE BIT6


void init_Boosterpack_Top_Button()
{
    // step 3.1: write a 0 to PxDIR for the specific bit you want
    P1DIR &= ~BUTTON_S1;

    // step 3.2: write a 1 to PxREB for the specific bit you want
    P1REN |= BUTTON_S1;

    // step 3.3: write a 1 to PxOUT for the specific bit you want
    P1OUT |= BUTTON_S1;  // select pull-up

}
void init_Boosterpack_Bottom_Button()
{
    // step 3.1: write a 0 to PxDIR for the specific bit you want
    P1DIR &= ~BUTTON_S2;

    // step 3.2: write a 1 to PxREB for the specific bit you want
    P1REN |= BUTTON_S2;

    // step 3.3: write a 1 to PxOUT for the specific bit you want
    P1OUT |= BUTTON_S2;  // select pull-up

}

void init_Boosterpack_LED()
{
    // step 3.1: write a 0 to PxDIR for the specific bit you want
    P5DIR &= ~BOOSTER_REDLED;
    // step 3.3: write a 1 to PxOUT for the specific bit you want
    P5OUT |= BOOSTER_REDLED;  // select pull-up

    P2DIR &= ~SETTER_BOOSTER;
    P2OUT |= SETTER_BOOSTER;

}

void TurnOn_Boosterpack_RED()
{
    P2DIR = P2DIR & SETTER_BOOSTER;
    P2DIR = P2DIR | BOOSTER_LED_RED;
    P2OUT = P2OUT | BOOSTER_LED_RED;
}
void TurnOff_Boosterpack_RED()
{
    P2OUT = P2OUT & ~BOOSTER_LED_RED;
}
void TurnOn_Boosterpack_GREEN()
{
    P2DIR = P2DIR & SETTER_BOOSTER;
    P2DIR = P2DIR | BOOSTER_LED_GREEN;
    P2OUT = P2OUT | BOOSTER_LED_GREEN;
}
void TurnOff_Boosterpack_GREEN()
{
    P2OUT = P2OUT & ~BOOSTER_LED_GREEN;
}
void TurnOn_Boosterpack_BLUE()
{
    P5DIR = P5DIR & BOOSTER_LED_BLUE;
    P5DIR = P5DIR | BOOSTER_LED_BLUE;
    P5OUT = P5OUT | BOOSTER_LED_BLUE;
}
void TurnOff_Boosterpack_BLUE()
{
    P5OUT = P5OUT & ~BOOSTER_LED_BLUE;
}

char SwitchStatus_Boosterpack_Button1()
{
    return P5IN & BUTTON_S1;
}
char SwitchStatus_Boosterpack_Button2()
{
    return P3IN & BUTTON_S2;
}
/*
void TurnOn_Boosterpack_Yellow()
{
    P2OUT = P2OUT & ~BOOSTER_LED_RED;
    P5DIR = P5DIR & BOOSTER_LED_BLUE;
    P5DIR = P5DIR | BOOSTER_LED_BLUE;
    P5OUT = P5OUT | BOOSTER_LED_BLUE;
}
void TurnOff_Boosterpack_Yellow()
{
    P2OUT = P2OUT & ~BOOSTER_LED_RED;
    P2OUT = P2OUT & ~BOOSTER_LED_GREEN;
}
*/
void initialize()
{

    // step 1: Stop watchdog timer
    // We do this at the beginning of all our programs for now.Later we learn more about it.
    WDT_A_hold(WDT_A_BASE);

    // step 2: Initializing LED1
    // According to table 12.1 on page 678 of MSP432 User guide,
    // to create an output, all you need is to write a 1 to PxDIR for the specific bit you want
    // A common mistake is to write P1DIR = LEFT_LED instead of P1DIR |= LEFT_LED;
    P1DIR |= LEFT_LED;
    P2DIR |= SETTER;
    P5DIR |= BOOSTER_REDLED;
    P2DIR |= SETTER_BOOSTER;


    init_Launchpad_Left_Button();
    init_Launchpad_Right_Button();
    init_Boosterpack_Top_Button();
    init_Boosterpack_Bottom_Button();
}





int main(void)
{
    /* Stop Watchdog*/
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

        initialize();
         //if launchpad right button is pressed, the right side will increase

        if (SwitchStatus_Launchpad_Button2() != PRESSED)
            left = left;
        else if (left == 40)
            left = left;
        else
            left++;
            snprintf(buffer, BUFFER_SIZE, "%02d", left);
            Graphics_drawString(&context, (int8_t*) buffer, -1, 20, 20, true);
        //if launchpad left button is pressed, the right side will decrease
        if (SwitchStatus_Launchpad_Button1() != PRESSED)
            left = left;
        else if (left == 0)
            left = left;
        else
            left--;
        //if Boosterpack top button is pressed, the right side will decrease
        if (SwitchStatus_Boosterpack_Button1() != PRESSED)
            right = right;
        else if (right == 40)
            right = right;
        else
            right++;
            snprintf(buffer, BUFFER_SIZE, "%02d", right);
            Graphics_drawString(&context, (int8_t*) buffer, -1, 100, 100, true);
        //if Boosterpack bottom button is pressed, the right side will decrease
        if (SwitchStatus_Boosterpack_Button2() != PRESSED)
            right = right;
        else if (right == 0)
            right = right;
        else
            right--;
            snprintf(buffer, BUFFER_SIZE, "%02d", right);
            Graphics_drawString(&context, (int8_t*) buffer, -1, 100, 100, true);



        //If the difference between left and right is within 10, then LED1 is on
        if (left - right <= 10)
            TurnOn_Launchpad_LED1();
        else
            TurnOff_Launchpad_LED1();
        //If the difference between left and right is between 10 and 20, then BLED is red
        if (left - right >= 10 && left - right <= 20)
            TurnOn_Boosterpack_RED();
        else
            TurnOff_Boosterpack_RED();
        //If the difference is between 20 and 30, then BLED LED is Green
        if (left - right >= 20 && left - right <= 30)
            TurnOn_Boosterpack_GREEN();
        else
            TurnOff_Boosterpack_GREEN();
        //If the difference is between 30 and 40, then BLED LED is blue
        if (left - right >= 30 && left - right <= 40)
            TurnOn_Boosterpack_BLUE();
        else
            TurnOff_Boosterpack_BLUE();
        //If the difference is between 10 and 20, then launchpad LED is red
        if (right - left >= 10 && right - left <= 20)
            TurnOn_Launchpad_LED2_RED();
        else
            TurnOff_Launchpad_LED2_RED();
        //If the difference is between 20 and 30, then launchpad LED is GREEN
        if (right - left >= 20 && right - left <= 30)
            TurnOn_Launchpad_LED2_GREEN();
        else
            TurnOff_Launchpad_LED2_GREEN();
        //If the difference is between 30 and 40, then launchpad LED is BLUE
        if (right - left >= 30 && right - left <= 40)
            TurnOn_Launchpad_LED2_BLUE();
        else
            TurnOff_Launchpad_LED2_BLUE();

        }


}






