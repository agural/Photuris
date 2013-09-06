/***********************************************************
 * photuris_display.cpp
 * 
 * For turning on the display LEDs.
 *
 * Author: Albert Gural
 * Email:  ag@albertgural.com
 * Date:   2013/08/30 - 2013/08/30
 **********************************************************/

#include "../include/photuris_display.h"

/*** Display Functions ***/

// Turn on specified display lights manually.
// TODO: Take function directly from photuris.cpp

// Turns on the RGB LEDs according to the current mode (uses PWM).
// @mode - Current flashlight mode (alternatively, just represents a color).
// @percent - What percentage of full output to turn the LED on.
void displayModeOn(int mode, float percent) {
  return;
}

// Turns on the UV LED.
// @percent - What percentage of full output to turn the LED on.
void displayOnUV(float percent) {
  return;
}

// Turns on the IR LED.
// @percent - What percentage of full output to turn the LED on.
void displayOnIR(float percent) {
  return;
}

