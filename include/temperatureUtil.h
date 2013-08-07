/***********************************************************
 * temperatureUtil.h
 * 
 * For getting Photuris temperature statistics.
 *
 * Author: Albert Gural
 * Email:  ag@albertgural.com
 * Date:   2013/08/07 - 2013/08/07
 **********************************************************/

#include "../lib/temperatureUtil.cpp"

#define REFERENCE_VOLTAGE 3.62
#define MAX_LED_TEMPERATURE 50
#define HIGH_THRESH_TEMPERATURE 45
#define LOW_THRESH_TEMPERATURE 0
#define MIN_LED_TEMPERATURE -10

float getTemperature();
float getTemperatureAt(int time);
void  snapshotTemperature();

