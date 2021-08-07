## Tug of War Game
This repository contains the code for a Tug-of-War project using Texas Instrument's MSP432 microcontroller.

## Description
Displays two numbers on the screen in which you can increase and decrease the numbers 
using the button on the microcontroller. Depending on the values of both numbers, and using
comparison logic, a certain LED will light up. The logic can be summarized below:

- If the difference between left and right is within 10, LED1 should be RED
- If left is greater than right by 10 but less than or equal to 20, BLED should be RED
- If left is greater than right by 20 but less than or equal to 30, BLED should be GREEN
- If left is greater than right by 30 but less than or equal to 40(capped), BLED should be BLUE
- If right is greater than left by 10 but less than or equal to 20, LED2 should be RED
- If right is greater than left by 20 but less than or equal to 30, LED2 should be GREEN
- If right is greater than left by 30 but less than or equal to 40 (capped), LED2 should be BLUE

## How to Play
If you have access to Texas Instrument's MSP432 microcontroller and have downloaded CCS (Code Composer Studio),
then simply importing and running the project with ccs' play button will run the game.
