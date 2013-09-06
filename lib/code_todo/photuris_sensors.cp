/***********************************************************
 * photuris_sensors.cpp
 * 
 * For getting information from Photuris sensors.
 *
 * Author: Albert Gural
 * Email:  ag@albertgural.com
 * Date:   2013/08/30 - 2013/08/30
 **********************************************************/

#include "../include/photuris_sensors.h"

/*** Switch Light Sensor ***/

// Returns the current output of the light sensor.
int getLightSensorRaw() {
  return 0;
}

// Returns the raw light sensor output and stores the color sensed on the input
// array. Call calibrateColorSensor routine to calibrate color sensitivities.
// @colorOut - the 3-float array that will get updated with the current
//    RGB values from the color sensor.
int getColorSensor(float* colorOut) {
  return 0;
}

// Calibrates the color sensor. Place sensor near white surface and call this
// function. You only need to do it once (then you can hardcode the results or
// store it in EEPROM memory).
void calibrateColorSensor() {
  return 0;
}

/*** IR Sensor ***/

// Gets the current output state of the IR module.
bool getIrState() {
  return 0;
}

