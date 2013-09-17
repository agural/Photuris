/***********************************************************
 * photuris_interface.h
 *
 * For getting information from the input device:
 *    - capacitive switch
 *    - capacitive slider
 *
 * Author: Albert Gural
 * Email:  ag@albertgural.com
 * Date:   2013/08/31 - 2013/09/14
 **********************************************************/

#include <CapacitiveSensor.h>

// Ensure this library description is only included once.
#ifndef photuris_interface_h
#define photuris_interface_h

/*** Default Values ***/
#define DEFAULT_MAIN_SAMPLES 10
#define DEFAULT_SLIDE_SAMPLES 10
#define DEFAULT_MAIN_THRESHOLD 10
#define DEFAULT_SLIDE_THRESHOLD 10

/*** Main Switch ***/

// Returns the main switch capacitive sensor (0 - front) analog value.
// @samples - number of times to poll for the main capacitive sensor value.
int getMainSwitchFrontRaw(int samples = DEFAULT_MAIN_SAMPLES);

// Returns the main switch capacitive sensor (1 - back) analog value.
// @samples - number of times to poll for the main capacitive sensor value.
int getMainSwitchBackRaw(int samples = DEFAULT_MAIN_SAMPLES);

// Returns the main switch output state (on or off).
// @samples - number of times to poll for the main capacitive sensor value.
// @threshold - the sensor value at which the switch should read logical 1.
bool getMainSwitchState(int threshold = DEFAULT_MAIN_THRESHOLD, int samples = DEFAULT_MAIN_SAMPLES);

/*** Slider ***/

int getSlideRaw(char key, int samples = DEFAULT_SLIDE_SAMPLES);

#endif // photuris_interface_h
