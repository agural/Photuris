/***********************************************************
 * photuris_utilities.cpp
 * 
 * For getting information from Photuris utility sensors.
 *
 * Author: Albert Gural
 * Email:  ag@albertgural.com
 * Date:   2013/08/07 - 2013/08/30
 **********************************************************/

#include "../include/photuris_utitlities.h"

/*** Battery Utilities ***/

// Returns the current battery voltage in volts.
// Fully charged: 4.2V
// Nominal voltage: 3.3V - 3.7V
// Fully discharged: 2.7V
// Connected to charger: -1V
float getBatteryVoltage() {
  return 0;
}

// Returns the percent charge of the battery.
// Uses a standard Li-Ion discharge curve to approximate energy percentage
// (as opposed to just using the direct voltage level).
int getBatteryPercent() {
  return 0;
}

// Returns true if currently charging and false otherwise.
// This can also be used to determine whether the device is connected to USB.
bool isCharging() {
  return getBatteryVoltage() < 0;
}

/*** Temperature Utilities ***/

// Returns the current temperature in *C.
// Very high: 50*C
// High: 45*C
float getTemperature() {
  return 0;
}

