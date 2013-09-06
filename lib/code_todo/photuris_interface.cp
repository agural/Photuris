/***********************************************************
 * photuris_interface.cpp
 * 
 * For getting information from the input devicee:
 *    - capacitive switch
 *    - capacitive slider
 *
 * Author: Albert Gural
 * Email:  ag@albertgural.com
 * Date:   2013/08/30 - 2013/08/30
 **********************************************************/

#include "../include/photuris_interface.h"

/*** Setup ***/
#define DEFAULT_THRESHOLD 0
#define DEFAULT_SAMPLES 0
// TODO: Setup routines for getting the capacitive sensor working.

/*** Capacitive Switch ***/

// Returns the main switch capacitive sensor analog value.
// @samples - number of times to poll for the main capacitive sensor value.
int getMainSwitchRaw(int samples = DEFAULT_SAMPLES) {
  return 0;
}

// Returns the main switch output state (on or off).
// @samples - number of times to poll for the main capacitive sensor value.
// @threshold - the sensor value at which the switch should read logical 1.
bool getMainSwitchState(int samples = DEFAULT_SAMPLES, int threshold = DEFAULT_THRESHOLD) {
  return getMainSwitchRaw(samples) > threshold * samples;
}

/*** Capacitive Slider ***/

char getActiveSliders(int samples = DEFAULT_SAMPLES) {
  return 0;
}

// Returns which key of slider 0 is most likely pressed (-1 if none).
// @samples - number of times to poll for the main capacitive sensor value.
// @threshold - the sensor value at which return value should not be -1.
int getSliderPosition0(int samples = DEFAULT_SAMPLES, int threshold = DEFAULT_THRESHOLD) {
  return 0;
}

// Returns which key of slider 1 is most likely pressed (-1 if none).
// @samples - number of times to poll for the main capacitive sensor value.
// @threshold - the sensor value at which return value should not be -1.
int getSliderPosition1(int samples = DEFAULT_SAMPLES, int threshold = DEFAULT_THRESHOLD) {
  return 0;
}

// Returns which key of slider 2 is most likely pressed (-1 if none).
// @samples - number of times to poll for the main capacitive sensor value.
// @threshold - the sensor value at which return value should not be -1.
int getSliderPosition2(int samples = DEFAULT_SAMPLES, int threshold = DEFAULT_THRESHOLD) {
  return 0;
}

// Returns which key of slider 3 is most likely pressed (-1 if none).
// @samples - number of times to poll for the main capacitive sensor value.
// @threshold - the sensor value at which return value should not be -1.
int getSliderPosition3(int samples = DEFAULT_SAMPLES, int threshold = DEFAULT_THRESHOLD) {
  return 0;
}

// Returns which key of all sliders is most likely pressed (-1 if none).
// @samples - number of times to poll for the main capacitive sensor value.
// @threshold - the sensor value at which return value should not be -1.
int getSliderPosition(int samples = DEFAULT_SAMPLES, int threshold = DEFAULT_THRESHOLD) {
  return 0;
}

