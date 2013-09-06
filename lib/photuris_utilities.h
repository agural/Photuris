/***********************************************************
 * photuris_utilities.h
 *
 * For getting information from Photuris utility sensors.
 *
 * Author: Albert Gural
 * Email:  ag@albertgural.com
 * Date:   2013/08/31 - 2013/08/31
 **********************************************************/

// Ensure this library description is only included once.
#ifndef photuris_utilities_h
#define photuris_utilities_h

/*** Useful Functions ***/

// Pauses the program execution for @count us. This allows for variable-length
// pauses (_delay_us only works for constant input).
void delay_us(int count);

// Pauses the program execution for @count ms. This allows for variable-length
// pauses (_delay_ms only works for constant input).
void delay_ms(int count);

/*** Bootloading ***/

// Moves the program counter to the start of the bootloader.
//void (*jump_to_bootloader)(void);

// Gets the MCU ready to accept USB commands with V-USB and bootload. Then calls
// jump_to_bootloader to actually go to the bootloader's location in memory.
void startBootloader(void);

/*** Battery Utilities ***/

#define EMPTY_VOLTAGE 2.7
#define FULL_VOLTAGE 4.2

float getBatteryVoltage();
int getBatteryPercent();
bool isCharging();

/*** Temperature Utilities ***/

#define MAX_LED_TEMPERATURE 50
#define HIGH_THRESH_TEMPERATURE 45
#define LOW_THRESH_TEMPERATURE 0
#define MIN_LED_TEMPERATURE -10

float getTemperature();

#endif // photuris_utilities_h
