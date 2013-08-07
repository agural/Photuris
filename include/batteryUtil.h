/***********************************************************
 * batteryUtil.h
 * 
 * For getting Photuris battery statistics.
 *
 * Author: Albert Gural
 * Email:  ag@albertgural.com
 * Date:   2013/08/07 - 2013/08/07
 **********************************************************/

#include "../lib/batteryUtil.cpp"

#define REFERENCE_VOLTAGE 3.62
#define EMPTY_VOLTAGE 2.7
#define FULL_VOLTAGE 4.2

float getBatteryVoltage();
float getBatteryAt(int time);
void  snapshotBatteryVoltage();
bool  isCharging();

