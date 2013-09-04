/***********************************************************
 * photuris_utilities.cpp
 *
 * For getting information from Photuris utility sensors.
 *
 * Author: Albert Gural
 * Email:  ag@albertgural.com
 * Date:   2013/08/07 - 2013/09/04
 **********************************************************/

#include "photuris_utitlities.h"

#include <math.h>

/*** Battery Utilities ***/

// Returns the current battery voltage in volts.
// Fully charged: 4.2V
// Nominal voltage: 3.3V - 3.7V
// Fully discharged: 2.7V
// Connected to charger: -1V
float getBatteryVoltage() {
    cbi(DDRC, 3);

    // 238.14 = 1024 [Full ADC Range] * 10/43 [Resistor Divider]
    const float kVoltageConvert = REFERENCE_VOLTAGE / 238.14;
    float voltage = kVoltageConvert * (float)analogRead(A3);
    if(voltage < 1.0) voltage = -1.0;

    delay(1);
    sbi(DDRC, 3);
    return voltage;
}

// Returns the theoretical (modeled) voltage you would expect after using a
// given fraction of the total charge of the battery.
// @usage - Fraction of the battery's charge used [0..1].
float getVoltageFromUsage(float usage) {
    // This formula is based on the AW IMR discharge curve.
    float voltage = 4.2 - 0.32 * log(8 * usage + 1) - exp(30 * (usage - 1));
    return voltage;
}


// Returns the percent charge of the battery [0..100] or -1 if charging.
// Uses a Li-Ion IMR discharge curve to approximate energy percentage
// (as opposed to just using the direct voltage level).
int getBatteryPercent() {
  const float kPrecision = 0.005;
  float pLower = 0.0, pUpper = 1.0;
  float voltage = getBatteryVoltage();
  if(voltage < 2.5) return -1;
  while(pUpper - pLower > kPrecision) {
      float pMiddle = (pLower + pUpper) / 2;
      // getVoltageFromUsage is monotonically decreasing so if it's too large,
      // we should use the upper range.
      if(getVoltageFromUsage(pMiddle) > voltage) {
          pLower = pMiddle;
      } else {
          pUpper = pMiddle;
      }
  }
  return (int)(pLower * 100);
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

