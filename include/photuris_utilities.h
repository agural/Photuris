/***********************************************************
 * photuris_utilities.h
 * 
 * For getting information from Photuris utility sensors.
 *
 * Author: Albert Gural
 * Email:  ag@albertgural.com
 * Date:   2013/08/31 - 2013/08/31
 **********************************************************/

#define REFERENCE_VOLTAGE 3.62

/*** Battery Utilities ***/

#define EMPTY_VOLTAGE 2.7
#define FULL_VOLTAGE 4.2

float getBatteryVoltage();
int getBatteryPercent();
bool isCharging;

/*** Temperature Utilities ***/

#define MAX_LED_TEMPERATURE 50
#define HIGH_THRESH_TEMPERATURE 45
#define LOW_THRESH_TEMPERATURE 0
#define MIN_LED_TEMPERATURE -10

float getTemperature();

